//Header Guard
#ifndef _MYHEAP_H
#define _MYHEAP_H

#define MAX_CAPACITY 512 // the size capacity of Img_heap

struct memory_block
{
	memory_block* right; // node to the right
	memory_block* left; // node to the left
	bool used; // if this memory block is reserved or not
	int size; // the number of bytes reserved in Img_heap
	int starting_address; // the starting address in Img_heap
	// of the memory reserved by this block

	//Default Constructors
	memory_block :: memory_block ()
	{}

	memory_block :: memory_block (memory_block* r, memory_block* l, bool b, int s, int s_a)
		: right(r), left(l), used(b), size(s), starting_address(s_a)
	{}
};

class My_heap{
private:
	memory_block* heap_begin; //pointer to the first memory_block in My_heap
	memory_block* blk; //pointer to the last memory_block in My_heap
	int used_bytes; // # of allocated bytes in Img_heap
public:
	My_heap();
	~My_heap();
	memory_block* bump_allocate(int num_bytes);
	memory_block* first_fit_allocate(int num_bytes);
	memory_block* best_fit_allocate(int num_bytes);
	memory_block* first_fit_split_allocate(int num_bytes);
	void deallocate(memory_block* block_address);
	void print_heap();
	float get_fragmantation();
};

#endif