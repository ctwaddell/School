#include <stdio.h>

struct point
{
  int x;
  int y;
};

struct rect
{
  struct point pt1;
  struct point pt2;
};
  
void Enlarge_Rectangle(struct rect* r, struct point p)
{
  if(p.x >= r->pt2.x && p.y >= r->pt2.y)
    {
      r->pt2.x = p.x;
      r->pt2.y = p.y;
      return;
    }
  else if(p.x <= r->pt1.x && p.y <= r->pt1.y)
    {
      r->pt1.x = p.x;
      r->pt1.y = p.y;
      return;
    }
  else
    {
      printf("POINT OUT OF BOUNDS\n");
      return;
    } 
}

void main()
{
  struct point p1 = {-1, -1};
  struct point p2 = {1, 1};
  struct rect r = {p1, p2};
  struct rect* rPointer = &r;
  printf("Bottom left = (%d, %d)\n", r.pt1.x, r.pt1.y);
  printf("Top right = (%d, %d)\n", r.pt2.x, r.pt2.y);
  struct point enlarge = {20, 22};
  printf("\nEnlarge point = (%d, %d)\n\nResult:\n", enlarge.x, enlarge.y);
  Enlarge_Rectangle(rPointer, enlarge);
  printf("Bottom left = (%d, %d)\n", r.pt1.x, r.pt1.y);
  printf("Top right = (%d, %d)\n", r.pt2.x, r.pt2.y);
  struct point enlarge2 = {-20, -22};
  printf("\nEnlarge point = (%d, %d)\n\nResult:\n", enlarge2.x, enlarge2.y);
  Enlarge_Rectangle(rPointer, enlarge2);
  printf("Bottom left = (%d, %d)\n", r.pt1.x, r.pt1.y);
  printf("Top right = (%d, %d)\n", r.pt2.x, r.pt2.y);
  struct point enlarge3 = {-20, 22};
  printf("\nEnlarge point = (%d, %d)\n\nResult:\n", enlarge3.x, enlarge3.y);
  Enlarge_Rectangle(rPointer, enlarge3);
  printf("Bottom left = (%d, %d)\n", r.pt1.x, r.pt1.y);
  printf("Top right = (%d, %d)\n", r.pt2.x, r.pt2.y);
  struct point enlarge4 = {20, -22};
  printf("\nEnlarge point = (%d, %d)\n\nResult:\n", enlarge4.x, enlarge4.y);
  Enlarge_Rectangle(rPointer, enlarge4);
  printf("Bottom left = (%d, %d)\n", r.pt1.x, r.pt1.y);
  printf("Top right = (%d, %d)\n", r.pt2.x, r.pt2.y);
  struct point enlarge5 = {1, 1};
  printf("\nEnlarge point = (%d, %d)\n\nResult:\n", enlarge5.x, enlarge5.y);
  Enlarge_Rectangle(rPointer, enlarge5);
  printf("Bottom left = (%d, %d)\n", r.pt1.x, r.pt1.y);
  printf("Top right = (%d, %d)\n", r.pt2.x, r.pt2.y);
}
