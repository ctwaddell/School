#include "types.h"
#include "user.h"
#include "stat.h"

int main()
{
  char swag[512];
  int a = getlastcat(swag);
  if(a)
    {
      printf(1, "XV6_TEST_OUTPUT -1");
    }
  else
    {
      printf(1, "XV6_TEST_OUTPUT Last catted filename: %s\n", swag);
      exit();
    }
}
