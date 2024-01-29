long pointerStuff(long *xp, long y)
{
  long x = *xp;
  *xp = y;
  return x;
}


int main()
{
  long* swag;
  long y = 7;
  long new = pointerStuff(swag, y);
  
}
