#ifndef QUAD_TREE_RESOURCE
#define QUAD_TREE_RESOURCE

#include <iostream>
#include <string>
#include "QuadTree.h"
using namespace std;

// Insert a node into the quadtree 
void Quad::insert(Node *tb_inserted, Node* root) 
{ 
	//if node to be inserted is empty, don't do anything, just return
	if (tb_inserted == NULL) 
		return; 

	//if position of the node to be inserted is occupied, do nothing, just return 
	if ((tb_inserted->x == root->x) && (tb_inserted->y == root->y))
		return;

	//Finding NW or SW
	if(tb_inserted->x < root->x)
	{ 
		//NW
		if (tb_inserted->y >= root->y) 
		{ 
			if (root->NW == NULL)
			{
				root->NW = new Node (tb_inserted->x, tb_inserted->y, tb_inserted->name_data, nullptr, nullptr, nullptr, nullptr); 
			}
			insert(tb_inserted, root->NW);
		} 

		//SW 
		else
		{ 
			if (root->SW == NULL)
			{
				root->SW = new Node (tb_inserted->x, tb_inserted->y, tb_inserted->name_data, nullptr, nullptr, nullptr, nullptr); 
			}
			insert(tb_inserted, root->SW);
		} 
	} 

	//Finding NE or SE
	else
	{ 
		//NE
		if (tb_inserted->y >= root->y) //belongs to northern
		{ 
			if (root->NE == NULL)
			{
				root->NE = new Node (tb_inserted->x, tb_inserted->y, tb_inserted->name_data, nullptr, nullptr, nullptr, nullptr); 
			}
			insert(tb_inserted, root->NE);
		} 

		//SE 
		else
		{ 
			if (root->SE == NULL)
			{
				root->SE = new Node (tb_inserted->x, tb_inserted->y, tb_inserted->name_data, nullptr, nullptr, nullptr, nullptr); 
			}
			insert(tb_inserted, root->SE);
		} 
	} 
} 
/*
Suppose that you have a circle centered at (x, y) with radius r and 
want to find all points in a quadtree that are in the circle. 
One idea is as follows:

Construct the bounding box inscribing the circle. 
This is the smallest rectangle containing the circle, 
which has upper-left corner (x - r, y - r) and lower-right corner (x + r, y + r). 
Any point in the circle must also be in the square, but not the other way around.

Query the quadtree for the set of points lying in that rectangle. Let these points be P.

For each point in P which is known to be in the rectangle, see if it is also in the circle.
You can do this by checking whether the distance from that point to (x, y) is no greater than r.
In other words, given a point (x0, y0), you would compute (x - x0)2 + (y - y0)2, 
and if this value is less than or equal to r2, then the point is contained in the circle.
*/

// Find a node in a quadtree 
void Quad::search(Node* root_, int x_cor, int y_cor, int r, linked_list & travelled, linked_list & result) 
{ 

	travelled.add_node(root_->name_data);
	if((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)//Is point in the circle? -> result
	{
		result.add_node(root_->name_data);
	}
	/*
	//1,2,4,9,10,11,13 -- 12 -A
	if(root_->SE != nullptr && ((root_->x <= x_cor && root_->y >= y_cor-r) || (root_->x >= x_cor && root_->x <= x_cor+r && root_->y >= y_cor) || ((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->SE, x_cor, y_cor, r, travelled, result);
	}
	//2,3,5,9,10,12,13 -- 11 -A
	if(root_->SW != nullptr && ((root_->x >= x_cor && root_->y >= y_cor-r) || (root_->x >= x_cor-r && root_->x <= x_cor && root_->y >= y_cor)||((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->SW, x_cor, y_cor, r, travelled, result);
	}
	//4,6,7,9,11,12,13 -- 10 -A
	if(root_->NE != nullptr && ((root_->x <= x_cor && root_->y <= y_cor+r) || (root_->x >= x_cor && root_->x <= x_cor+r && root_->y <= y_cor)||((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->NE, x_cor, y_cor, r, travelled, result);
	}
	//5,7,8,10,11,12,13 -- 9 -A
	if(root_->NW != nullptr && ((root_->x >= x_cor && root_->y <= y_cor+r) || (root_->x >= x_cor-r && root_->x <= x_cor && root_->y <= y_cor)||((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->NW, x_cor, y_cor, r, travelled, result);
	} */

	//1,2,4,9,10,11,13 -- 12 -A
	if(root_->SE != nullptr && ((root_->x <= x_cor && root_->y >= y_cor-r) || (root_->x >= x_cor && root_->x <= x_cor+r && root_->y >= y_cor) || ((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->SE, x_cor, y_cor, r, travelled, result);
	}
	//2,3,5,9,10,12,13 -- 11 -A
	if(root_->SW != nullptr && ((root_->x >= x_cor && root_->y >= y_cor-r) || (root_->x >= x_cor-r && root_->x <= x_cor && root_->y >= y_cor)||((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->SW, x_cor, y_cor, r, travelled, result);
	}
	//4,6,7,9,11,12,13 -- 10 -A
	if(root_->NE != nullptr && ((root_->x <= x_cor && root_->y <= y_cor+r) || (root_->x >= x_cor && root_->x <= x_cor+r && root_->y <= y_cor)||((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->NE, x_cor, y_cor, r, travelled, result);
	}
	//5,7,8,10,11,12,13 -- 9 -A
	if(root_->NW != nullptr && ((root_->x >= x_cor && root_->y <= y_cor+r) || (root_->x >= x_cor-r && root_->x <= x_cor && root_->y <= y_cor)||((((root_->x - x_cor)*(root_->x - x_cor)) + ((root_->y - y_cor)*(root_->y - y_cor))) <= r*r)))
	{
		search(root_->NW, x_cor, y_cor, r, travelled, result);
	}
}

void Quad::pretty_print(Node *root)
{
	//if the tree is not empty
	if(root != NULL)
	{
		cout << root->name_data << endl;
		pretty_print(root->SE); // recursively print the south east subtree             
		pretty_print(root->SW); // recursively print the south west subtree             
		pretty_print(root->NE); // recursively print the north east subtree             
		pretty_print(root->NW); // recursively print the north west subtree
	}
}
#endif QUAD_TREE_RESOURCE