#include "mem.hpp"

// #define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

// MemoryManager Constructor
MemoryManager::MemoryManager(char * buffer, int num_bytes)
{
  /***
   * Initalization function
   * 
   * Args:
   *  buffer (char *): pre-allocated buffer
   *  num_bytes (int): size of pre-allocated buffer
   ***/
  #ifdef DEBUG
  cout << "Init " << num_bytes << " bytes" << endl;
  #endif

  this->buffer = buffer;
  this->num_bytes = num_bytes;
  this->available_bytes = num_bytes;
  this->partitions.push_back(make_pair(buffer, num_bytes));
}
 
// Date member function
char * MemoryManager::alloc(int size)
{
  /***
   * Greedy allocator function that finds the smallest large-enough contigious amount of space
   * and returns the address of the memory. NULL if it fails.
   * 
   * Args:
   *  size (int): size of buffer to allocate in bytes
   * 
   * Returns:
   *  address (char *): address of allocated memory
   ***/
  #ifdef DEBUG
  cout << "Allocating " << size << " bytes" << endl;
  #endif

  if (size > this->available_bytes) { // cannot allocate more than theoretical limit
    return NULL;
  }

  int min_memory = -1;
  vector<pair<char*, int> >::iterator pos;
  for(vector<pair<char*, int> >::iterator it = this->partitions.begin(); it != this->partitions.end(); ++it) {
    char * block_start = it->first;
    int block_size = it->second;

    #ifdef DEBUG
    cout << "Considering " << (void *)(it->first) << " " << it->second << endl;
    #endif

    // if the block is the correct size and is the smallest so far
    if (block_size >= size && (min_memory == -1 || block_size < min_memory) ) {
      min_memory = block_size;
      pos = it;
    }
  }

  if (min_memory == -1) { // Not able to allocate memorys
    return NULL;
  }

  #ifdef DEBUG
  cout << "Best found is " << (void *)(pos->first) << " " << pos->second << endl;
  #endif

  char * loc = pos->first;

  if (min_memory == size) {
    this->partitions.erase(pos);
  } else {
    pos->first += size; // offset pointer
    pos->second -= size; // decrease available size
  }

  this->space[loc] = size;
  this->available_bytes -= size;

  return loc;
}

void MemoryManager::free(char* m) {
    /***
   * Frees the memory previous allocated starting at the provided address.
   * Must have been allocated with alloc();
   * 
   * Args:
   *  address (char *): memory to free
   * 
   ***/

  int size = this->space[m]; // note: I assume the correct memory address is passed

  #ifdef DEBUG
  cout << "Found space of size " << size << endl;
  #endif

  pair<char*, int> new_block;
  new_block.first = m;
  new_block.second = size;
  char * end_memory = m + size;

  vector<pair<char*, int> >::iterator it = this->partitions.begin();
  while(it != this->partitions.end()) {
    if (it->first + it->second == m) { // block before the freed one
      new_block.first = it->first;
      new_block.second += it->second;
      it = this->partitions.erase(it);
    } else if (it->first == end_memory) { // block after the freed one
      new_block.second += it->second;
      it = this->partitions.erase(it);
    } else {
      ++it;
    }
  }

  this->partitions.push_back(new_block);
  this->available_bytes += size;
}