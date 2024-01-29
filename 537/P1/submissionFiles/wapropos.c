#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <dirent.h>

char* writeDirectoryPath(int directoryNumber)
{
  char* directoryBase = "./man_pages/manX/";
  char* directoryPath = (char*)malloc(strlen(directoryBase) + 1);
  strcpy(directoryPath, directoryBase);
  directoryPath[15] = directoryNumber + 48;
  return directoryPath;
}

char* writeFilePath(char* directoryPath, char* fileName)
{
  char* filePath = (char*)malloc(strlen(directoryPath) + strlen(fileName) + 1);
  strcpy(filePath, directoryPath);
  for(int i = strlen(directoryPath); i < strlen(directoryPath) + strlen(fileName) + 1; i++)
    {
      filePath[i] = fileName[i - strlen(directoryPath)];
    }
  
  return filePath;
}

char* searchFile(char* fileName, char* directoryPath, char* searchTerm, int directoryNumber)
{
  char name[] = {27, 91, 49, 109, 78, 65, 77, 69, 0};
  char description[] = {27, 91, 49, 109, 68, 69, 83, 67, 82, 73, 80, 84, 73, 79, 78, 0};
  char* filePath = writeFilePath(directoryPath, fileName);
  FILE* file;
  char buffer[256];
  char nameBuffer[256];
  int bufferFlag = 0;
  
  file = fopen(filePath, "r");
  if(file == NULL)
    {
      free(filePath);
      return NULL;
    }
  
  while(fgets(buffer, 256, file))
    {
      bufferFlag = 0;
      if(strncmp(buffer, name, 8) == 0) bufferFlag = 1;
      if(bufferFlag || strncmp(buffer, description, 15) == 0)
	{
	  while(fgets(buffer, 256, file) && buffer[0] != 10)
	    {
	      if(bufferFlag) strcpy(nameBuffer, buffer);
	      char* searchResult = strstr(buffer, searchTerm);
	      if(searchResult == NULL) continue;
	      goto match;
	    }
	  
	}
    }
  fclose(file);
  free(filePath);
  return NULL;
  
 match:
  char simpleFileName[strlen(fileName)];
  strcpy(simpleFileName, fileName);
  for(int i = 0; i < strlen(simpleFileName); i++)
    {
      if(simpleFileName[i] == '.') simpleFileName[i] = 0;
    }

  char section[] = {32, 40, directoryNumber + 48, 41, 32, 45, 32, 0};
  
  for(int j = 0; j < strlen(nameBuffer) + 1; j++)
    {
      if(nameBuffer[j] == '-')
	{
	  memmove(nameBuffer, nameBuffer + j + 2, 255 - j); 
	}
    }
  
  char returnString[strlen(simpleFileName) + strlen(section) + strlen(nameBuffer) + 2];
  memset(returnString, 0, strlen(simpleFileName) + strlen(section) + strlen(nameBuffer) + 2);

  strcat(returnString, simpleFileName);
  strcat(returnString, section);
  strcat(returnString, nameBuffer);

  char* returnStringPointer = (char*)malloc(strlen(returnString) + 1);
  strcpy(returnStringPointer, returnString);

  fclose(file);
  free(filePath);
  return returnStringPointer;
}

int main(int argc, char* argv[])
{
  if(argc == 1)
    {
      printf("wapropos what?\n");
      exit(0);
    }
  if(argc == 2)
    {
      goto search;
    }
  else
    {
      printf("wapropos has encountered an error\n");
      exit(1);
    }
  
 search:
  DIR* directory;
  char* directoryPath;
  char* result;
  int hasFound = 0;
  
  for(int i = 1; i < 10; i++)
    {
      directoryPath = writeDirectoryPath(i);
      directory = opendir(directoryPath);
      if(directory == NULL)
	{
	  printf("wapropos has encountered an error\n");
	  exit(1);
	}
      struct dirent* nextEntry = readdir(directory);
      while(nextEntry != NULL)
	{
	  result = NULL;
	  if(nextEntry->d_name[0] != '.')
	    {
	      result = searchFile(nextEntry->d_name, directoryPath, argv[1], i);
	      if(result != NULL)
		{
		  hasFound = 1;
		  printf("%s", result);
		}
	      free(result);
	    }
	  nextEntry = readdir(directory);
	}
      free(directoryPath);
      closedir(directory);
    }
  if(!hasFound) printf("nothing appropriate\n");
  exit(0);
}
