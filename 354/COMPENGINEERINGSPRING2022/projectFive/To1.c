#include <stdio.h>
void ToUpper(char* str)
{
  while(*str != '\0')
    {
      if(*str >= 97 && *str <=122)
	{
	  *str -= 32;
	}
      str++;
    }
}

int main()
{
  char swag[] = "asdf123asdf a$#s\tdf";
  ToUpper(swag);
  printf("%s", swag);
}
