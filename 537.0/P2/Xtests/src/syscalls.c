#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char* argv[])
{
  int total = atoi(argv[1]);
  int success = atoi(argv[2]);
  int swag = getpid();
  int calls = 0;
  int goodcalls = 0;
  int bad = total - success;
  
  for(int i = 0; i < success; i++)
  {
    getpid();
  }

  for(int j = 0; j < bad; j++)
  {
    kill(-1);
  }

  
  
  calls = getnumsyscalls(swag);
  goodcalls = getnumsyscallsgood(swag);
  calls--;
  goodcalls = calls - goodcalls; 
  printf(1, "%d, %d\n", calls, goodcalls);
    
  return(0);
}
