#include <stdio.h>
#include <stdlib.h>
// ***************************************
// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST test_Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void test_Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void test_Print_File(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// this function returns the number 
// of elements in the linked list
int test_Size(LINKED_LIST list){
    if (list.head == NULL) return 0;
    int count = 0;
    for (NODE *p = list.head; p != NULL; p = p->next) 
        count++;
    return count;
}
// this function adds an element to
// the front of the list
void test_Push_Front(LINKED_LIST *list, int data){
    NODE *new_node = malloc(sizeof(NODE)); test_Verify_Malloc(new_node);
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    return;
}

// this function adds an element 
// to the end of the linked list 
void test_Push_Back(LINKED_LIST *list, int data) {
    if (list->head == NULL) {
        test_Push_Front(list, data);
        return;
    }
    // find the last NODE
    NODE *current = list->head;
    while (current->next) current = current->next;
    NODE *new_node = malloc(sizeof(NODE)); test_Verify_Malloc(new_node);
    new_node->data = data;
    new_node->next = NULL;
    current->next = new_node;
    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int test_Pop_Front(LINKED_LIST *list, int *data) {
    if (list->head == NULL) return 0;
    *data = list->head->data;
    NODE *delete_this = list->head;
    list->head = list->head->next;
    free(delete_this);
    return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int test_Pop_Back(LINKED_LIST *list, int *data) {
    if (list->head == NULL) return 0;

    if (list->head->next == NULL)
    {
        *data = list->head->data;
        free( list->head );
        list->head = NULL;
        return 1;
    }
    // find the last NODE
    NODE *current = list->head;

    while( current->next != NULL ) current = current->next;
    *data = current->data;

    // find and update the node before the last
    NODE *previous = list->head;
    while (previous->next != current) previous = previous->next;
    previous->next = NULL;
    free(current);
    return 1;
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int test_Count_If(LINKED_LIST list, int data) {
    if (list.head == NULL) return 0;
    int count = 0;
    NODE *current = list.head;
    while (current != NULL){ 
        if (current->data == data) count++;
        current = current->next;
    }
    return count++;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int test_Delete(LINKED_LIST *list, int data) {
    if (list->head == NULL) return 0; // empty list
    
    // find the first node containing this value
    NODE *current = list->head;
    while (current->data != data && current->next != NULL) current = current->next;
    // current is either the data or the last NODE
    if (current->data == data) {
        // find the previous node
        NODE *previous = list->head;
        //  Node to be deleted is head
        if( previous == current )
        {
            list->head = NULL;
            free(current);
            return 1;
        }
        while (previous->next != current)  previous=previous->next;
        previous->next = current->next;
        free(current);
        return 1;
    }
    else return 0;
}

// return 1 if the list is empty otherwise returns 0
int test_Is_Empty(LINKED_LIST list) {
    if (list.head == NULL) return 1;
    return 0;
}

// delete all elements of the list
// remember to free the nodes
void test_Clear(LINKED_LIST *list) {
    if (list->head == NULL) return;
    NODE *current = list->head;
    NODE *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    return;
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void test_Remove_Duplicates(LINKED_LIST *list) {
    if (list->head == NULL) return;
    // make a new list
    LINKED_LIST new_list = test_Create_List();
    NODE *current = list->head;
    while (current != NULL) {
        if (test_Count_If(new_list, current->data) == 0) test_Push_Back(&new_list, current->data); 
        current=current->next;
    }
    test_Clear(list);
    list->head = new_list.head;
    return;
}


int compare_LL( NODE *candidate, NODE *sol ) {
    if( sol == NULL )
        return candidate == NULL;

    if( candidate == NULL )
        return 0;

    return sol->data == candidate->data && compare_LL( candidate->next, sol->next );
}
