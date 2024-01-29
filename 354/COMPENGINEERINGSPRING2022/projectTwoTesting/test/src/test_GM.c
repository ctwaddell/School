#include "enigma.h"
#include "enigma_sol.h"

int main() {
    // Boilerplate definitions for all variables
    char message[80], sol_message[80];
    int i;

    //  printf("Enter the message to be encrypted or decrypted: ");
    test_GM(sol_message);
    Get_Message(message);

    printf("\n==GM Test==\n");
    if( strlen(message) != strlen(sol_message) )
    {
        printf("Wrong Size - %lu vs %lu\n", strlen(message), strlen(sol_message));
        return 0;
    }
    if( message[strlen(message) - 1] == '\n' )
    {
        printf("Wrong Input - contains newline\n");
        return 0;
    }

    for( i = 0; i < strlen(message); i++)
    {
        if( message[i] != sol_message[i] )
        {
            printf("Wrong Input - %s vs %s\n", message, sol_message );
            return 0;
        }
    }

    if( i == strlen(message) )
        printf("Correct Input\n");

    return 0;
}
