#ifndef _MODIFIED_PRIORITY_QUEUE_H
#define _MODIFIED_PRIORITY_QUEUE_H

#include<iostream>
#include<vector>
using namespace std;

struct MPQ_Obj
{
	//left corner of the building 
	int x_cor;

	//height of the building
	int height;

	//right corner of the building
	bool isLeft;
	bool isRight;

	int label;
	//Constructor
	MPQ_Obj::MPQ_Obj(int x, int  h, bool l, bool r, int lbl) 
		: x_cor(x), height(h), isLeft(l), isRight(r), label(lbl)
	{}

	//Default Constructor
	MPQ_Obj()
	{}
};


//Modified Priority Queue
class MPQ
{
private:
	//Keeps track of the current size of the MPQ
	int current_size;

	//Heap array of the Skyline Objects
	vector<MPQ_Obj>heap_arr;

public:
	//Constructor
	MPQ(int size = 0) : heap_arr(size+1)
	{
		current_size = size;
	}

	//Destructor
	~MPQ(); 

	//Inserts an item with the given value  and label into the MPQ
	void insert(MPQ_Obj & obj);

	//Removes the value with this label and returns it
	void Remove(int label);

	//Returns the maximum value that is currently stored
	int  GetMax();

	//Check if the MPQ is empty, or not?
	bool IsEmpty() const; 

	void percolateDown (int hole);
};

#endif