#include <iostream>
#include "my_heap.h"

using namespace std;

My_heap :: My_heap ()
	//Creates an empty doubly linked list: My_heap
{
	heap_begin = NULL;
	blk = NULL;
	used_bytes = 0;
}
//-------------------------------------------------------------------------------------------
memory_block * My_heap :: bump_allocate(int num_bytes)
{

	memory_block *new_block = new memory_block;
	new_block->size = num_bytes;
	new_block->used = true;
	new_block->right = NULL;


	//If empty linked list, create the first node
	if(heap_begin == nullptr)
	{
		new_block->left = nullptr;
		new_block->starting_address = 0;
		heap_begin = new_block;
		used_bytes += heap_begin->size;
		blk= heap_begin;
		return heap_begin;
	}
	else
	{
		if(((blk->starting_address + blk->size)  + num_bytes) <= MAX_CAPACITY)
		{
			new_block->starting_address = blk->starting_address + blk->size;
			new_block->left = blk;
			blk->right = new_block;
			blk = new_block;
			used_bytes += new_block->size;
		}
		else 
		{
			return nullptr;
		}
	}
	return new_block;
}
//-------------------------------------------------------------------------------------------
void My_heap :: deallocate(memory_block* to_delete)
{
	memory_block * dalloc_ptr = to_delete;
	memory_block *tempL = dalloc_ptr;
	memory_block *tempR = dalloc_ptr;

	dalloc_ptr->used = false;

	if(heap_begin == NULL || dalloc_ptr == NULL)
		return;
	if(heap_begin == dalloc_ptr)
		heap_begin = dalloc_ptr->right;

	while((dalloc_ptr->left)->used != true)
	{
		dalloc_ptr->left = dalloc_ptr->left->left;
		dalloc_ptr->size += dalloc_ptr->left->size;
		dalloc_ptr->starting_address -= dalloc_ptr->left->size;
		dalloc_ptr->left = dalloc_ptr->left->left;
	}

	if(dalloc_ptr->right != nullptr)
	{
		while((dalloc_ptr->right)->used != true)
		{
			dalloc_ptr->right = dalloc_ptr->right->right;
			dalloc_ptr->size += dalloc_ptr->right->size;
			dalloc_ptr->right = dalloc_ptr->right->right;
		}
	}


	if(dalloc_ptr->right != NULL)
		dalloc_ptr->right->left = dalloc_ptr->left;
	if(dalloc_ptr->left != NULL)
		dalloc_ptr->left->right = dalloc_ptr->right;

	used_bytes-=dalloc_ptr->size;
	delete dalloc_ptr;
	dalloc_ptr = NULL;
}
//-------------------------------------------------------------------------------------------
memory_block * My_heap :: first_fit_allocate(int num_bytes)
{
	memory_block *ptr = heap_begin;
	while(ptr != nullptr)
	{
		if(((ptr->used) == false) && ((ptr->size) >= num_bytes))
		{
			ptr->used = true;
			used_bytes+= ptr->size;
			return ptr;
		}
		else
		{
			ptr = ptr->right;
		}
	}
	return bump_allocate(num_bytes);
}
//-------------------------------------------------------------------------------------------
memory_block * My_heap :: best_fit_allocate(int num_bytes)
{
	memory_block *ptr = heap_begin;
	memory_block *best_ptr = nullptr;
	int bestsizecounter = INT_MAX;

	while(ptr != nullptr)
	{
		if((ptr->used == false) && (ptr->size >= num_bytes)&& (ptr->size-num_bytes < bestsizecounter))
		{
			bestsizecounter = ptr->size - num_bytes;
			best_ptr = ptr;
		}
		ptr = ptr->right;
	}
	if(best_ptr  == nullptr)
		return bump_allocate(num_bytes);
	else 
	{
		best_ptr->used = true;
		used_bytes += best_ptr->size;
		return best_ptr;
	}	
}
//-------------------------------------------------------------------------------------------
memory_block * My_heap :: first_fit_split_allocate(int num_bytes)
{
	memory_block *ptr = heap_begin;
	memory_block *ptr_split;
	int addressCounter = 0;
	while(ptr != nullptr)
	{
		addressCounter += ptr->size;
		if(ptr->used == false)
		{
			if((ptr->size) == num_bytes)
			{
				ptr->used = true;
				return ptr;
			}
			else if((ptr->size) > num_bytes)
			{

				ptr->size = num_bytes;
				ptr_split = new memory_block (ptr->right, ptr, false, ((ptr->size)-num_bytes),addressCounter);
				ptr->right = ptr_split;
				used_bytes += num_bytes;
				//return adress of the numbyte size block

			}
		}
		ptr = ptr->right;
	}
	return bump_allocate(num_bytes);
}
//-------------------------------------------------------------------------------------------
float My_heap :: get_fragmantation()
{
	float biggest_free_block = 0.0;
	memory_block *ptr = heap_begin;
	int free_memory = MAX_CAPACITY-used_bytes;

	while(ptr != nullptr)
	{
		if(ptr->used == false)
		{
			int biggest = ptr->size;
			if(biggest > biggest_free_block )
			{
				biggest_free_block = float(ptr->size);
			}
		}
		ptr = ptr->right;
	}
	float fragmentation_percentage = (free_memory - biggest_free_block)/free_memory*100;
	return fragmentation_percentage;
}
//-------------------------------------------------------------------------------------------
void My_heap :: print_heap()
{
	memory_block * ptr = heap_begin;
	int currently_used_memo = used_bytes;
	int total_memo_blks = 0;
	int used_memo_blks = 0;
	int free_memo_blks = 0;
	float heap_frag = get_fragmantation();
	int index_counter = 0;
	memory_block * last;


	while(ptr != NULL)
	{
		total_memo_blks++;
		if(ptr->used == false)
		{
			free_memo_blks ++;
		}
		else if(ptr->used == true)
		{
			used_memo_blks ++;
		}
		ptr = ptr->right;

	}
	cout << "Maximum capacity of heap: 512B" << endl;
	cout << "Currently used memory (B): " << currently_used_memo << endl;
	cout << "Total memory blocks: " << total_memo_blks << endl;
	cout << "Total used memory blocks: " << used_memo_blks << endl;
	cout << "Total free memory blocks: " << free_memo_blks << endl;
	cout << "Fragmentation: " << heap_frag << endl;
	cout << "------------------------------" << endl;

	ptr = heap_begin;
	while(ptr != NULL)
	{
		cout << "Block " << index_counter << "  Used: " << ptr->used 
			<< " Size (B): " << ptr->size << " Starting Address: 0x" << hex << ptr->starting_address << dec<< endl;
		index_counter ++;
		last = ptr;
		ptr = ptr->right;
	}
	cout << "------------------------------" << endl;
	cout << "------------------------------" << endl;
}
//-------------------------------------------------------------------------------------------
My_heap :: ~My_heap() //Deconstructor
{
	memory_block *temp;
	memory_block *ptr = heap_begin;


	int leak = 0;
	while(ptr != blk)
	{
		leak += ptr->size;
		ptr = ptr->right;
	}

	cout << "At destruction, the heap had a memory leak of " << leak << " bytes. " << endl;

	while (ptr != NULL)
	{
		temp = ptr->right;
		delete ptr;
		ptr = temp;
	}
}