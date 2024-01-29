// Copyright 2022 Casey Waddell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("wordle: invalid number of args\n");
    exit(1);
  }
  char* blacklist = argv[argc - 1];
  char* filename = argv[1];
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("wordle: cannot open file\n");
    exit(1);
  }

  char toComp[50];
  int noPrint = 0;
  char* condition;

  while (1) {
    noPrint = 0;
    condition = fgets(toComp, 50, file);
    if (condition == NULL) {
      exit(0);
    }
    if (strlen(toComp) != 6) {
      continue;
    } else {
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < strlen(blacklist); j++) {
          if (toComp[i] == blacklist[j]) {
            noPrint = 1;
            break;
          }
        }
      }
      if (noPrint == 1) {
        continue;
      } else {
        printf("%s", toComp);
      }
    }
  }
  fclose(file);
}
