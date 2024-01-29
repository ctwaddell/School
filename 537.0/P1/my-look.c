// Copyright 2022 Casey Waddell

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

int main(int argc, char* argv[]) {
  // Input subroutine
  if (argc == 1) {
      printf("my-look: invalid command line\n");
      exit(1);
    }
  char* filename = "/usr/share/dict/words";
  char* searchphrase = NULL;
  int opt;
  searchphrase = argv[argc-1];
  while ((opt = getopt(argc, argv, "Vhf:")) != -1) {
    switch (opt) {
    case 'V':
      printf("my-look from CS537 Summer 2022\n");
      exit(0);
    case 'h':
      printf("\nNAME\n\tmy-look - search for a word");
      printf("in a dictionary given a partial string\n");
      printf("\nSYNOPSIS\n\t./my-look [OPTIONS]... [SEARCH PHRASE]...\n");
      printf("\nDESCRIPTION\n\tSearch for word/words in");
      printf("either the default or a user defined dictionary.");
      printf("\n\n\t-V\n\t\tprints version information\n");
      printf("\n\t-h\n\t\tprints help information (this page)\n");
      printf("\n\t-f\n\t\tallows the usertto specify a");
      printf("custom dictionary to search through");
      printf("(as opposed to the default dictionary)\n");
      printf("\n\tExit status:\n\t\t0 if OK\n\n\t\t1 if NOT OK\n");
      printf("\nAUTHOR\n\tWritten by Casey Waddell\n");
      printf("\nREPORTING BUGS\n\tLet's hope there aren't any to report\n");
      printf("\nCOPYRIGHT\n\tCopyright 2022 Casey Waddell\n\n");
      exit(0);
    case 'f':
      filename = optarg;
      break;
    default:
      printf("my-look: invalid command line\n");
      exit(1);
    }
  }

  // Phrase cleanup subroutine
  char cleanup[255];
  int cleanupIndex = 0;
  int j = 0;
  while (*(searchphrase + j) != 0) {
    if ((*(searchphrase + j) <= 122 && *(searchphrase + j) >= 97)
        || (*(searchphrase + j) <= 90 && *(searchphrase + j) >= 65)
        || (*(searchphrase + j) <= 57 && *(searchphrase + j) >= 48)) {
      cleanup[cleanupIndex] = *(searchphrase + j);
      cleanupIndex++;
    }
    j++;
  }
  strncpy(searchphrase, cleanup, j);


  // Initialization
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("my-look: cannot open file\n");
    exit(1);
  }
  char toComp[255];
  int copyFlag = 0;
  // char apostropheCheck[255];
  char apos[255] = {0};
  // Find words subroutine
  strncpy(apos, searchphrase, strlen(searchphrase));
  apos[strlen(searchphrase) + 1] = 0;
  apos[strlen(searchphrase)] = 's';
  apos[strlen(searchphrase) - 1]  = 39;

  do {
    fgets(toComp, 50, file);
    if ((strncasecmp(searchphrase, toComp, strlen(searchphrase))) == 0
        || strncasecmp(apos, toComp, strlen(searchphrase)) == 0) {
      copyFlag = 1;
      printf("%s", toComp);
    }
    if (copyFlag == 1) {
      if ((strncasecmp(searchphrase, toComp, strlen(searchphrase))) != 0) {
        copyFlag = 0;
      }
    }
  } while ((toComp[0] >= 48 && toComp[0] <= 57)
           || (toComp[0] >= 97 && toComp[0] <= 122)
           || (toComp[0] >= 65 && toComp[0] <= 90));

  // Wrap up
  fclose(file);
  exit(0);
}
