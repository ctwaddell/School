 #include <stdio.h>
  
 int * modify(int * b){
       int q = 3;
       b = &q;
       return b;
   }
  
  int main(){
         int a = 2;
         int * b = &a;
         int * c = &a;
         modify(b);
         printf("%d\n", *b);
 
    }
