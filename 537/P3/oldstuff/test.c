#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  char buffer[256];

  printf("Enter a line of text: ");
  fflush(stdout); // Ensure the prompt is displayed

  if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    printf("You entered: %s", buffer);

    // Wait for 2 seconds
    sleep(2);

    printf("After 2 seconds: %s", buffer);
  }

  return 0;
}
