#include <stdio.h>
#include "student_functions.h"

void Clean_Whitespace_soln(char str[]) {
    //for (int i = 0; i<30; i++) printf("%d  %c %d\n",i,str[i],str[i]);
    // remove leading whitespace
    char *p = str, *q = str;
    while (*p == ' ' || *p == '\t' || *p == '\n') p++; // advance pointer p to the first character
    while ((*q++ = *p++)); // copy the rest of the string
    
    //for (int i = 0; i<30; i++) printf("%d  %c %d\n",i,str[i],str[i]);
    // remove trailing whitespace
    q--; // start with the null character 
    while (*q == ' ' || *q == '\t' || *q == '\n' || *q == '\0') {
        // printf("%c %d\n",*q, *q);
        q--; // advance pointer p to the last character
    }
    q++; 
    *q = '\0'; // replace last whitespace with null
// */

    //for (int i = 0; i<30; i++) printf("%d  %c %d\n",i,str[i],str[i]);
    // fix internal spaces
    p = str; q = str; p++; q++; // start with second character
    while (*p) {
        if (*p == ' ' && *(p-1) == ' ') {p++; continue;}
        *q = *p; q++; p++; // copy the character
    }
    *q = *p; // copy the \0
    
    //for (int i = 0; i<30; i++) printf("%d  %c %d\n",i,str[i],str[i]);
    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case_soln(char str[]) {
    // all lower
    char *p = str;
    while (*p) {
        if (*p >= 'A' && *p <= 'Z')
            *p = *p + 'a'-'A';
        p++;
    }
    
    // upper case first character
    p = str; *p = *p + 'A'-'a';

    // upper case every character after a space
    p++; // begin with second character
    while (*p) {
        if (*(p-1) == ' ') *p = *p + 'A'-'a';
        p++;
    }
    return;
}

void Read_CSV(char *filename, char csv[10][1024], int *num_movies) {    
    FILE *fp;
    fp = fopen(filename, "r");
    fscanf(fp, "%d", num_movies);
    char read_rest_of_line[1024];
    fgets(read_rest_of_line, 1024, fp);
    for (int i=0; i<*num_movies; i++) 
        fgets(csv[i], 1024, fp);
    fclose(fp);
    return;
}

void Director_Last_Name_soln(char str[]) {
    // printf("function: %s\n",str);
    Clean_Whitespace(str); // may not be needed
    // printf("function: %s\n",str);
    char *p = str, *last_space = str-1;
    while (*p++) if (*p == ' ') last_space = p; // find the last space
    last_space++; // advance to the first letter of the last name
    p = str; // reset to first character
    while ((*p++ = *last_space++)); // copy the director name to the front of the string
    // printf("function: %s\n",str);
    return;
}

int Length_Of_Longest_String_soln(char str[10][1024], int num_movies) {
    int longest=0;
    for (int i = 0; i<num_movies; i++) {
        char *p = str[i];
        int n = 0;
        while (*p++) n++;
        if (n>longest) longest = n;
    }
    return longest;
}

void Print_Table_Soln(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    
    for(int x = 0; x < num_movies; x++){
        Clean_Whitespace_soln(titles[x]);
        Fix_Case_soln(titles[x]);
        Clean_Whitespace_soln(directors[x]);
        Fix_Case_soln(directors[x]);
        Director_Last_Name_soln(directors[x]);
    }
    
    int title_length = Length_Of_Longest_String_soln(titles, num_movies)+2;
    if (title_length < 7) title_length = 7;

    int director_length = Length_Of_Longest_String_soln(directors, num_movies)+2;
    if (director_length < 10) director_length = 10;

    // print the header
    printf("%-3s%-*s%-6s%-*s%6s%11s\n","Id",title_length,"Title","Year",director_length,"Director","Rating","Revenue");    
    for (int i = 0; i<num_movies; i++) {        
        printf("%-3d%-*s%-6d%-*s%6.1f%11lld\n",i+1,title_length,titles[i],years[i],director_length,directors[i],ratings[i],dollars[i]);    
    }

    return;
}


int main() {

    char csv[10][1024]; // data structure for the entire movie csv file
    int num_movies;
    char titles[10][1024];
    int years[10];
    char directors[10][1024];
    float ratings[10];
    long long dollars[10];
    
    char csv_file[256];
    scanf("%[^\n]", csv_file);
     
    Read_CSV(csv_file, csv, &num_movies);
    Split(csv, num_movies, titles, years, directors, ratings, dollars);
    Print_Table_Soln(num_movies, titles, years, directors, ratings, dollars);

    return 0;
}
