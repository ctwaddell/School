#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ARGSIZE 256

typedef struct Job
{
  char name[ARGSIZE];
  char args[10][ARGSIZE];
} Job;

typedef struct Task
{
  Job jobs[100];
  int background;
  int taskId;
  int pid;
  int jobNo;
  int jobc;
} Task;

Task* tasks;
int shellPID;
int shellPGID;
int shellfg;

void initializeTask(Task* task)
{
  for(int i = 0; i < 100; i++)
    {
      memset(task->jobs[i].name, 0, ARGSIZE);
      for(int j = 0; j < 10; j++)
	{
	  memset(task->jobs[i].args[j], 0, ARGSIZE);
	}
    }
  task->taskId = -1;
  task->background = 0;
  task->pid = 0;
  task->jobNo = 0;
  task->jobc = 0;
}

Task createTask(char args[100][ARGSIZE])
{
  Task task;
  initializeTask(&task);
  int index = 0;
  int jobNo = 0;
  int argNo = 0;
  int nameFlag = 0;

  for(int i = 0; i < 100; i++)
    {
      memset(task.jobs[i].name, 0, ARGSIZE);
      for(int j = 0; j < 10; j++)
	{
	  memset(task.jobs[i].args[j], 0, ARGSIZE);
	}
    }
  
  while(1)
    {
      if(args[index][0] == '\0') break;
      if(args[index][0] == '&')
	{
	  task.background = 1;
	  break;
	}
      if(args[index][0] == '|')
	{
	  task.background = 1;
	  nameFlag = 0;
	  argNo = 0;
	  jobNo++;
	  index++;
	  continue;
	}
      if(nameFlag == 0)
	{
	  strncpy(task.jobs[jobNo].name, args[index], strlen(args[index]));
	  nameFlag++;
	  index++;
	  continue;
	}
      strncpy(task.jobs[jobNo].args[argNo], args[index], strlen(args[index]));
      argNo++;
      index++;
    }
  task.jobc = jobNo + 1;
  task.jobNo = 0;
  return task;
}

Task* addTask(Task* task)
{
  for(int i = 1; i < 100; i++)
    {
      if(tasks[i].taskId != -1)
	{
	  continue;
	}
      task->taskId = i; 
      tasks[i] = *task;
      return &tasks[i];
    }
  return NULL;
}

void setTaskPID(Task* task, int pid)
{
  task->pid = pid;
  for(int i = 1; i < 100; i++)
    {
      if(tasks[i].taskId == task->taskId)
	{
	  tasks[i].pid = pid;
	  return;
	}
    }
}

Task* getTask(int pid)
{
  for(int i = 0; i < 100; i++)
    {
      if(tasks[i].pid == pid)
	{
	  return &tasks[i];
	}
    }
  return NULL;
}

void completeTask(Task* task)
{
  Task* curTask = getTask(task->pid);
  curTask->taskId = -1;
}

int getPath(Task* task, char path[ARGSIZE], int jobNo)
{
  memset(path, 0, ARGSIZE);
  strncpy(path, "/bin/", strlen("/bin/"));
  strcat(path, task->jobs[jobNo].name);
  if(!access(path, X_OK)) return 0;
  
  memset(path, 0, ARGSIZE);
  strncpy(path, "/usr/bin/", strlen("/usr/bin/"));
  strcat(path, task->jobs[jobNo].name);
  if(!access(path, X_OK)) return 0;
  
  write(1, "command not found\n", strlen("command not found\n"));
  return 1;
}

void printTask(Task* task, char string[ARGSIZE])
{
  int index = 0;
  int argNo = 0;
  char taskIdString[4] = {0};
  
  memset(string, 0, ARGSIZE);
  
  sprintf(taskIdString, "%d", task->taskId);
  strcat(string, taskIdString);
  strcat(string, ": ");

  while(task->jobs[index].name[0] != 0)
    {
      if(index > 0) strcat(string, "| ");
      strcat(string, task->jobs[index].name);
      strcat(string, " ");
      while(task->jobs[index].args[argNo][0] != '\0')
	{
      	  strcat(string, task->jobs[index].args[argNo]);
	  strcat(string, " ");
	  argNo++;
	}
      argNo = 0;
      index++;
    }
  if(index > 1 || task->background) strcat(string, "&\n");
  else strcat(string, "\n");
}

void getArgs(Task* task, char* args[ARGSIZE], int jobNo)
{
  for(int i = 0; i < ARGSIZE; i++)
    {
      args[i] = NULL;
    }
  args[0] = task->jobs[jobNo].name;
  
  int index = 1;
  while(task->jobs[jobNo].args[index - 1][0] != '\0')
    {
      args[index] = task->jobs[jobNo].args[index - 1];
      index++;
    }
}

