// Copyright 2022 Casey Waddell

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
  int index;
  char input[512];
  char* exitMsg = "exit\n";
  FILE* file;
  char* check;
  char command[100][540];
  int child;

  if (argc == 1) {
      goto interactive;
  } else if (argc == 2) {
    if (argv[1][0] == '-') {
      write(STDERR_FILENO, "mysh: invalid command line\n", 27);
      exit(1);
    }
      if ((file = fopen(argv[1], "r")) == NULL) {
        write(STDERR_FILENO, "Error: Cannot open file ", 24);
          write(STDERR_FILENO, argv[1], strlen(argv[1]));
          write(STDERR_FILENO, ".\n", strlen(".\n"));
          exit(1);
      } else {
        goto batch;
      }
  } else {
    char* error = "Usage: mysh [batch-file]\n";
    write(STDERR_FILENO, error, strlen(error));
    exit(1);
  }

  int sanitize(char* str) {
    int limit = strlen(str);
    char* savestate = &*str;
    char str2[540];
    int boost = 0;

    strncpy(str2, str, strlen(str) + 1);

    for (int i = 0; i < limit; i++) {
      while (str2[i + boost] == 9 || str2[i + boost] == 10) {
          boost++;
        }
      *str = str2[i + boost];
      str++;
      }
    str = &*savestate;
    return 0;
  }

  int freeblocks(char* arg[]) {
    for (int i = 0; i < 100; i++) {
      free(arg[i]);
      arg[i] = NULL;
    }
    return 0;
  }

  interactive:
  {
    // RESET MEMORY AND DISPLAY PROMPT
    char* argv2[100];
    memset(input, 0, 512);
    for (int i = 0; i < 100; i++) {
      memset(command[i], 0, 540);
      argv2[i] = NULL;
    }
    write(1, "mysh> ", 6);

    // READ AND PARSE INPUT
    check = fgets(input, 512, stdin);
    if (check == NULL) {
      goto end;
    }
    if (strncmp(input, exitMsg, strlen(input)) == 0) {
      goto end;
    }
    for (int i = 0; i < strlen(input); i++) {
      if (input[i] == EOF) {
            goto end;
      }
    }

    // SANITIZE INPUT
    sanitize(input);

    // CHECK 0: EMPTY INPUT
    if (strlen(input) == 0) {
      goto interactive;
    }

    // CHECK 1: > BEGINNING INPUT
    if (input[0] == '>') {
      write(STDERR_FILENO, "Redirection misformatted.\n", 26);
      goto interactive;
    }

    // CHECK 2: SPACES ONLY INPUT
    int spacecheck = 0;
    for (int i = 0; i < strlen(input); i++) {
      if (input[i] != 32) {
        spacecheck = 1;
        break;
      }
    }
    if (spacecheck == 0) {
      goto interactive;
    }

    // SEPARATE INPUT COMMANDS
    check = strtok(input, " ");
    strncpy(command[0], check, strlen(check));
    index = 1;
    while ((check = strtok(NULL, " ")) != NULL && index < 100) {
      strncpy(command[index], check, strlen(check));
      index++;
    }
    check = strtok(command[index-1], ">");
    while ((check = strtok(NULL, ">")) != NULL && index < 100) {
      strncpy(command[index], ">\0", 2);
      strncpy(command[index + 1], check, strlen(check) + 1);
    }
    if (command[index - 1][0] == '>' && command[index - 1][1] != 0) {
        check = strtok(command[index-1], ">");
        strncpy(command[index], check, strlen(check));
        strncpy(command[index - 1], ">\0", 2);
    }

    // COPY DATA
    int i = 0;
    while (command[i][0] != 0 && command[i][0] != '>') {
      argv2[i] = malloc(strlen(command[i]) + 1);
      strncpy(argv2[i], command[i], strlen(command[i]) + 1);
      i++;
    }

    // INTERPRET DATA AND REDIRECTION
    int redirection = 0;
    while (command[i][0] != 0) {
      if (command[i][0] == '>') {
        redirection = i;
      }
      i++;
    }
    if (redirection) {
      // IMPROPER REDIRECTION CHECK
      if (command[redirection + 1][0] == '>'
          || command[redirection + 2][0] != 0
          || command[redirection + 1][0] == 0) {
            write(STDERR_FILENO, "Redirection misformatted.\n", 26);
            freeblocks(argv2);
            goto interactive;
      }
      int failure = 0;
      for (int i = 0; i < 100; i++) {
        if (command[i][0] == '>') {
          failure++;
        }
      }
      if (failure > 1) {
        write(STDERR_FILENO, "Redirection misformatted.\n", 26);
        freeblocks(argv2);
        goto interactive;
      }
    }

    // EXECUTE INPUTS
    child = fork();
    if (child == 0) {
      if (redirection) {
        DIR* dir = opendir(command[redirection + 1]);
        if (dir != NULL) {
          write(STDERR_FILENO, "Cannot write to file ", 21);
          int templ = strlen(command[redirection + 1]);
          write(STDERR_FILENO, command[redirection + 1], templ);
          write(STDERR_FILENO, ".\n", 2);
          _exit(1);
        }
        close(1);
        fopen(command[redirection + 1], "w");
      }
      int asdf = execv(command[0], argv2);
      if (asdf == -1) {
        write(2, command[0], strlen(command[0]));
        write(2, ": Command not found.\n", 21);
        freeblocks(argv2);;
        _exit(1);
      }
    } else {
      for (int j = 0; j < 100; j++) {
        free(argv2[j]);
        argv2[j] = NULL;
      }
      wait(NULL);
        goto interactive;
    }
    goto interactive;
  }

  batch:
  {
    // RESET MEMORY AND DISPLAY PROMPT
    char* argv2[100];
    memset(input, 0, 512);
    for (int i = 0; i < 100; i++) {
      memset(command[i], 0, 540);
      argv2[i] = NULL;
    }

    // READ INPUT
    if ((check = fgets(input, 512, file)) == NULL) {
      goto end;
    }
    if (strcmp(input, exitMsg) == 0) {
      write(1, "exit\n", 5);
      goto end;
    }

    write(1, input, strlen(input));

    // SANITIZE INPUT
    sanitize(input);

    // CHECK 0: EMPTY INPUT
    if (strlen(input) == 0) {
      goto batch;
      }

    // CHECK 1: > BEGINNING INPUT
    if (input[0] == '>') {
      write(STDERR_FILENO, "Redirection misformatted.\n", 26);
      goto batch;
    }

    // CHECK 2: SPACES ONLY INPUT
    int spacecheck = 0;
    for (int i = 0; i < strlen(input); i++) {
      if (input[i] != 32) {
        spacecheck = 1;
        break;
      }
    }
    if (spacecheck == 0) {
      goto batch;
    }

    // SEPARATE INPUT COMMANDS
    check = strtok(input, " ");
    strncpy(command[0], check, strlen(check));
    index = 1;
    while ((check = strtok(NULL, " ")) != NULL && index < 100) {
      strncpy(command[index], check, strlen(check));
      index++;
    }
    check = strtok(command[index-1], ">");
    while ((check = strtok(NULL, ">")) != NULL && index < 100) {
      strncpy(command[index], ">\0", 2);
        strncpy(command[index + 1], check, strlen(check) + 1);
    }
    if (command[index - 1][0] == '>' && command[index - 1][1] != 0) {
      check = strtok(command[index-1], ">");
      strncpy(command[index], check, strlen(check));
      strncpy(command[index - 1], ">\0", 2);
    }

    // COPY DATA
    int i = 0;
    while (command[i][0] != 0 && command[i][0] != '>' && i < 100) {
      argv2[i] = malloc(strlen(command[i]) + 1);
      strncpy(argv2[i], command[i], strlen(command[i]) + 1);
      i++;
    }

    // INTERPRET DATA AND REDIRECTION
    int redirection = 0;
    while (command[i][0] != 0) {
      if (command[i][0] == '>') {
        redirection = i;
      }
      i++;
    }
    if (redirection) {
      // IMPROPER REDIRECTION CHECK
      if (command[redirection + 1][0] == '>'
          || command[redirection + 2][0] != 0
          || command[redirection + 1][0] == 0) {
        write(STDERR_FILENO, "Redirection misformatted.\n", 26);
        freeblocks(argv2);
        goto batch;
      }
      int failure = 0;
      for (int i = 0; i < 100; i++) {
        if (command[i][0] == '>') {
          failure++;
        }
      }
      if (failure > 1) {
        write(STDERR_FILENO, "Redirection misformatted.\n", 26);
        freeblocks(argv2);
        goto batch;
      }
    }

    child = fork();
    if (child == 0) {
      if (redirection) {
        DIR* dir = opendir(command[redirection + 1]);
        if (dir != NULL) {
          write(STDERR_FILENO, "Cannot write to file ", 21);
          int tmpl = strlen(command[redirection + 1]);
          write(STDERR_FILENO, command[redirection + 1], tmpl);
          write(STDERR_FILENO, ".\n", 2);
          _exit(1);
        }
        close(1);
        fopen(command[redirection + 1], "w");
      }
      int asdf = execv(command[0], argv2);
      if (asdf == -1) {
        write(2, command[0], strlen(command[0]));
        write(2, ": Command not found.\n", 21);
        fclose(file);
        freeblocks(argv2);
        _exit(1);
      }
    } else {
      wait(NULL);
        for (int j = 0; j < 100; j++) {
          free(argv2[j]);
          argv2[j] = NULL;
        }
        goto batch;
    }
    goto batch;
  }

  end:
  {
    if (file != NULL) {
       fclose(file);
    }
    return 0;
  }
  fclose(file);
  exit(1);
}
