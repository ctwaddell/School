#include "enigma.h"
#include "enigma_sol.h"

int main() {
    // Boilerplate definitions for all variables
    char which_rotors[5];
    char encryption_rotors[4][27], sol_encryption_rotors[4][27];
    int num_active_rotors;

    num_active_rotors   =   test_GWR( which_rotors );
    test_SUR( sol_encryption_rotors, which_rotors );
    Set_Up_Rotors( encryption_rotors, which_rotors );

    printf("\n==SUR Test==\n");
    int i, j;
    for( i = 0; i < num_active_rotors; i++ )
    {
        for( j = 0; j < 27; j++ )
        {
            if( encryption_rotors[i][j] != sol_encryption_rotors[i][j] )
                break;
        }
        if( j != 27 )
        {
            printf("Wrong Setup - Differs in rotor %d\n", i );
            return 0;
        }
    }

    if( i == num_active_rotors ) 
        printf("Correct Setup\n");

    return 0;
}
