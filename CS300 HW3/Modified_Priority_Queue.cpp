#ifndef _MODIFIED_PRIORITY_QUEUE_CPP
#define _MODIFIED_PRIORITY_QUEUE_CPP

#include <iostream>
#include "Modified_Priority_Queue.h"
using namespace std;

//Destructor
MPQ :: ~MPQ()
{
	for(unsigned int i = 0; i < heap_arr.size(); i++)
	{
		heap_arr.pop_back();
	}
}

//Returns the maximum value that is currently stored
int MPQ :: GetMax()
{
	if (!IsEmpty())	
		return heap_arr[1].height;
}

//Check if the MPQ is empty, or not?
bool MPQ :: IsEmpty() const
{
	//if size of the heap_arr is equal to zero, then return true
	if( heap_arr.size() == 0)
		return true;
	else
		return false;
}

//Inserts an item with the given value  and label into the MPQ
void MPQ :: insert (MPQ_Obj & obj)
{
	int hole = ++current_size;
	for( ; hole > 1 && obj.x_cor > heap_arr[hole / 2].x_cor; hole /= 2 )
	{
		heap_arr[hole] = heap_arr[hole/2];
	}
	heap_arr[hole] = obj;
}

//Removes the value with this label and returns it
void MPQ :: Remove(int label)
{
	// return 0 if the heap is empty or there doesn't exist the labeled item
	if (IsEmpty())
	{
		return;
	}
	else
	{
		for(unsigned int i = 0; i < heap_arr.size(); i++)
		{
			if(heap_arr[i].label == label && !IsEmpty())
			{
				heap_arr.erase(heap_arr.begin() + i);
				--current_size; //reduce the stored elements.
				percolateDown(i); //Establish heap order property back.
			}
		}
	}
}

//Percolate down in the heap.
void MPQ:: percolateDown( int hole )
{
	int child;
	MPQ_Obj temp = heap_arr[hole];

	for( ; hole * 2 <= current_size; hole = child )
	{
		child = hole * 2;
		if( child != current_size && heap_arr[child + 1].x_cor > heap_arr[child].x_cor)
			child++;
		if( heap_arr[child].x_cor > temp.x_cor )
			heap_arr[hole] = heap_arr[child];
		else
			return;
	}
	heap_arr[hole] = temp;
}

#endif