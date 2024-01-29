#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

char* writeFileName(char* fileNameBase, int fileNumber)
{
  char* fileName = (char*)malloc(strlen(fileNameBase) + 4);

  for(int i = 0; i < strlen(fileNameBase); i++)
    {
      fileName[i] = fileNameBase[i];
    }
  fileName[strlen(fileNameBase)] = '.';
  fileName[strlen(fileNameBase) + 1] = fileNumber + 48;
  fileName[strlen(fileNameBase) + 2] = 0;

  return fileName;
}

char* writeDirectoryName(int directoryNumber)
{
  char* directoryName = (char*)malloc(strlen("manXX") + 1);

  strcpy(directoryName, "manX");
  directoryName[3] = directoryNumber + 48;
  
  return directoryName;
}

char* writeFilePath(char* fileNameBase, int fileNumber, int directoryNumber)
{
  char* fileName = writeFileName(fileNameBase, fileNumber);
  char* directoryName = writeDirectoryName(directoryNumber);
  char* filePathHeader = "./man_pages/";
  char* filePath = (char*)malloc(strlen(directoryName) + strlen(fileName) + strlen(filePathHeader) + 2 + 2 + 1);
  
  strcpy(filePath, filePathHeader);
  strcat(filePath, directoryName);
  strcat(filePath, "/");
  strcat(filePath, fileName);

  free(fileName);
  free(directoryName);
  free(filePath);
  return filePath;
}


int main(int argc, char* argv[])
{
  FILE* file;
  char* filePath;
  char buffer[256];
  
  if(argc == 1)
    {
      printf("What manual page do you want?\nFor example, try 'wman wman'\n");
      exit(0);
    }
  if(argc == 2)
    {
      goto one;
    }
  if(argc == 3)
    {
      if(strlen(argv[1]) > 1)
	{
	  printf("invalid section\n");
	  exit(1);
	}

      int invalidFlag = 1;
      for(int i = 1; i < 10; i++)
	{
	  if(argv[1][0] - 48 == i) invalidFlag = 0;
	}
      if(invalidFlag)
	{
	  printf("invalid section\n");
	  exit(1);
	}
      
      goto two;
    }
  else
    {
      printf("wman has encountered an error\n");
      exit(1);
    }

 one:
  for(int i = 1; i < 10; i++)
    {
      filePath = writeFilePath(argv[1], i, i);
      file = fopen(filePath, "r");
      if(file == NULL)
	{
	  if(errno != ENOENT && errno != 0)
	    {
	      printf("cannot open file\n");
	      exit(1);
	    }
	  free(filePath);
	  continue;
	}
      
      while(fgets(buffer, 256, file))
	{
	  printf("%s", buffer);
	}
      
      fclose(file);
      exit(0);
    }
  if(errno == ENOENT)
    {
      printf("No manual entry for %s\n", argv[1]);
      exit(0);
    }

 two:
  int sectionNumber = atoi(argv[1]);

  filePath = writeFilePath(argv[2], sectionNumber, sectionNumber);
  
  file = fopen(filePath, "r");
  if(file == NULL)
    {
      if(errno == ENOENT)
	{
	  printf("No manual entry for %s in section %d\n", argv[2], sectionNumber);
	  exit(0);
	}
      printf("cannot open file\n");
      exit(1);
    }

  while(fgets(buffer, 256, file))
    {
      printf("%s", buffer);
    }

  fclose(file);
  exit(0);
}
