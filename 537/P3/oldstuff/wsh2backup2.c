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
} Task;

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
  task->background = -1;
  task->pid = 0;
}

void createTask(Task* task, char args[100][ARGSIZE])
{
  int index = 0;
  int jobNo = 0;
  int argNo = 0;
  int nameFlag = 0;

  task->background = 0;
  
  for(int i = 0; i < 100; i++)
    {
      memset(task->jobs[i].name, 0, ARGSIZE);
      for(int j = 0; j < 10; j++)
	{
	  memset(task->jobs[i].args[j], 0, ARGSIZE);
	}
    }

  while(1)
    {
      if(args[index][0] == '\0') break;
      if(args[index][0] == '&')
	{
	  task->background = 1;
	  break;
	}
      if(args[index][0] == '|')
	{
	  nameFlag = 0;
	  argNo = 0;
	  jobNo++;
	  index++;
	  continue;
	}
      if(nameFlag == 0)
	{
	  strncpy(task->jobs[jobNo].name, args[index], strlen(args[index]));
	  nameFlag++;
	  index++;
	  continue;
	}
      strncpy(task->jobs[jobNo].args[argNo], args[index], strlen(args[index]));
      argNo++;
      index++;
    }
  return;
}

void addTask(Task* task, Task tasks[100])
{
  for(int i = 1; i < 100; i++)
    {
      if(tasks[i].taskId != -1)
	{
	  continue;
	}
      task->taskId = i; 
      tasks[i] = *task;
      return;
    }
}

void completeTask(int taskId, Task tasks[100])
{
  tasks[taskId].taskId = -1;
}

void printTask(Task task, char string[ARGSIZE])
{
  int index = 0;
  int argNo = 0;
  char taskIdString[4] = {0};
  
  memset(string, 0, ARGSIZE);
  
  sprintf(taskIdString, "%d", task.taskId);
  strcat(string, taskIdString);
  strcat(string, ": ");

  while(task.jobs[index].name[0] != 0)
    {
      if(index > 0) strcat(string, "| ");
      strcat(string, task.jobs[index].name);
      strcat(string, " ");
      while(task.jobs[index].args[argNo][0] != '\0')
	{
      	  strcat(string, task.jobs[index].args[argNo]);
	  strcat(string, " ");
	  argNo++;
	}
      argNo = 0;
      index++;
    }
  if(index > 1 || task.background) strcat(string, "&\n");
  else strcat(string, "\n");
}

void getArgs(Task task, char* args[ARGSIZE], int jobNo)
{
  for(int i = 0; i < ARGSIZE; i++)
    {
      args[i] = NULL;
    }
  args[0] = task.jobs[jobNo].name;
  
  int index = 1;
  while(task.jobs[jobNo].args[index - 1][0] != '\0')
    {
      args[index] = task.jobs[jobNo].args[index - 1];
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

void signalHandler(int signal)
{
  if(signal == 2)
    {
      write(1, "\n", strlen("\n"));
      exit(0);
    }
  if(signal == 20) exit(0); //WRITE SUSPEND FUNCTION HERE LATER
  if(signal == 17)
    {
      write(1, "done child", strlen("done child"));
    }
}


int main(int argc, char* argv[])
{
  char buffer[ARGSIZE];
  char args[100][ARGSIZE];
  char compactargs[100][ARGSIZE];
  FILE* file;

  Task* tasks = malloc(100 * sizeof(Task));
  
  for(int i = 0; i < 100; i++)
    {
      initializeTask(&tasks[i]);
    }

  signal(SIGINT, signalHandler);
  signal(SIGTSTP, signalHandler);
  
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
      goto batch;
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
  
  write(1, "wsh> ", strlen("wsh> "));

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
	  printTask(tasks[i], taskPrintBuffer);
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
		  tcsetpgrp(STDIN_FILENO, tasks[i].pid);
		  goto interactive;
		}
	    }
	  write(1, "no tasks to switch to foreground\n", strlen("no tasks to switch to foreground\n"));
	  goto interactive;
	}
      if(argnum == 2 && atoi(args[1])) //DEFAULT
	{
	  for(int i = 1; i < 100; i++)
	    {
	      if(tasks[i].taskId == atoi(args[1]))
		{
		  //tcsetpgrp
		  goto interactive;
		}
	    }
	  write(1, "task with id ", strlen("task with id2 "));
	  write(1, args[1], strlen(args[1]));
	  write(1, " could not be found\n", strlen(" could not be found\n"));
	  goto interactive;
	}
      else
	{
	  write(1, "invalid argument for fg\n", strlen("invalid argument for fg\n"));
	  goto interactive;
	}
    }
  if(!strncmp(args[0], "bg", strlen(args[0])))
    {

    }


  //PROCESS TASK
  Task task;
  Task* taskPointer = &task;
  char taskPrint[ARGSIZE];
  createTask(taskPointer, args);
  addTask(taskPointer, tasks);
  //completeTask(task, tasks);
  
  char path[ARGSIZE] = {0};
  strncpy(path, "/bin/", strlen("/bin/"));
  strcat(path, task.jobs[0].name);
  if(!access(path, X_OK)) goto success;

  memset(path, 0, ARGSIZE);
  strncpy(path, "/usr/bin/", strlen("/usr/bin/"));
  strcat(path, task.jobs[0].name);
  if(!access(path, X_OK)) goto success;
  
  write(1, "command not found\n", strlen("command not found\n"));
  goto interactive;

 success: 
  
  char* argList[ARGSIZE];
  getArgs(task, argList, 0);
  
  if(!task.background)
    {
      int child = fork();
      if(child == 0)
	{
	  execvp(path, argList);
	}
      else
	{
	  signal(SIGCHLD, signalHandler);
	  int status = -1;
	  task.pid = child;
	  waitpid(task.pid, &status, 0);
	}
    }
  else
    {
      int child = fork();
      if(child == 0)
	{
	  execvp(path, argList);
	}
      else
	{
	  signal(SIGCHLD, signalHandler);
	  int status = -1;
	  task.pid = child;
	  waitpid(task.pid, &status, WNOHANG);
	}
    }

  goto interactive;
  
 batch:
  
 end:
  
  exit(0);
}
