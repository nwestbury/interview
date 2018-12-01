#include "mem.hpp"
#include <cassert>


void test_case_init() {
    int num_bytes = 1000;
    char * buffer = new char[num_bytes];

    MemoryManager* mm = new MemoryManager(buffer, num_bytes);

    delete [] buffer;
    delete mm;
}

void test_case_alloc() {
    int num_bytes = 1000;
    char * buffer = new char[num_bytes];

    MemoryManager* mm = new MemoryManager(buffer, num_bytes);

    for(int i=0; i<10; ++i) {
        mm->alloc(100);
    }

    char * overalloc = mm->alloc(100);

    assert(overalloc == NULL);

    delete [] buffer;
    delete mm;
}

void test_case_alloc_free() {
    int num_bytes = 1000;
    char * buffer = new char[num_bytes];
    char * orig_buffer = buffer;

    MemoryManager* mm = new MemoryManager(buffer, num_bytes);

    char * first = mm->alloc(300);
    char * second = mm->alloc(300);
    char * third = mm->alloc(400);
    
    mm->free(first);
    mm->free(second);

    char * fourth = mm->alloc(600);
    assert(fourth != NULL);

    mm->free(fourth);
    mm->free(third);

    char * all = mm->alloc(1000);

    assert(all != NULL);
    assert(all == orig_buffer); // should be same as original start

    delete [] buffer;
    delete mm;
}

int main (){
    test_case_init();
    test_case_alloc();
    test_case_alloc_free();
}