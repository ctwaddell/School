#include "user.h"
#include "types.h"
#include "stat.h"

int main(void)
{
  int a = 2//nice(2);
  int b = 1;//getschedstate(2);
  cprintf("!%d", a);
  cprintf("$%d", b);
  return 0;
}
