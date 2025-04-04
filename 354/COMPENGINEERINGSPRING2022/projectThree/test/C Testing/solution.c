// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// ***************************************
// *** struct definitions ****************
// *** do not change these ***************
// ***************************************
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// ******************************************************
// *** Complete the following functions  ****************
// ******************************************************

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list)
{
  //start at the head of the linked list
  //from the first object, size is 1
  //after that, make a while loop that takes the current pointer, goes to the next node's pointer, and incremements it while it isn't NULL
  int size = 0;
  NODE* tempNode;
  
  if(list.head == NULL)
    {
      return 0;
    }
  else
    {
      tempNode = list.head;
      while(tempNode != NULL)
	{
	  size++;
	  tempNode = tempNode->next;
	}
    }
  
  return size;
}

// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data)
{
  //create a new NODE pointer with the right space allocated
  //assign the NODE fields accordingly
  //reassign the list pointer to the new NODE
  
  NODE* newNode = malloc(sizeof(NODE));
  newNode->data = data;
  newNode->next = list->head;
  list->head = newNode;
  return;
}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data)
{
  //similar as above, but assign the last pointer to it, which makes you traverse the list
  //also, assign newnode next to NULL
  NODE* newNode = malloc(sizeof(NODE));
  newNode->data = data;
  newNode->next = NULL;

  if(list->head == NULL)
    {
      list->head = newNode;
      return;
    }
  
  NODE* tempNode = list->head;
  while(tempNode->next != NULL)
    {
      tempNode = tempNode->next;
    }
  tempNode->next = newNode;
  //create a new NODE using the provided data. the next pointer will be null.
  //assign the last node's next pointer to the new NODE.
  return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data)
{
  if(list->head == NULL) //if list has no head, it's empty. Size = 0.
    {
      *data = -1;
      return 0;
    }
  /*if(list->head->next == NULL) //if the list is one element, it's now empty
    {
      printf("DIe Blay");
      *data = list->head->data;
      free(list->head);
      NODE* tempNode = list->head;
      tempNode->data = -11;
      list->head == NULL;
      return 1;
    }*/
  *data = list->head->data; //make data pointer's value be the data thing
  NODE* temp = list->head->next;
  //printf("\n\n%d\n\n", temp->data);
  free(list->head);
  list->head = temp;
  return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data)
{
  if(list->head == NULL) //list is empty
    {
      *data = -1;
      return 0;
    }
  NODE* tempNode = list->head;
  if(list->head->next == NULL) //list is 1 element
    {
      *data = list->head->data;
      free(list->head);
      list->head = NULL;
      return 1;
    }
  else //list is >=2 elements
    {
      while(tempNode->next->next != NULL) //see if the n+1 element has an n+2 element. If not, continue.
	{
	  tempNode = tempNode->next;
	}
      *data = tempNode->next->data;
      free(tempNode->next);
      tempNode->next = NULL;
      return 1;
    }
  return 0;
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data)
{
  int dracula = 0;
  if(list.head == NULL)
    {
      return 0;
    }
  NODE* tempNode = list.head;
  while(tempNode->next != NULL)
    {
      if(tempNode->data == data)
      {
	dracula++;
      }
      tempNode = tempNode->next;
    }
  if(tempNode->data == data)
    {
      dracula++;
    }
  return dracula;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data)
{
  if(list->head == NULL) //list is empty
    {
      return 0;
    }
  if(list->head->next == NULL) //list is 1 element
    {
      if(list->head->data == data)
	{
	  free(list->head);
	  list->head = NULL;
	  return 1;
	}
      else
	{
	  return 0;
	}
    }
  NODE* tempNode = list->head;
  NODE* bridgeNode;
  if(tempNode->data == data) //if first node is data
    {
      bridgeNode = tempNode->next;
      free(tempNode);
      list->head = bridgeNode;
    }

  while(tempNode->next->next != NULL) //list is 2+ elements
    {
      if(tempNode->next->data == data)
	{
	  bridgeNode = tempNode->next->next;
	  free(tempNode->next);
	  tempNode->next = bridgeNode;
	  return 1;
	}
      tempNode = tempNode->next;
    }
  if(tempNode->next->data == data)
    {
      tempNode->next = NULL;
      free(tempNode->next);
      tempNode->next = NULL;
    }
  return 0;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list)
{
  if(list.head == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list)
{
  if(list->head == NULL)
    {
      return;
    }
  NODE* tempNode;
  while(list->head != NULL)
    {
      tempNode = list->head;
      if(tempNode->next == NULL)
	{
	  free(list->head);
	  list->head = NULL;
	}
      else
	{
	  while(tempNode->next != NULL)
	    {
	      free(tempNode->next);
	      tempNode->next = NULL;
	    }
	}
    }
  return;
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list)
{
  if(list->head == NULL) //empty list
    {
      return;
    }
  if(list->head->next == NULL) //1 element list
    {
      return;
    }
  if(list->head->next->next == NULL) //2 element list
    {
      if(list->head->data == list->head->next->data)
	{
	  free(list->head->next);
	  return;
	}
      else
	{
	  return;
	}
    }
  //>2 element list
  NODE* tempNode = list->head;
  int dracula = Size(*list);
  int listArray[dracula];
  for(int i = 0; i < dracula; i++)
    {
      listArray[i] = tempNode->data;
      tempNode = tempNode->next;
    }
  tempNode = list->head;
  int known[dracula];
  for(int i = 0; i < dracula; i++)
    {
      known[i] = -1623;
    }
  int delete = 0;
  int knownIndex = 1;
  NODE* prevNode;

  known[0] = list->head->data;
  for(int i = 0; i < dracula; i++)
    {
      if(tempNode->next->next == NULL)
	{
	  break;
	}
      //printf("NEW LOOP!\n");
      prevNode = tempNode;
      tempNode = tempNode->next;
      delete = 0;
      for(int j = 0; j < dracula; j++)
	{
	  //printf("\n%d, %d\n", tempNode->data, known[j]);
	  if(known[j] == tempNode->data)
	    {
	      delete = 1;
	      break;
	    }
	}
      if(delete == 1)
	{
	  //  printf("\nMUST DELETE\n");
	  prevNode->next = tempNode->next;
	  free(tempNode);
	  tempNode = prevNode;
	}
      if(delete == 0)
	{
	  known[knownIndex] = tempNode->data;
	  knownIndex++;
	}
      // printf("TEMPNODE: %d\nPREVNODE: %d\n", tempNode->data, prevNode->data);
    }
  for(int k = 0; k < dracula; k++)
    {
      if(known[k] == tempNode->next->data)
	{
	  free(tempNode->next);
	  //printf("Swag?");
	  tempNode->next = NULL;
	  break;
	}
    }
  return;
}

// modify main to completely test your functions 
int swag() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);

    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));

    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    // write a better test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);

    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a beter test for Count_If
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    // write a test for Delete 
    printf("Testing Delete\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);

    // write a better test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    // write a better test for Clear
    Clear(&list);
    
    if (Is_Empty(list))
      {
	printf("List is Empty\n");
      }
    else
      {
	printf("List is not empty\n");
      }
    // write a better test for Remove_Duplicate
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Print_List(stdout, list);
    Remove_Duplicates(&list);
    Print_List(stdout, list);    
    return 0;
}
