#include <stdlib.h>
#include <stdio.h>
#include "student_functions.c"

int main()
{
  float rating;
  char testArray[] = {'1', '3', '.', '3','\0'};
  rating = String_To_Rating(testArray);
  printf("%f \n", rating);
  return 0;
}  
