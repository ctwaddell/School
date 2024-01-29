#include "enigma.h"
#include "enigma_sol.h"

int main() {

    int rotations, sol_rotations;

    sol_rotations   =   test_GR();
    rotations   =   Get_Rotations();

    printf("\n==GR Test==\n");
    if( rotations == sol_rotations )
        printf("Correct Input\n");
    else
        printf("Wrong Input - %d vs %d\n", rotations, sol_rotations);

    // Boilerplate definitions for all variables

    return 0;
}
