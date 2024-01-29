#include "enigma.h"
#include "enigma_sol.h"

int main() {
    // Boilerplate definitions for all variables
    char message[80];
    char encrypted_message[80], sol_encrypted_message[80];
    char which_rotors[5];
    char encryption_rotors[4][27];
    int rotations;
    int num_active_rotors;

    test_GM( message );
    num_active_rotors   =   test_GWR( which_rotors );
    rotations           =   test_GR();
    test_SUR( encryption_rotors, which_rotors );
    test_AR( rotations, encryption_rotors );
    test_E( encryption_rotors, num_active_rotors, message, sol_encrypted_message );
    Encrypt( encryption_rotors, num_active_rotors, message, encrypted_message );

    printf("\n==E Test==\n");
    if( compare_strings( encrypted_message, sol_encrypted_message ) )
        printf( "Correct Encryption\n" );
    else
        printf("Wrong Output Encryption - %s vs %s\n", encrypted_message, sol_encrypted_message );

    return 0;
}
