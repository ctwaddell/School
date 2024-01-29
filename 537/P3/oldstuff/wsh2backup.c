#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

typedef struct Job
{
  char name[512];
  char args[10][512];
} Job;

typedef struct Task
{
  Job jobs[100];
  int taskId;
  int background;
} Task;

void createTask(Task task, char args[100][512], int taskId)
{
  int index = 0;
  int jobNo = 0;
  int argNo = 0;
  int nameFlag = 0;

  task.background = 0;
  task.taskId = taskId;
  taskId++;
  
  for(int i = 0; i < 100; i++)
    {
      memset(task.jobs[i].name, 0, 512);
      for(int j = 0; j < 10; j++)
	{
	  memset(task.jobs[i].args[j], 0, 512);
	}
    }
  
 create:
  argNo = 0;
  nameFlag = 0;
  while(args[index][0] != '|')
    {
      if(jobNo > 0) task.background = 1;
      if(args[index][0] == '\0') goto done;
      if(args[index][0] == '&')
	{
	  task.background = 1;
	  continue;
	}
      
      if(nameFlag == 0)
	{
	  strncpy(task.jobs[jobNo].name, args[index], strlen(args[index]));
	  nameFlag++;
	  continue;
	}
      strncpy(task.jobs[jobNo].args[argNo], args[index], strlen(args[index]));
      argNo++;
      index++;
    }
  jobNo++;
  goto create;

 done:
  printf("&\n%d, %d\n$", task.taskId, taskId);
  return;
}

void printTask(Task task, char string[512])
{
  int index = 0;
  int argNo = 0;
  char taskIdS[4] = {0};
  
  memset(string, 0, 512);

  printf("\n\n%d\n\n", task.taskId);
  
  sprintf(taskIdS, "%d", task.taskId);
  strcat(string, taskIdS);
  strcat(string, ":!~!\n ");

  write(1, string, strlen(string));
 
  while(task.jobs[index].name[0] != 0)
    {
      if(index > 0) strcat(string, " | ");
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
  if(index > 1 || task.background) strcat(string, "&");

  write(1, string, strlen(string));
}


int format(char buffer[512], char args[100][512])
{
  char* current = (char*)malloc(512);
  
  current = strtok(buffer, " \n");
  
  int index = 0;
  while(current != NULL)
    {
      strncpy(args[index], current, 512);
      index++;
      current = strtok(NULL, " ");
    }
  free(current);
  return index;
}

int compact(char args[100][512], char returnargs[100][512])
{
  int index = 0;
  int returnIndex = 0;
  int argc = 1;
  Task taskList[100];
  
  while(args[index][0] != 0)
    {
      if(args[index][0] == '|')
	{
	  returnIndex++;
	  returnargs[returnIndex][0] = '|';
	  returnIndex++;
	  argc++;
	}
      else
	{
	  strcat(returnargs[returnIndex], args[index]);
	  strcat(returnargs[returnIndex], " ");
	}
      index++;
    }
  return argc;
}

int main(int argc, char* argv[])
{
  char buffer[512];
  char args[100][512];
  char compactargs[100][512];
  int taskId = 0;
  FILE* file;
  
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

  memset(buffer, 0, 512);
  for(int i = 0; i < 100; i++)
    {
      memset(args[i], 0, 512);
      memset(compactargs[i], 0, 512);
    }
  
  write(1, "wsh> ", strlen("wsh> "));

  if(fgets(buffer, 512, stdin) == NULL) goto end;

  if(buffer == NULL)
    {
      goto end;
    }
  for(int i = 0; i < strlen(buffer); i++)
    {
      if(buffer[i] == EOF) goto end;
    }

  int argnum = format(buffer, args);
  
  Task task;
  char taskPrint[512];
  createTask(task, args, taskId);

  printf("!\n\n%d\n\n!", task.taskId);
  
  printTask(task, taskPrint);

  write(1, "seg", 3);
  
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
      goto interactive;
    }
  if(!strncmp(args[0], "jobs", strlen(args[0])))
    {
      
    }
  if(!strncmp(args[0], "fg", strlen(args[0])))
    {
      
    }
  if(!strncmp(args[0], "bg", strlen(args[0])))
    {

    }

  char path[512] = {0};
  strncpy(path, "/bin/", strlen("/bin/"));
  strcat(path, args[0]);
  if(!access(path, X_OK)) goto success;

  memset(path, 0, 512);
  strncpy(path, "/usr/bin/", strlen("/usr/bin/"));
  strcat(path, args[0]);
  if(!access(path, X_OK)) goto success;
  
  write(1, "command not found\n", strlen("command not found\n"));
  goto interactive;

 success:
  
  int child = fork();
  if(child == 0)
    {
      //execvp(args[0], compactargs);
    }
  else
    {

    }
  goto interactive;
  
 batch:
  
 end:
  
  exit(0);
}