int format(char buffer[ARGSIZE], char args[100][ARGSIZE])
{
  char* current = (char*)malloc(ARGSIZE);
  
  current = strtok(buffer, " \n");
  
  int index = 0;
  while(current != NULL)
    {
      strncpy(args[index], current, ARGSIZE);
      index++;
      current = strtok(NULL, " \n");
    }
  free(current);
  return index;
}


void nextJob(Task* nextJob)
{
  nextJob->jobNo++;
  int jobIndex = nextJob->jobNo;
  char* args[ARGSIZE];
  char path[ARGSIZE];
  getArgs(nextJob, args, jobIndex);
  getPath(nextJob, path, jobIndex); //make sure this is called within the child context

  execvp(path, args);
}

void signalChildHandler(int signal)
{
  int pid;
  int status;

  while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
      if(WIFEXITED(status))
	{
	  Task* curTask = getTask(pid);
	  if(curTask->jobc > 1) return;
	  else completeTask(curTask);
	}
    }
}

void signalChildHandlerMulti(int signal)
{
  int pid;
  int status;

  while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
      if(WIFEXITED(status))
	{
	  Task* curTask = getTask(pid);
	  completeTask(curTask);
	}
    }
}

void dummy(int signal)
{

}

int main(int argc, char* argv[])
{
  char buffer[ARGSIZE];
  char args[100][ARGSIZE];
  char compactargs[100][ARGSIZE];
  FILE* file;
  Task* currentTask;
  int batch = 0;
  
  shellPID = getpid();
  shellPGID = getpgid(shellPID);
  
  tasks = malloc(100 * sizeof(Task));

  Task emptyTask;
  initializeTask(&emptyTask);
  for(int i = 0; i < 100; i++)
    {
      tasks[i] = emptyTask;
    }
  
  signal(SIGTTOU, SIG_IGN);
  signal(SIGCHLD, signalChildHandler);
  
  if(argc == 1)
    {
      goto interactive;
    }
  if(argc == 2)
    {
      if((file = fopen(argv[1], "r")) == NULL)
	{
	  write(STDERR_FILENO, "Cannot open file ", strlen("Cannot open file "));
	  write(STDERR_FILENO, argv[1], strlen(argv[1]));
	  write(STDERR_FILENO, "\n", strlen("\n"));
	  exit(1);
	}
      batch = 1;
      goto interactive;
    }
  if(argc >= 3)
    {
      write(STDERR_FILENO, "Improper number of arguments\n", strlen("Improper number of arguments\n"));
      exit(1);
    }


 interactive:

  //GET INPUT
  memset(buffer, 0, ARGSIZE);
  for(int i = 0; i < 100; i++)
    {
      memset(args[i], 0, ARGSIZE);
      memset(compactargs[i], 0, ARGSIZE);
    }
  
  if(!batch) write(1, "wsh> ", strlen("wsh> "));

  if(fgets(buffer, ARGSIZE, stdin) == NULL) goto end;

  if(buffer == NULL)
    {
      goto end;
    }
  for(int i = 0; i < strlen(buffer); i++)
    {
      if(buffer[i] == EOF) goto end;
    }

  int argnum = format(buffer, args);

  
  //BUILT IN COMMANDS
  if(!strncmp(args[0], "\n", strlen(args[0]))) goto interactive;
  if(!strncmp(args[0], "exit\n", strlen(args[0]))) goto end;
  if(!strncmp(args[0], "cd", strlen(args[0])))
    {
      if(argnum != 2)
	{
	  write(1, "improper number of arguments for cd\n", strlen("improper number of arguments for cd\n"));
	  goto interactive;
	}
      if(!chdir(args[1])) goto interactive;
      write(1, "unable to open directory ", strlen("unable to open directory "));
      write(1, args[1], strlen(args[1]));
      write(1, "\n", strlen("\n"));
      goto interactive;
    }
  if(!strncmp(args[0], "jobs", strlen(args[0])))
    {
      for(int i = 1; i < 100; i++)
	{
	  char taskPrintBuffer[ARGSIZE];
	  if(tasks[i].taskId == -1) continue;
	  printTask(&tasks[i], taskPrintBuffer);
	  write(1, taskPrintBuffer, strlen(taskPrintBuffer));
	}
      goto interactive;
    }
  if(!strncmp(args[0], "fg", strlen(args[0])))
    {
      if(argnum == 1) //LARGEST
	{
	  for(int i = 99; i > 0; i--)
	    {
	      if(tasks[i].taskId != -1)
		{
		  currentTask = getTask(tasks[i].pid);
		  currentTask->background = 0;
		  goto resumeTask;
		}
	    }
	  write(1, "no tasks to switch to foreground\n", strlen("no tasks to switch to foreground\n"));
	  goto interactive;
	}
      if(argnum == 2 && atoi(args[1])) //PID
	{
	  currentTask = &tasks[atoi(args[1])];
	  if(currentTask->taskId != -1)
	    {
	      currentTask->background = 0;
	      goto resumeTask;
	    }
	  else
	    {
	      write(1, "task with id ", strlen("task with id "));
	      write(1, args[1], strlen(args[1]));
	      write(1, " could not be found\n", strlen(" could not be found\n"));
	      goto interactive;
	    }
	}
      else
	{
	  write(1, "invalid argument for fg\n", strlen("invalid argument for fg\n"));
	  goto interactive;
	}
    }
  if(!strncmp(args[0], "bg", strlen(args[0])))
    {
      if(argnum == 1)
	{
	  for(int i = 99; i > 0; i--)
	    {
	      if(tasks[i].taskId != -1)
		{
		  currentTask = getTask(atoi(args[1]));
		  currentTask->background = 1;
		  goto resumeTask;
		}
	    }
	}
      else if(argnum == 2 && atoi(args[1]))
	{
	  currentTask = &tasks[atoi(args[1])];
       	  if(currentTask->taskId != -1)
	    {
	      currentTask->background = 1;
	      goto resumeTask;
	    }
	  else
	    {
	      write(1, "task with id ", strlen("task with id "));
	      write(1, args[1], strlen(args[1]));
	      write(1, " could not be found\n", strlen(" could not be found\n"));
	      goto interactive; 
	    }
	}
      else
	{
	  write(1, "invalid command for bg\n", strlen("invalid command for bg\n"));
	  goto interactive;
	}
    }

  
  //PROCESS TASK
  char taskPrint[ARGSIZE];
  Task task = createTask(args);
  currentTask = &task;
  char path[ARGSIZE];
  
  if(!getPath(currentTask, path, 0) == 0) goto interactive;

 success: 
  addTask(currentTask);
  char* argList[ARGSIZE];
  getArgs(currentTask, argList, 0);

  if(currentTask->jobc > 1) goto runMulti;
  
  if(currentTask->background == 0) //FOREGROUND
    {
      int child = fork();
      if(child == 0)
	{
	  setpgid(0, 0);
	  tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
	  execvp(path, argList);
	}
      else
	{
	  int status;
	  setTaskPID(currentTask, child);
	  waitpid(currentTask->pid, &status, WUNTRACED);
	  tcsetpgrp(STDIN_FILENO, shellPGID);
	  if(WIFSTOPPED(status))
	    {
	      goto interactive;
	    }
	  completeTask(currentTask);
	}
    }
  else //BACKGROUND
    {
      int child = fork();
      if(child == 0)
	{
	  execvp(path, argList);
	}
      else
	{
	  tcsetpgrp(STDIN_FILENO, shellPGID);
	  setTaskPID(currentTask, child);
	}
    }

  goto interactive;

 runMulti:
  int child = fork();
  if(child == 0)
    {
      int pipefiles[2];
      pipe(pipefiles);
      close(pipefiles[0]);
      dup2(pipefiles[1], STDOUT_FILENO);
      close(pipefiles[1]);
      while(currentTask->jobNo < currentTask->jobc)
	{
	  int subproc = fork();
	  int subprocstatus;
	  if(subproc == 0)
	    {
	      execvp(path, argList);
	    }
	  else
	    {
	      signal(SIGCHLD, signalChildHandlerMulti);
	      waitpid(subproc, &subprocstatus, 0);
	      currentTask->jobNo++;
	    }
	}
    }
  else
    {
      signal(SIGCHLD, signalChildHandlerMulti);
      tcsetpgrp(STDIN_FILENO, shellPGID);
      setTaskPID(currentTask, child);
      goto interactive;
    }

  exit(0);
  
 resumeTask:

  int status;
  if(currentTask->background)
    {
      kill(currentTask->pid, SIGCONT);
      goto interactive;
    }
  else
    {
      tcsetpgrp(STDIN_FILENO, currentTask->pid);
      kill(currentTask->pid, SIGCONT);
      waitpid(currentTask->pid, &status, WUNTRACED);
      tcsetpgrp(STDIN_FILENO, shellPGID);
      if(WIFSTOPPED(status)) goto interactive;
      completeTask(currentTask);
      goto interactive;
    }
  
 end:
  
  exit(0);
}
