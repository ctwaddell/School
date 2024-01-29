#include "types.h"
#include "stat.h"
#include "user.h"
#include "psched.h"

int main()
{
  struct pschedinfo sch;
  int a = nice(7);
  int d = sch.priority[0];
  int b = getschedstate(&sch);
  int c = sch.priority[0];
  int e = sch.ticks[1];
  printf(1, "%d, %d, %d, %d, !%d!", a, b, c, d, e);
  exit();
}
