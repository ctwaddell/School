#ifndef ENIGMA_SOL_H
#define ENIGMA_SOL_H 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG		0
#define dbgprintf(...)	if (DEBUG) {printf(__VA_ARGS__);}

const char *SOL_ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// Helper method to compare two strings for equality when there
// may or may not be a trailing newline character in the first
// string (but the second one will not have a newline)
int compare_strings( char first[], char second[] ){
    int max_size = 80; // we will work only with 80 length strings at most
    int size_f, size_s;

    // Compute the sizes of the string, ignoring trailing newline if any in first
    for( size_f = 0;  ( first[ size_f ] != '\n' && first[ size_f ] != '\0' ) && size_f < max_size ; size_f++ );
    for( size_s = 0;  ( second[ size_s ] != '\0' ) && size_s < max_size ; size_s++ );

    if( size_f != size_s )
        return 0;

    for( int i = 0; i < size_f; i++ )
    {
        if( first[i] != second[i] )
            return 0;
    }

    return 1;
}


// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void test_GM(char msg[]){
    char* buffer;
    size_t max_size = 81; //81 as max size is 80(msg) + 1('\n')
    size_t num_characters_read;

    buffer = (char *)malloc(max_size * sizeof(char));
    if( buffer == NULL)
    {
        dbgprintf("Malloc Failed\n");
        exit(1);
    }
    
    num_characters_read = getline(&buffer, &max_size, stdin);
    dbgprintf("Num of chars read inlcuding newline: %ld\n", num_characters_read);
    if (num_characters_read > 80) {
        dbgprintf("Amount of characters read is greater than msg max_size\n");
        exit(1);
    }

    int i=0;
    while(buffer[i] != '\n') {
        msg[i] = buffer[i];
        i++;
    }
    msg[i] = '\0';

    free(buffer);
    return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int test_GWR(char which_rotors[]){
    char* buffer;
    size_t max_size = 6; //6 as max size is 5(msg) + 1('\n')
    size_t num_characters_read;

    buffer = (char *)malloc(max_size * sizeof(char));
    if( buffer == NULL)
    {
        dbgprintf("Malloc Failed\n");
        exit(1);
    }

    num_characters_read = getline(&buffer, &max_size, stdin);
    dbgprintf("Num of chars read inlcuding newline: %ld\n", num_characters_read);
    if (num_characters_read > 5) {
        dbgprintf("Amount of characters read is greater than which_rotors max_size\n");
        exit(1);
    }

    int i = 0;
    while(buffer[i] != '\n') {
        which_rotors[i] = buffer[i];
        i++;
    }
    which_rotors[i] = '\0';

    // i will be number of active rotors as till index i we have valid num entries
    free(buffer);
    return i;
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int test_GR(){
    int num_rotations = 0;
    scanf("%d", &num_rotations);

    return num_rotations;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void test_SUR(char encryption_rotors[4][27], char which_rotors[5]){
    dbgprintf("Inside Set_Up_Rotors\n");

    int i = 0;
    // for every rotor number specified in which_rotors[]
    while (which_rotors[i] != '\0'){
        dbgprintf("i = %d\n", i);
        dbgprintf("which_rotors[i] = %d\n", which_rotors[i]);

        // get the rotor string
        const char * c = SOL_ROTOR_CONSTANTS[which_rotors[i] - '0'];
        dbgprintf("ROTOR_CONSTANTS %s\n", c);

        // copy to encryption_rotors
        for (int j = 0; j <= 26; j++){
            encryption_rotors[i][j] = c[j];
        }

        i++;
    }

    return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void test_AR(int rotations, char encryption_rotors[4][27]) {
    dbgprintf("Inside Apply_Rotation\n");
    int size1 = 26 - rotations + 1;

    // go through all encryption_rotors[]
    for (int i = 0; i < 4; i++){
        // divide the rotor string into 2 - one that gets pushed to the right
        // and the other that comes to the front 
        // eg. "BDFHJLCPRTXVZNYEIWGAKMUSQO" with rotations = 3
        // "BDFHJLCPRTXVZNYEIWGAKMU" is the part that gets pushed to the right (secondHalf)
        // "SQO" is the part that comes to the front (firstHalf)
        // then concatenate the first and second half

        // get the second half
        char secondHalf[size1];
        memset(secondHalf, 0, size1 * sizeof(char));
        strncpy(secondHalf, encryption_rotors[i], 26 - rotations);
        dbgprintf("secondHalf %s\n", secondHalf);

        // get the first half
        char rotatedString[27];
        memset(rotatedString, 0, 27 * sizeof(char));
        strncpy(rotatedString, encryption_rotors[i] + 26 - rotations, rotations);
        dbgprintf("firstHalf %s\n", rotatedString);

        // concatenate firstHalf and secondHalf
        strcat(rotatedString, secondHalf);
        for (int j = 0; j <= 26; j++){
            encryption_rotors[i][j] = rotatedString[j];
        }
        dbgprintf("rotatedString %s\n", rotatedString);
    }
    
    dbgprintf("Exiting Apply_Rotation\n");
    return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void test_E(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
    strcpy(encrypted_msg, msg);
    for (int i = 0; i < num_active_rotors; i++)
        for (int j = 0; j < strlen(msg); j++) {
            int pos = encrypted_msg[j] - 'A';
            if (pos >=0 && pos <= 26)
            {
                dbgprintf("Changing from %c:", encrypted_msg[j]);
                encrypted_msg[j] = encryption_rotors[i][pos];
                dbgprintf("To %c:\n", encrypted_msg[j]);
            }
        }
    return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void test_D(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
    for(int i = 0; i < num_active_rotors; i++)
        dbgprintf("Rotor :%d - %s\n", i, encryption_rotors[i]);
    strcpy(decrypted_msg, encrypted_msg);
    for (int i = num_active_rotors - 1; i >= 0; i--)
        for (int j = 0; j < strlen(encrypted_msg); j++) {
            char *temp = strchr(encryption_rotors[i], decrypted_msg[j]);
            if (temp != NULL){
                int pos = temp - encryption_rotors[i];
                if (pos >=0 && pos <= 26)
                    decrypted_msg[j] = SOL_ROTOR_CONSTANTS[0][pos];
            }
        }
    return;
}

#endif
