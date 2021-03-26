#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <iostream>
#include <string>
using namespace std;

//For travelled and result
struct ll_node
{
	string city;
	ll_node *next;
};

class linked_list
{
public:
	ll_node *head,*tail;

	linked_list()
	{
		head = NULL;
		tail = NULL;
	}

	//Add node th the linked list 
	void add_node(string str)
	{
		ll_node *tmp = new ll_node;
		tmp->city = str;
		tmp->next = NULL;

		if(head == NULL)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tail = tail->next;
		}
	}
	//Get the head of the linkedlist
	ll_node* gethead()
	{
		return head;
	}

	//display the linkedlist
	void display(ll_node *head)
	{
		if(head == NULL)
		{
			cout << endl;
		}
		else
		{
			/*
			cout << head->city << ", ";
			display(head->next);
			*/
			if(head->next != nullptr)
			{
				head->city += ", ";
				cout << head->city;
				display(head->next);
			}
			else
			{
				cout << head->city;
				display(head->next);
			}
		}
	}

	bool isEmpty()
	{
		return head == nullptr;
	}  
};

// The objects that we want stored in the quadtree 
struct Node
{ 
	int x;
	int y;
	string name_data; 

	// Children of this tree 
	Node *SE; //South East 
	Node *SW; //South West
	Node *NE; //North East
	Node *NW; //North West

	//constructor
	Node(int x_cor, int y_cor, string city_name_info, Node* se_node, Node* sw_node, Node* ne_node, Node* nw_node)
		: x(x_cor), y(y_cor), name_data(city_name_info), NW(sw_node), SW(sw_node), NE(ne_node), SE(se_node)
	{}

	//default constructor
	Node() 
	{} 

}; 

//quadtree class 
class Quad 
{ 
public: 
	// Contains details of node 
	Node *root; 
	// Insert a node into the quadtree 
	void insert(Node* to_insert, Node* root);  
	// Find a node in a quadtree and insert to a list
	void search(Node* root, int x_cor, int y_cor, int r, linked_list & trvl_city, linked_list & res); 

	// Print the quadtree recursively
	void pretty_print(Node* root);
}; 


#endif QUAD_TREE_H