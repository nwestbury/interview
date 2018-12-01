#ifndef MEM_H
#define MEM_H

#include <map>
#include <vector>

class MemoryManager {
  public:
    // buffer is a large chunk of contiguous memory.
    // num_bytes is the size of the buffer.
    MemoryManager(char * buffer, int num_bytes);

    // Allocate memory of size 'size'. Use malloc() like semantics.
    char* alloc(int size);

    // Free up previously allocated memory.  Use free() like semantics.
    void free(char*);

  private:
    char * buffer;
    int num_bytes;
    int available_bytes;
    std::map<char*, int> space;
    std::vector< std::pair<char*, int> > partitions;
};

#endif