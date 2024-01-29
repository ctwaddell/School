#include "solution.c"
#include "linked_list_sol.h"

int main() 
{
    LINKED_LIST sol = test_Create_List();
    LINKED_LIST list = test_Create_List(); 

    //  Valid functions to test : 
    //  Size -> returns count of nodes
    //  Push_Front -> adds to the front of the node (head)
    //  Push_Back -> adds to the back
    //  Pop_Front -> removes head
    //  Pop_Back -> removes last element
    //  Count_If -> returns count of elements == data
    //  Delete -> Delete first node containing data
    //  Is_Empty -> return if list is empty
    //  Clear -> remove all nodes
    //  Remove_Duplicates -> remove all with same value

    int num_ops;
    int data[40];
    char op[40];
    int ret_cand, ret_sol;
    int cand_data;
    int sol_data;
    int exec = 1;

    scanf("%d", &num_ops);

    //  Read all Linked List operations
    for( int i = 0; i < num_ops; i++ )
    {
        scanf(" %c", &op[i]);
        scanf("%d", &data[i]);
    } 

    printf("Testing for %d operations in total\n", num_ops );
    //  Process all the Linked List operations
    for( int i = 0; i < num_ops; i++ )
    {
        //  Init comparison variables to defaults
        ret_cand = 1;
        ret_sol = 1;

        cand_data = 0;
        sol_data = 0;

        switch( op[i] )
        {
            //  Init - Add elements to the list for init
            case 'X'    :   test_Push_Back( &list, data[i] );
                            test_Push_Back( &sol, data[i] );
                            break;
            //  Size - returns size
            case 'S'    :   ret_cand = Size( list );
                            ret_sol = Size( sol );
                            break;
            //  Push Front - modifies LL
            case 'F'    :   Push_Front( &list, data[i] ); 
                            test_Push_Front( &sol, data[i] );
                            break;
            //  Push Back - modifies LL
            case 'B'    :   Push_Back( &list, data[i] );
                            test_Push_Back( &sol, data[i] );
                            break;
            //  Pop Front - modifies LL + returns !isEmpty
            case 'f'    :   ret_cand = Pop_Front( &list, &cand_data );
                            ret_sol = test_Pop_Front( &sol, &sol_data );
                            break;
            //  Pop Back - modifies LL + returns !isEmpty
            case 'b'    :   ret_cand = Pop_Back( &list, &cand_data );
                            ret_sol = test_Pop_Back( &sol, &sol_data );
                            break;
            //  Count If - returns count
            case 'I'    :   ret_cand = Count_If( list, data[i] );
                            ret_sol = test_Count_If( sol, data[i] );
                            break;
            //  Delete - modifies LL + returns (did something delete)
            case 'D'    :   ret_cand = Delete( &list, data[i] );
                            ret_sol = test_Delete( &sol, data[i] );
                            break;
            // Is Empty - returns isEmpty 
            case 'E'    :   ret_cand = Is_Empty( list );
                            ret_sol = test_Is_Empty( sol );
                            break;
            //  Clear - modifies LL
            case 'C'    :   Clear( &list );
                            test_Clear( &sol );
                            break;
            //  Remove Duplicates - modifies LL
            case 'R'    :   Remove_Duplicates( &list );
                            test_Remove_Duplicates( &sol );
                            break;
            default     :   printf("Incorrect OP\n");
        }

        //  Failed to return right value from op
        if( ret_cand != ret_sol )
        {
            printf("Failed at operation index: %d\n - Incorrect return", i );
            printf("Cand : %d vs Sol : %d \n", ret_cand, ret_sol );
            exec = 0;
            break;
        }

        //  Failed to modify param correctly in op
        if( sol_data != cand_data )
        {
            printf("Failed at operation index: %d\n - Incorrect data", i );
            exec = 0;
            printf("Cand : %d vs Sol : %d\n", cand_data, sol_data );
        }

    }

    if( sol.head )
    {
        if( list.head == NULL )
        {
            printf("Failed at end, list is empty\n");
            exec = 0;
        }
        else
        {
            if( !compare_LL( sol.head, list.head ) )
            {
                printf("Failed at end, incorrect list\n");
                //  Print both lists to compare
                printf("Student list:\n");
                test_Print_File( stdout, list );
                printf("\nExpected list:\n");
                test_Print_File( stdout, sol );
                exec = 0;
            }
        }
    }
    else
    {
        if( list.head )
        {
            printf("Failed at end, list should have been empty\n");
            exec = 0;
        }
    }

    if( exec )
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    
    return 0;
}
