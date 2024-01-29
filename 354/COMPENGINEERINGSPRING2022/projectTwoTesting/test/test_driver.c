#include "enigma.h"

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

int main() {
    char message[80];
    char encrypted_message[80];
    char decrypted_message[80];
    char which_rotors[5];
    char encryption_rotors[4][27];
    int rotations;
    int num_active_rotors;

    //  printf("Enter the message to be encrypted or decrypted: ");
    Get_Message(message);

    //  printf("\nWhich rotors will be used to encrypt the message: ");
    num_active_rotors = Get_Which_Rotors(which_rotors); 

    //  printf("\nEnter the number of rotations to apply to the encryption rotors: ");
    rotations = Get_Rotations();

    Set_Up_Rotors(encryption_rotors, which_rotors);
    Apply_Rotation(rotations, encryption_rotors);
    Encrypt(encryption_rotors, num_active_rotors, message, encrypted_message);
    Decrypt(encryption_rotors, num_active_rotors, encrypted_message, decrypted_message);
    //  printf("The encrypted message is: %s", encrypted_message);
    //  printf("The decrypted message is: %s", decrypted_message);
    int i;

    printf("\n==Driver Test==\n");
    if( compare_strings( decrypted_message, message ) ) 
        printf( "Correct Decryption\n" );
    else
        printf( "Wrong Output - %s vs %s\n", decrypted_message, message );


    return 0;
}
