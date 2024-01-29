#include "enigma.h"
#include "enigma_sol.h"

int main() {
    // Boilerplate definitions for all variables
    char message[80];
    char encrypted_message[80];
    char decrypted_message[80], sol_decrypted_message[80];
    char which_rotors[5];
    char encryption_rotors[4][27];
    int rotations;
    int num_active_rotors;

    test_GM( message );
    num_active_rotors   =   test_GWR( which_rotors );
    rotations           =   test_GR();

    test_SUR( encryption_rotors, which_rotors );
    test_AR( rotations, encryption_rotors );
    test_E( encryption_rotors, num_active_rotors, message, encrypted_message );
    test_D( encryption_rotors, num_active_rotors, encrypted_message, sol_decrypted_message );
    Decrypt( encryption_rotors, num_active_rotors, encrypted_message, decrypted_message );
    
    printf("\n==D Test==\n");
    if( compare_strings( decrypted_message, sol_decrypted_message ) )
        printf("Correct Decryption\n");
    else
        printf("Wrong Output Decryption - %s vs %s\n", decrypted_message, sol_decrypted_message );

    return 0;
}
