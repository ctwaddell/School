#include "enigma.h"
#include "enigma_sol.h"

int main() {
    // Boilerplate definitions for all variables
    char which_rotors[5], sol_which_rotors[5];
    int num_active_rotors, sol_num_active_rotors;

    sol_num_active_rotors   =   test_GWR(sol_which_rotors);
    num_active_rotors       =   Get_Which_Rotors(which_rotors);

    printf("\n==GWR Test==\n");
    if( num_active_rotors != sol_num_active_rotors )
    {
        printf("Wrong Return Value - %d vs %d\n", num_active_rotors, sol_num_active_rotors );
        return 0;
    }

    if( strlen(which_rotors) != strlen(sol_which_rotors) )
    {
        printf("Wrong Size - %lu vs %lu\n", strlen( which_rotors ), strlen( sol_which_rotors ) );
        return 0;
    }

    int i;
    for( i = 0; i < strlen(which_rotors); i++)
    {
        if( which_rotors[i] != sol_which_rotors[i] )
        {
            printf("Wrong Input - %d\n", i );
            return 0;
        }
    }

    if( i == strlen(which_rotors) )
        printf("Correct Input\n");

    return 0;
}
