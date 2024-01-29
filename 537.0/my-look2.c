//TO DO
//Main fuctionality
//-V prints "my-look from CS537 Summer 2022\n", exit(0)
//-h prints help information regarding my-look, exit(0)
//-f allows use of a custom dictionary
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

int main(int argc, char* argv[])
{
  //Input subroutine
  if(argc == 1)
    {
      printf("my-look: invalid command line\n");
      exit(1);
    }
  char* filename = "/usr/share/dict/words";
  char* searchphrase = NULL;
  int opt;
  searchphrase = argv[argc-1];
  while((opt = getopt(argc, argv, "Vhf:")) != -1)
    {
      switch(opt)
	{
	case 'V':
	  printf("my-look from CS537 Summer 2022\n");
	  exit(0);
	case 'h':
	  printf("\nNAME\n\tmy-look - search for a word in a dictionary given a partial string\n\nSYNOPSIS\n\t./my-look [OPTIONS]... [SEARCH PHRASE]...\n\nDESCRIPTION\n\tSearch for word/words in either the default or a user defined dictionary.\n\n\t-V\n\t\tprints version information\n\n\t-h\n\t\tprints help information (this page)\n\n\t-f\n\t\tallows the user to specify a custom dictionary to search through (as opposed to the default dictionary)\n\n\tExit status:\n\t\t0 if OK\n\n\t\t1 if NOT OK\n\nAUTHOR\n\tWritten by Casey Waddell\n\nREPORTING BUGS\n\tLet's hope there aren't any to report\n\nCOPYRIGHT\n\tFree use, if you prefer my-look over look...\n\n");
	  exit(0);
	case 'f':
	  filename = optarg;
	  break;
	default:
	  printf("my-look: invalid command line\n");
	  exit(1);
	}
    }


  //Phrase cleanup subroutine
  char cleanup[50];
  int cleanupIndex = 0;
  int j = 0;
  while(*(searchphrase + j) != 0)
    {
      if((*(searchphrase + j) <= 122 && *(searchphrase + j) >= 97) || (*(searchphrase + j) <= 90 && *(searchphrase + j) >= 65) || (*(searchphrase + j) <= 57 && *(searchphrase + j) >= 48))
	{
	  cleanup[cleanupIndex] = *(searchphrase + j);
	  cleanupIndex++;
	}
      j++;
    }
  strncpy(searchphrase, cleanup, j);


  //Initialization
  FILE* file = fopen(filename, "r");
  if(file == NULL)
    {
      printf("cannot open file\n");
      exit(1);
    }
  char toComp[50];
  int copyFlag = 0;
  char outputBuffer[100][50];
  int index = 0;


  //Find words subroutine
  do
    {
      fgets(toComp, 50, file);
      if((strncasecmp(searchphrase, toComp, strlen(searchphrase))) == 0)
	{
	  copyFlag = 1;
	  strcpy(outputBuffer[index], toComp);
	  index++;
	}
      if(copyFlag == 1)
	{
	  if((strncasecmp(searchphrase, toComp, strlen(searchphrase))) != 0)
	    {
	      copyFlag = 0;
	    }
	}
    }
  while((toComp[0] >= 48 && toComp[0] <= 57) || (toComp[0] >= 97 && toComp[0] <= 122) || (toComp[0] >= 65 && toComp[0] <= 90));


  //Display results
  for(int i = 0; i < index; i++)
    {
      printf("%s", outputBuffer[i]);
    }
  fclose(file);
  exit(0);
  //real code part
}
