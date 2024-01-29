#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
  int a = nice();
  int b = getschedstate();
  printf(1, "%d, %d", a, b);
  return 0;
}
