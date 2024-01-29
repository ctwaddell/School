/* Casey Waddell
 * ctwaddell@wisc.edu
*/

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"

//WORKS
int Array_Count(char str[])
{
  int i = 0;
  while(str[i] != '\0')
    {
      i++;
    }
  return i;
}

//WORKS
void kcprint(char str[])
{
  int limit = Array_Count(str);
  printf("\n\n");
  for(int i = 0; i < limit; i++)
    {
      printf("%c", str[i]);
    }
  
}

//WORKS
void Clean_Whitespace(char str[])
{
  int stringYet = 0;
  int i = 0;
  int j = 0;
  char str2[1000];

  while(str[j] != '\0')
    {
      if(str[j] == '\t' || str[j] == '\n') //char is a tab or newline, skip it
	{
	  // printf("SKIP!");
	  j++;
	  continue;
	}
      if(str[j] == ' ') //char is a space
	{
	  if(stringYet == 1) //within the string
	    {
	      if(str[j+1] == ' ') //and the next char is also a space, skip it
		{
		  j++;
		  continue;
		}
	      else //and the next char isnt a space, add it
		{
		  str2[i] = str[j];
		  i++;
		  j++;
		  continue;
		}
	    }
	  else //outside of the string, skip it
	    {
	      j++;
	      continue;
	    }
	}
      else //char is anything else, add it
	{
	  stringYet = 1;
	  str2[i] = str[j];
	  i++;
	  j++;
	  continue;
	}
    }

  for(j = 0; j < i; j++) //copy new spacing into old array
    {
      str[j] = str2[j];
    }

  str[i] = '\0'; //set new endpoint
  
  return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */
//WORKS
void Fix_Case(char str[])
{
  char tempStorage;
  int i = 0;

  if(str[i] >= 97 && str[i] <= 122)
    {
      tempStorage = str[i];
      tempStorage -= 32;
      str[i] = tempStorage;
    }
  i++;

  while(str[i] != '\0')
    {
      if(str[i] >= 65 && str[i] <= 90)
	{
	  if(str[i-1] == ' ')
	    {
	      i++;
	      continue;
	    }
	  else
	    {
	      tempStorage = str[i];
	      tempStorage += 32;
	      str[i] = tempStorage;
	      i++;
	      continue;
	    }
	}
	else if(str[i] >= 97 && str[i] <= 122)
	{
	  if(str[i-1] == ' ')
	    {
	      tempStorage = str[i];
	      tempStorage -= 32;
	      str[i] = tempStorage;
	      i++;
	      continue;
	    }
	  else
	    {
	      i++;
	      continue;
	    }
	}
      else
	{
	  i++;
	  continue;
	}
      
    }
  return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
//WORKS
int String_To_Year(char str[])
{ 
  int a; 
  a = atoi(str);
  return a;
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
//WORKS
void Director_Last_Name(char str[])
{
  int resumeIndex = 0;
  int newSize;
  int strSize = Array_Count(str);
  int oneWord = 1;
  
  //printf("%s", str);
  
  for(int i = strSize; i > 0; i--)
    {
      if(str[i] == ' ')
	{
	  resumeIndex = (i+1);
	  newSize = (strSize - i - 1);
	  oneWord = 0;
	  break;
	}
    }

  if(oneWord == 1)
  {
    return;
  }
  
  for(int j = 0; j < newSize; j++)
    {
      str[j] = str[resumeIndex + j];
    }
  str[newSize] = '\0';
  //  printf("2: %s\n", str);
  return;
}


/* this function takes the a string and returns
 * the floating point equivalent
 */
//WORKS
float String_To_Rating(char str[])
{
  float rating = -1.0;
  int i;
  float digit;

  if(str[1] == '.') //single digit score
    {
      rating = 0;
      i = str[0];
      i -= 48;
      rating += i;
      i = str[2];
      i -= 48;
      digit = ((float)i) / 10;
      rating += digit;
    }
  else if(str[2] == '.') //double digit score / perfect 10
    {
      rating = 10.0;
    }
  else
    {
      i = atoi(str);
      rating = i;
    }
  return rating;
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
//WORKS
long long String_To_Dollars(char str[])
{
  int strSize = Array_Count(str);
  int tempRev;
  long long revenue;
  
  for(int i = 0; i < strSize; i++)
    {
      if(str[i] == 'M' || str[i] == 'm') // the revenue is in millions
	{
          str[i] = '\0';
	  tempRev = atoi(str);
	  revenue = tempRev * 1000000;
	  return revenue;
	}
      if(str[i] == 'K' || str[i] == 'k') // the revenue is in thousands
	{
	  str[i] = '\0';
	  revenue = atoi(str);
	  revenue*=1000;\
	  return revenue;
	}
    }
  revenue = atoi(str);
  return revenue;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10])
{
  int i = 0;
  int k = 0;
  int localMovies = num_movies;
  char tempArray[64];
  int tempIndex = 0;
  float tempRating = 0.0;
  long long revenue = 0;
  /*
  int s = Array_Count(csv);
  printf("%d", localMovies);
  for(int u = 0; u < s; u++)
    {
      printf("%s", csv[u]);
      printf("\n");
    }
  */
  for(int j = 0; j < localMovies; j++) //traverse each one dimensional array and figure it out
    {
      //  printf("\n\nloop no: %d", j);
      k = 0;
      Clean_Whitespace(csv[j]);
      Fix_Case(csv[j]);
      tempIndex = 0;
      while(csv[j][k] != ',')  //copy title - WORKS
	{
	  titles[j][tempIndex] = csv[j][k];
	  tempIndex++;
	  k++;
	}
      k += 2;
      tempIndex = 0;

	  
      while(csv[j][k] != ',') //copy year - WORKS
	{
	  for(int m = k; m < (k+4); m++)
	    {
	      tempArray[tempIndex] = csv[j][m];
	      tempIndex++;
	    }
	  tempArray[tempIndex] = '\0';
	  i = String_To_Year(tempArray);
	  years[j] = i;
	  k += 4;
	}
      k += 2;
      tempIndex = 0;
      
      
      while(csv[j][k] != ',') //ignore runtime
	{
	  k++;
	}
      k += 2;
      i = 0;
      
      
      while(csv[j][k] != ',') //copy directors - WORKS
	{
	  tempArray[i] = csv[j][k];
	  i++;
	  k++;
	}
      tempArray[i] = '\0';
      i = 0;
      Director_Last_Name(tempArray);
      while(tempArray[i] != '\0')
	{
	  directors[j][i] = tempArray[i];
	  i++;
	}
      k += 2;
      i = 0;
      tempIndex = 0;
      
      
      while(csv[j][k] != ',') //copy rating - WORKS
	{
	  tempArray[i] = csv[j][k];
	  i++;
	  k++;
	}
      tempArray[i] = '\0';
      i = 0;
      tempRating = String_To_Rating(tempArray);
      ratings[j] = tempRating;
      k += 2;
      tempIndex = 0;
      
      
      while(csv[j][k] != ',' && csv[j][k] != '\0') //copy dollars - WORKS
	{
	  for(int n = k; n < (k + 10); n++)
	    {
	      if(csv[j][n] != '\n' && csv[j][n] != '\0')
		{
		  tempArray[tempIndex] = csv[j][n];
		  tempIndex++;
		}
	      else
		{
		  break;
		}
	    }
	  tempArray[tempIndex + 1] = '\0';
	  revenue = String_To_Dollars(tempArray);
	  dollars[j] = revenue;
	  break;
	}
      /*      printf("\ngrand summary:\n");
      printf("%s\n", titles[j]);
      printf("%d\n", years[j]);
      printf("%s\n", directors[j]);
      printf("%f\n", ratings[j]);
      printf("%lld\n", dollars[j]);
      */
    }
  return;
}



/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10])
{
  int arraySize;
  int longestTitle;
  int longestDirector;
  
  arraySize = Array_Count(titles[0]);
  for(int i = 0; i < num_movies; i++) //longest title
    {
      if(Array_Count(titles[i]) > arraySize)
	{
	  arraySize = Array_Count(titles[i]);
	}
    }
  longestTitle = arraySize;
  longestTitle += 2;
  if(longestTitle < 7)
    {
      longestTitle = 7;
    }
  
  arraySize = Array_Count(directors[0]);
  for(int i = 0; i < num_movies; i++) //longest director
    {
      if(Array_Count(directors[i]) > arraySize)
	{
	  arraySize = Array_Count(directors[i]);
	}
    }
  longestDirector = arraySize;
  longestDirector += 2;
  if(longestDirector < 10)
    {
      longestDirector = 10;
    }
  
  printf("%-3s", "Id");
  printf("%-*s", longestTitle, "Title");
  printf("%-6s", "Year");
  printf("%-*s", longestDirector, "Director");
  printf("%6s", "Rating");
  printf("%11s", "Revenue");
  printf("\n");

  for(int i = 0; i < num_movies; i++)
    {
      printf("%-3d", (i+1)); //ID
      printf("%-*s", longestTitle, titles[i]); //TITLE
      printf("%-6d", years[i]); //YEAR
      printf("%-*s", longestDirector, directors[i]); //DIRECTOR
      printf("%6.1f", ratings[i]); //RATING
      printf("%11lld", dollars[i]); //REVENUE
      printf("\n");
    }
  return;
}
