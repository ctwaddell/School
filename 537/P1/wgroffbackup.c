#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
  if(argc == 1)
    {
      printf("Improper number of arguments\nUsage: ./wgroff <file>\n");
      exit(0);
    }
  if(argc == 2)
    {
      goto convert;
    }
  if(argc == 3)
    {
      printf("wgroff has encountered an error.\n");
      exit(1);
    }

 convert:
  FILE* file;
  FILE* standardOutBackup = stdout;
  char buffer[256];
  int currentLineNumber = 0;
  
  char* filePath = (char*)malloc(strlen(argv[1]) + 3);
  strcpy(filePath, "./");
  strcat(filePath, argv[1]);

  file = fopen(filePath, "r");
  if(file == NULL)
    {
      if(errno == ENOENT)
	{
	  printf("File doesn't exist\n");
	  exit(0);
	}
      printf("wgroff has encountered an error\n");
      exit(1);
    }
  free(filePath);
  
  fgets(buffer, 256, file);
  currentLineNumber++;

  if(buffer[0] != '.' && buffer[1] != 'T' && buffer [2] != 'H') goto formatError;

  int spaceIndices[4];
  int currIndex = 0;
  for(int i = 0; i < strlen(buffer); i++)
    {
      if(currIndex == 3 && (buffer[i] == '\n' || buffer[i] == '\t' || buffer[i] == ' '))
	{
	  spaceIndices[currIndex] = i;
	  break;
	}
      if(buffer[i] == ' ' && currIndex < 4)
	{
	  spaceIndices[currIndex] = i;
	  currIndex++;
	}
    }
  
  char* commandName = (char*)malloc(spaceIndices[1] - spaceIndices[0]);
  char* sectionName = (char*)malloc(spaceIndices[2] - spaceIndices[1]);
  char* dateName = (char*)malloc(spaceIndices[3] - spaceIndices[2]);

  currIndex = 0;
  for(int j = 0; j < spaceIndices[1] - spaceIndices[0]; j++)
    {
      commandName[j] = buffer[j + spaceIndices[0] + 1];
    }
  commandName[spaceIndices[1] - spaceIndices[0] - 1] = 0;
  
  for(int k = 0; k < spaceIndices[2] - spaceIndices[1]; k++)
    {
      sectionName[k] = buffer[k + spaceIndices[1] + 1];
    }
  sectionName[spaceIndices[2] - spaceIndices[1] - 1] = 0;

  for(int l = 0; l < spaceIndices[3] - spaceIndices[2]; l++)
    {
      dateName[l] = buffer[l + spaceIndices[2] + 1];
    }
  dateName[spaceIndices[3] - spaceIndices[2] - 1] = 0;

  if(strlen(sectionName) > 1 || sectionName[0] < 49 || sectionName[0] > 57) goto formatError;

  if(strlen(dateName) > 10 || (dateName[0] < 48 || dateName[0] > 57) || (dateName[1] < 48 || dateName[1] > 57) || (dateName[2] < 48 || dateName[2] > 57) || (dateName[3] < 48 || dateName[3] > 57) || (dateName[5] < 48 || dateName[5] > 57) || (dateName[6] < 48 || dateName[6] > 57) || (dateName[8] < 48 || dateName[8] > 57) || (dateName[9] < 48 || dateName[9] > 57) || dateName[4] != 45 || dateName[7] != 45) goto formatError;


  char* outputFileName = (char*)malloc(strlen(commandName) + 3);
  char terminus[] = {46, atoi(sectionName) + 48, 0};
  strcpy(outputFileName, commandName);
  strcat(outputFileName, terminus);
  
  stdout = fopen(outputFileName, "w");
  free(outputFileName);
  
  int charLeft = 80;
  int commandSize = strlen(commandName) + 3;
  printf("%s(%s)", commandName, sectionName);
  charLeft -= commandSize;
  while(charLeft > commandSize)
    {
      printf(" ");
      charLeft--;
    }
  printf("%s(%s)\n", commandName, sectionName);

  free(commandName);
  free(sectionName);
  
  while(fgets(buffer, 256, file))
    {
      currentLineNumber++;
      if(buffer[0] == '#') goto endloop;
      if(buffer[0] == '.' && buffer[1] == 'S' && buffer[2] == 'H')
	{
	  printf("\n\033[1m");
	  for(int z = 4; z < strlen(buffer); z++)
	    {
	      if(buffer[z] >= 97 && buffer[z] <= 122) buffer[z] -= 32;
	      printf("%c", buffer[z]);
	    }
	  printf("\033[0m\n");
	  goto endloop;
	}
      for(int m = 0; m < strlen(buffer); m++)
	{
	  if(buffer[m] == 47 && buffer[m + 1] == 'f')
	    {
	      if(buffer[m + 2] == 'B')
		{
		  printf("\033[1m");
		  m += 3;
		}
	      if(buffer[m + 2] == 'I')
		{
		  printf("\033[3m");
		  m += 3;
		}
	      if(buffer[m + 2] == 'U')
		{
		  printf("\033[4m");
		  m += 3;
		}
	      if(buffer[m + 2] == 'P')
		{
		  printf("\033[0m");
		  m += 3;
		}
	    }
	  if(buffer[m] == 47 && buffer[m + 1] == 47)
	    {
	      printf("%c", 47);
	      m += 1;
	      continue;
	    }
	  printf("%c", buffer[m]);
	}

      
    endloop: continue;
    }
  
  for(int x = 0; x < 36; x++)
    {
      printf(" ");
    }
  printf("%s", dateName);
  free(dateName);
  for(int y = 0; y < 36; y++)
    {
      printf(" ");
    }
  printf("\n");

  fclose(file);
  fclose(stdout);
  stdout = standardOutBackup;
  
  exit(0);
  
 formatError:
  printf("Improper formatting on line %d\n", currentLineNumber);
  fclose(file);
  fclose(stdout);
  stdout = standardOutBackup;
  exit(0);
}
