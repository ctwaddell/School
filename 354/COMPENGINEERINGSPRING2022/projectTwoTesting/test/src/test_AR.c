#include "enigma.h"
#include "enigma_sol.h"

int main() {
    // Boilerplate definitions for all variables
   
    char which_rotors[5];
    char encryption_rotors[4][27], sol_encryption_rotors[4][27];
    int num_active_rotors, rotations;

    //  Setup both encryp as well as sol, modify one using
    //  candidate solution and one using target solution 
    //  and compare
    num_active_rotors   =   test_GWR( which_rotors );
    Set_Up_Rotors( encryption_rotors, which_rotors );
    Set_Up_Rotors( sol_encryption_rotors, which_rotors );

    rotations           =   test_GR();
    test_AR( rotations, sol_encryption_rotors );
    Apply_Rotation( rotations, encryption_rotors );

    int i, j;

    printf("\n==AR Test==\n");
    for( i = 0; i < num_active_rotors; i++ )
    {
        for( j = 0; j < 27; j++ )
        {
            if( encryption_rotors[i][j] != sol_encryption_rotors[i][j] )
                break;
        }
        if( j != 27 )
        {
            printf("Wrong Rotation - Differs in rotor %d\n", i );
            break;
        }
    }

    if( i == num_active_rotors )
        printf("Correct Rotation\n");

    return 0;
}
