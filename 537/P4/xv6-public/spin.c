#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char* argv[])
{
  if(argc != 2) exit();

  int x = 0;
  for(int i = 1; i < atoi(argv[1]); i++)
    {
      x += i;
    }
  exit();
}
