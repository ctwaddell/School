#include <stdio.h>
#include <string.h>


void To_Upper(char *str);
  
int main() {
    char str[20];
    strcpy(str, "cs 354 is Awesome!");
    printf("Original string:   %s\n",str);
    To_Upper(str);
    printf("\n");
    printf("Upper case string: %s\n",str);
    char str2[20];
    strcpy(str2, "");
    printf("Original string:   %s\n",str2);
    To_Upper(str2);
    printf("\n");
    printf("Upper case string: %s\n",str2);
    char str3[2];
    strcpy(str3, "c");
    printf("Original string:   %s\n",str3);
    To_Upper(str3);
    printf("\n");
    printf("Upper case string: %s\n",str3);
    char str4[150];
    strcpy(str4, "cs 354 is Awesome!aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    printf("Original string:   %s\n",str4);
    To_Upper(str4);
    printf("\n");
    printf("Upper case string: %s\n",str4);
    char str5[20];
    strcpy(str5, "cdP{cd''asdfj1`23");
    printf("Original string:   %s\n",str5);
    To_Upper(str5);
    printf("\n");
    printf("Upper case string: %s\n",str5);
    printf("BLAYBOYSWAG");
    printf("\nBLAYBOYSWAG");
    char* nullstring = NULL;
    To_Upper(nullstring);
    printf("souljah boy tellem");
    printf("\n");
    printf("Upper case string: %s\n",nullstring);
    return 0;
}



