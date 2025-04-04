#include "mem.h"                      
extern BLOCK_HEADER* first_header;

//1 is true/free, 0 is false/allocated
int isFree(BLOCK_HEADER block)
{
  if(block.size_alloc % 2 == 1) //if the alloc bit is 1, it is not free (false)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

int getSize(BLOCK_HEADER block)
{
  return block.size_alloc;
}


int trueSize(BLOCK_HEADER block)
{
  if(block.size_alloc%2 == 1)
    {
      return block.size_alloc - 1;
    }
  else
    {
      return block.size_alloc;
    }
}

void setSize(BLOCK_HEADER block, int newSize)
{
  block.size_alloc = newSize;
  return;
}

int getPayload(BLOCK_HEADER block)
{
  return block.payload;
}

void setPayload(BLOCK_HEADER block, int newPayload)
{
  block.payload = newPayload;
  return;
}

void setFree(BLOCK_HEADER block)
{
  if(block.size_alloc % 2 == 0)
    {
      return;
    }
  else
    {
      block.size_alloc -= 1;
      return;
    }
}

void setAllocated(BLOCK_HEADER block)
{
  if(block.size_alloc % 2 == 1)
    {
      return;
    }
  else
    {
      block.size_alloc += 1;
      return;
    }
}


// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size)
{
  int blockSize = (8 + size);
  while(blockSize % 16 != 0) //ensure padding
    {
      blockSize++;
    }
  
  BLOCK_HEADER newBlock;
  newBlock.payload = size;
  newBlock.size_alloc = blockSize;
  BLOCK_HEADER* traversal = first_header;
  void* returnPointer;
  
  int jump;
  //int heapSize = first_header->size_alloc;
  int remainder;
  int failsafe = 0;
  //printf("\nasdf%d\n", newBlock.size_alloc);
  while(traversal->size_alloc != 1 && failsafe < 100) //begin search
    {
      //failsafe++;
      jump = traversal->size_alloc;
      if(isFree(*traversal)) //if found block is free
	{
	  if(trueSize(*traversal) >= trueSize(newBlock)) //if the found block has more than or equal size to the new block
	    {
	      { //insert the data
		remainder = trueSize(*traversal);
		remainder -= trueSize(newBlock);
		traversal->size_alloc = (newBlock.size_alloc + 1);
		traversal->payload = newBlock.payload;
		
		returnPointer = traversal;
		returnPointer += 8;
		
		jump = trueSize(*traversal);
		//printf("\n\n\n\nremainder:%d", remainder);
	      }
	      { //split the new block
		if(remainder == 0)
		  {
		    return returnPointer;
		  }
		traversal += (jump/8); //jump to next block header
		traversal->size_alloc = remainder;
		traversal->payload = (remainder-8);
		//printf("Initialization Successful.\n");
		return returnPointer;
	      }
	    }
	  else //traverse to the next found block
	    {
	      //printf("size Failure. Was %d, needed %d; %p\n", trueSize(*traversal), trueSize(newBlock), traversal);
	      traversal += trueSize(*traversal)/8;
	    }
	}
      else //traverse to the next found block
	{
	  //printf("freedom failure.");
	  //printf("\n%p, %d;\n", traversal, trueSize(*traversal));
	  traversal += trueSize(*traversal)/8;
	}
      //printf("swag");
    }

  // find a free block that's big enough

    // return NULL if we didn't find a block

    // allocate the block

    // split if necessary (if padding size is greater than or equal to 16 split the block)

    return NULL;
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr)
{
  BLOCK_HEADER* traversal = first_header;
  BLOCK_HEADER* tracer = traversal;
  BLOCK_HEADER* blazer = (traversal + trueSize(*traversal)/8);
  int failsafe = 0;
  while(traversal->size_alloc != 1 && failsafe < 10)
    {
      //failsafe++;
      //printf("\nTracer:    %p\nTraversal: %p\nBlazer:    %p\nToFind:    %p\n", tracer, traversal, blazer, ptr);

      //CHECK FOR SEGFAULT WITH BLAZER
      
      if((traversal + 1) == ptr) //check if the pointer parameter matches the pointer in the heap
	{
	  if(isFree(*traversal) == 1) //free a freed block catcher
	    {
	      return -1;
	    }
	  //printf("\n?:%d\n", traversal->size_alloc & 1);
	  //four cases
	  // ALLOC above, ALLOC below
	  if(isFree(*tracer) == 0 && isFree(*blazer) == 0)
	    {
	      //printf("\nAA\n");
	      traversal->size_alloc--;
	      traversal->payload = (traversal->size_alloc - 8);
	      return 0;
	    }
	  
	  // ALLOC above, FREE below
	  if(isFree(*tracer) == 0 && isFree(*blazer) == 1)
	    {
	      //printf("\nAF\n");
	      traversal->size_alloc--;
	      traversal->payload = (traversal->size_alloc - 8);
	      traversal->size_alloc += blazer->size_alloc;
	      traversal->payload = (traversal->size_alloc - 8);
	      return 0;
	    }

	  // FREE above, ALLOC below
	  if(isFree(*tracer) == 1 && isFree(*blazer) == 0)
	    {
	      //printf("\nFA\n");
	      traversal->size_alloc--;
	      traversal->payload = (traversal->size_alloc - 8);
	      tracer->size_alloc += traversal->size_alloc;
	      tracer->payload = (tracer->size_alloc - 8);
	      return 0;
	    }
	  
	  // FREE above, FREE below
	  if(isFree(*tracer) == 1 && isFree(*blazer) == 1)
	    {
	      //printf("\nFF\n");
	      traversal->size_alloc--;
	      //traversal->payload = (traversal->size_alloc - 8);
	      traversal->size_alloc += blazer->size_alloc;
	      //traversal->payload += blazer->payload;
	      tracer->size_alloc += traversal->size_alloc;
	      //tracer->payload += traversal->payload;
	      tracer->payload = (tracer->size_alloc - 8);
	      return 0;
	    }
	  return -1;
	}
      else
	{
	  tracer = traversal;	 
	  traversal += trueSize(*traversal)/8; //else, go to next block header
	  if(blazer->size_alloc != 1)
	    {
	      blazer += trueSize(*blazer)/8;
	    }
	}
    }
    // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
    
    // free the block 

    // coalesce adjacent free blocks
  
  return -1;
}


//potentially useful helpers
/*
is free
if\s allocated
get size
set size
get payload
set payload
set free
set allocated
get user pointer
next header
get padding


multiple of the minimum block size is the allowerd block size
aka
ABS = MBS*n
*/
