#include "enigma.h"
#include <stdio.h>

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // 1
        "AJDKSIRUXBLHWTMCQGZNPYFVOE", // 2
        "BDFHJLCPRTXVZNYEIWGAKMUSQO", // 3
        "ESOVPZJAYQUIRHXLNFTGKDCMWB", // 4
        "VZBRGITYUPSDNHLXAWMJQOFECK", // 5
        "JPGVOUMFYQBENHZRDKASXLICTW", // 6
        "NZJHGRCXMYSWBOUFAIVLPEKQDT", // 7
        "FKQHTLXOCBJSPDZRAMEWNIUYGV", // 8
       //01234567890123456789012345
       //0         1         2
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[])
{
  char c = '0';
  int i = 0;
  
  while(c != '\n' && i < 80)
    {
      c = getchar();
      if(c > 96 && c < 123)
	{
	  c -= 32;
	}
      msg[i] = c;
      i++;
    }

  msg[i] = '\0';
  
  return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[])
{
  char c = '0';
  int i = 0;

  char temp[100] = {'\0'};

  while(c != '\n')
  {
    c = getchar();
    if(c == '\n')
      {
	break;
      }
    temp[i] = c;
    i++;
  }

  for(int j = 0; j < 5; j++)
    {
      which_rotors[j] = temp[j];
    }
  
  which_rotors[4] = '\0';

  if(i > 4)
    {
      i = 4;
    }
  
  return i; //i or --i?
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations()
{
  char c = '0';
  char str[3];
  int i = 0;
  
  while(c != '\n' && i < 2)
  {
    c = getchar();
    str[i] = c;
    i++;
  }
  str[2] = '\0';

  int d = atoi(str);
  d = d % 26;

  printf("\nBIGSWAG: %d\n", d);
  return d;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5])
{ 
  int int_rotors[5];
  int size = 0;
  char temp;
  char *nextChar;
  
  for(int j = 0; j < 5; j++)
    {
      if(which_rotors[j] == '\0')
	{
	  break;
	}
      else
	{
	  temp = which_rotors[j];
	  int_rotors[j] = temp - '0';
	  size++;
	}
    }
  
  //nextChar = ROTOR_CONSTANTS[1];

  //char a = *ROTOR_CONSTANTS[2];
  
  for(int k = 0; k < size; k++)
  {
    nextChar = ROTOR_CONSTANTS[int_rotors[k]];
    for(int m = 0; m < 27; m++)
      {
	encryption_rotors[k][m] = *nextChar;
	nextChar++;
      }
  }
  
  return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27])
{
  char copy[27];
  int diff = (26 - rotations);

  //ROTATES THE WRONG WAY
  
  copy[27] = '\0';

  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 27; j++)
	{
	  copy[j] = encryption_rotors[i][j];
	}
      for(int k = 0; k < rotations; k++)
	{
	  encryption_rotors[i][k] = copy[k + diff];
	}
      for(int l = 0; l < diff; l++)
	{
	  encryption_rotors[i][l + rotations] = copy[l]; 
	} 
    }
  /* 
  printf("\n%s\n", encryption_rotors[0]);
  printf("\n%s\n", encryption_rotors[1]);
  printf("\n%s\n", encryption_rotors[2]);
  printf("\n%s\n", encryption_rotors[3]);
  */
  return;
}

char Encrypt_Helper(char ichar, char base[], char encrypt[])
{
  char rchar;
  int index = 0;
    
  if(ichar < 65 || ichar > 90)
    {
      return ichar;
    }
  
  for(int i = 0; i < 27; i++)
    {
      if(base[i] == ichar)
	{
	  break;
	}
      index++;
    }

  rchar = encrypt[index];

  return rchar;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[])
{
  char base_rotor[27];  
  char* nextChar = ROTOR_CONSTANTS[0];

  for(int i = 0; i < 27; i++)
    {
      base_rotor[i] = *nextChar;
      nextChar++;
    }
  base_rotor[27] = '\0';

  for(int i = 0; i < 80; i++)
    {
      encrypted_msg[i] = msg[i];
    }

  for(int j = 0; j < num_active_rotors; j++)
    {
      for(int i = 0; i < 80; i++)
	{
	  encrypted_msg[i] = Encrypt_Helper(encrypted_msg[i], base_rotor, encryption_rotors[j]);
	}
    }
  
  return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[])
{
  char base_rotor[27];
  char* nextChar = ROTOR_CONSTANTS[0];

  for(int i = 0; i < 27; i++)
    {
      base_rotor[i] = *nextChar;
      nextChar++;
    }
  base_rotor[27] = '\0';

  for(int i = 0; i < 80; i++)
    {
      decrypted_msg[i] = encrypted_msg[i];
    }

  for(int j = (num_active_rotors - 1); j >= 0; j--)
    {
      for(int i = 0; i < 80; i++)
	{
	  decrypted_msg[i] = Encrypt_Helper(decrypted_msg[i], encryption_rotors[j], base_rotor);
	}
    }
  
  return;
}


