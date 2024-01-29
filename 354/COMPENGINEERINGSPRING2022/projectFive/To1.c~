#include <stdio.h>
void ToUpper(char* str)
{
  int i = 0;
  while(str[i] != '\0')
    {
      if(str[i] >= 97 && str[i] <=122)
	{
	  str[i] -= 32;
	}
      i++;
    }
}

int main()
{
  char swag[] = "asdf123asdf a$#s\tdf";
  ToUpper(swag);
  printf("%s", swag);
}
