#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void delayPrint(char s[], unsigned int delay) {
  unsigned int printDelay = delay;
  for(int i = 0; i < strlen(s); i++) {
    write(1, &s[i], 1);
    int a = usleep(printDelay);
  }
  write(1, "\n", 1);
}

int main(int argc, char* argv[]) {
  if(argc == 1) return 0;
  int del = atoi(argv[2]);
  delayPrint(argv[1], del);
  return 0;
  
}

