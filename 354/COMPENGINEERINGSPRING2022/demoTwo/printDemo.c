#include <stdio.h>

int main()
{
  char c = 'a';
  printf("The character is %c %d %x \n", c, c, c);
  c = c + 1;
  printf("The character is %c %d %x \n", c, c, c);
  c = c - ('a' - 'A'); //minus 32 in decimal to convert to uppercase
  printf("The character is %c %d %x \n", c, c, c);


  {
    char garbage[] = "as;dlkfjasdfk;asdflksajdf";
  }
  
  //no string class
  //how to declare an array; char is the type of array, str is the name, the [] indicates its an array, the 5 indicates size
  char str[5] = "CS354";
  //  str[3] = '\0';
  //char str2[] = {'C', 'S', '3', '5', '4', '\0'};

  printf("%s \n", str);
  
  return 0;

}

