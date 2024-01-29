#include <stdio.h>

// THE CACHE
struct LINE{
    char valid;
    int tag;
    char data[32];
};

struct SET{
    struct LINE line[1];
};

struct CACHE {
    struct SET set[8];
} cache;

// GLOBALDATA
// increment these in your function
unsigned hit_count  = 0;
unsigned miss_count = 0;
unsigned read_data_count = 0;

// SYSTEM BUS 
// call Read_Data_From_Ram to update this
char system_bus[32];



// READ DATA FROM RAM
// this function copies 32 character from the text file to
// the system_bus array aligned with the system bus
// (we will not test this with input larger than the text file)
void Read_Data_From_Ram(unsigned address) {
    address >>= 5; address <<= 5; // get align the data
    read_data_count++;
    FILE *file;
    file = fopen("alice_in_wonderland.txt", "r");
    fseek(file, address, SEEK_SET);
    for (int i = 0; i<32; i++) system_bus[i] = fgetc(file);
    return;
}


// COMPLETE THE FOLLOWING FUNCTION 
//
// this code should check to see if the data in the cache is valid and the tag matches
// if so it should return the char matching the address and increment the hit count
//
// if not it should read the data from the system bus copy it into the cache and 
// increment the miss count and return the char matching the address
// 
char Read_Data_From_Cache(unsigned address)
{
  //printf("%u\n", address);
  unsigned setNumber = ((address >> 29) & 7);
  //printf("%u\n", setNumber);
  unsigned tagNumber = (((address << 3) >> 8) & 16777215);
  printf("\n%u\n", tagNumber);
  unsigned offsetNumber = (address & 31);
  //printf("%u\n", offsetNumber);
  printf("tag%d", cache.set[setNumber].line[0].tag);
  if(cache.set[setNumber].line[0].tag == tagNumber) //if the set's tag equals the address tag
    {
      if(cache.set[setNumber].line[0].valid != 0) //and the set's valid bit is not 0
	{
	  printf("\nRATIO!\n");
	  hit_count++;
	  return cache.set[setNumber].line[0].data[offsetNumber];
	}
    }
  //else the address is not valid/found
  //printf("\nANTI-RATIO!\n");
  miss_count++;
  Read_Data_From_Ram(address);
  for(int i = 0; i < 32; i++)
    {
      cache.set[setNumber].line[0].data[i] = system_bus[i];
    }
  return cache.set[setNumber].line[0].data[offsetNumber];
}

void Print_Cache(struct CACHE c)
{
  for(int i = 0; i < 8; i++)
    {
      printf("SET %d: %c %d %s\n", i, c.set[i].line[0].valid, c.set[i].line[0].tag, c.set[i].line[0].data);
    }
}

int main() {
    // INITIALIZE CACHE
    for (int i = 0; i<8; i++) cache.set[i].line[0].valid = 0;
    
    // READ SOME DATA
    char c;
    for(int j = 0; j < 1000; j++)
      {
	c = Read_Data_From_Cache(j);
        //printf("%c", c);
      }
    c = Read_Data_From_Cache(0); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(1); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(2); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(3); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(4); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(4294967295);
    c = Read_Data_From_Cache(3221225471);
    c = Read_Data_From_Cache(2684354815);
    c = Read_Data_From_Cache(1610613219);
    c = Read_Data_From_Cache(3758096867);
    // WRITE A LOT MORE TESTS

    return 0;
}

