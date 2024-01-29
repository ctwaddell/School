void Reverse(char* str)
{
  char temp;
  char* begin = str;
  
  while(*str != '\0')
    {
      str++;
    }
  str--;

  while(str >= begin)
    {
      temp = *begin;
      *begin = *str;
      *str = temp;
      str--;
      begin++;
    }
}
