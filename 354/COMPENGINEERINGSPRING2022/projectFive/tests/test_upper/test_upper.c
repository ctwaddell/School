#include <stdio.h>
#include <string.h>
void To_Upper(char *str);

int main() {
    char str[9000];
    scanf("%s", str);
    To_Upper(str);
    printf("%s", str);
    return 0;
}
