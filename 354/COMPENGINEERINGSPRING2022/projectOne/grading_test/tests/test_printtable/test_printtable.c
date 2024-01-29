#include <stdio.h>
#include <stdlib.h>
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

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year_soln(char str[]) {
    return atoi(str);
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name_soln(char str[]) {
    // printf("function: %s\n",str);
    Clean_Whitespace_soln(str); // may not be needed
    // printf("function: %s\n",str);
    char *p = str, *last_space = str-1;
    while (*p++) if (*p == ' ') last_space = p; // find the last space
    last_space++; // advance to the first letter of the last name
    p = str; // reset to first character
    while ((*p++ = *last_space++)); // copy the director name to the front of the string
    // printf("function: %s\n",str);
    return;
}


/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating_soln(char str[]) {
    // do your work here
    return atof(str);
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars_soln(char str[])  {
    long long result = atoll(str);
    char *p = str;
    while (*p < 'A') p++;
    // printf("string to dollars: char = %c\n",*p);
    if (*p == 'M' || *p == 'm') result *= 1000000;
    if (*p == 'K' || *p == 'k') result *= 1000;
    return result;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split_soln(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    // printf ("\nFUNCTION SPLIT\n");

    char temp_str[1024];
    for (int i = 0; i < num_movies; i++) {
        char *row = csv[i];
        char *t = titles[i];
        char *d = directors[i];
        char *temp=temp_str;

        // title
        while (*row != ',') {*t = *row; t++; row++;} row++; // copy the title, skip comma
        *t = '\0'; // add null to string
        Clean_Whitespace_soln(titles[i]);
        Fix_Case_soln(titles[i]);
        // printf("Title = %s\n",titles[i]);

        // year
        while (*row != ',') {*temp = *row; temp++; row++;} row++; // copy the year, skip comma
        *temp = '\0'; // add null to string
        years[i] = String_To_Year_soln(temp_str); row++; // store year in array as int
        temp=temp_str; // reset temp_str
        // printf("Year = %d\n",years[i]);
        
        // runtime
        while (*row != ',') {*temp = *row; temp++; row++;} row++; // copy the runtime, skip comma
        temp=temp_str; // ignore runtime, reset temp_str
        
        // director 
        while (*row != ',') {*d = *row; d++; row++;} row++; // copy the director last name, skip comma
        *d = '\0'; // add null to string
        Clean_Whitespace_soln(directors[i]);
        Fix_Case_soln(directors[i]);
        Director_Last_Name_soln(directors[i]);
        // printf("Director = %s\n",directors[i]);

        // rating
        while (*row != ',') {*temp = *row; temp++; row++;} row++; // copy the rating to temp, skip comma
        *temp = '\0'; // add null to string
        ratings[i] = String_To_Rating_soln(temp_str); // conver to float and store
        temp = temp_str; // reset temp_str 
        // printf("Rating = %f\n",ratings[i]);
        
        // revenue 
        while (*row != '\0') {*temp = *row; temp++; row++;} row++; // copy the dollars last name,
        *temp = '\0'; // add null to string
        dollars[i] = String_To_Dollars_soln(temp_str);
        // printf("Revenue = %lld\n",dollars[i]);
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
    Split_soln(csv, num_movies, titles, years, directors, ratings, dollars);
    Print_Table(num_movies, titles, years, directors, ratings, dollars);

    return 0;
}
