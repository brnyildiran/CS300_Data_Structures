#include <iostream> 
#include <string>
#include "QuadTree.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std; 

void deleteList(ll_node *&node) {
	if (!node)
		return;
	deleteList(node->next);
	delete node;
	node = nullptr;
}

int main() 
{ 
	Quad myquad;
	myquad.root = nullptr;
	string city_name, city_name_r, line_city, line_query, c1, c2;
	int x_cor_max, y_cor_max, xx, yy, x_r, y_r, x, y, x_query, y_query, r_query;
	ifstream input_cities, input_queries;

	linked_list result;
	linked_list travelled;

	input_cities.open("cities.txt");

	input_cities >> xx >> yy;
	x_cor_max = xx;
	y_cor_max = yy;

	input_cities >> city_name_r >> x_r >> y_r;
	myquad.root = new Node(x_r, y_r, city_name_r, nullptr, nullptr, nullptr, nullptr);
	cout << "Given the following cities.txt file: " << endl;

	input_cities.seekg(0);
	getline(input_cities, line_city);
	//cout << line << endl;
	//read line by line --> turn lines into nodes --> insert into the root of the quadtree
	while(input_cities >> city_name>> x >> y) 
	{
		cout << city_name << " " << x << " " << y << endl;
		if( x <= x_cor_max && y <= y_cor_max)
		{
			Node *tb_inserted_node = new Node(x, y, city_name, nullptr, nullptr, nullptr, nullptr);
			myquad.insert(tb_inserted_node, myquad.root);
		}
	}
	cout << endl;

	cout << "Thus, the following output should be printed out: " << endl;
	myquad.pretty_print( myquad.root);
	cout << endl;

	cout << "Then given the following queries.txt file: " << endl;
	input_queries.open("queries.txt");

	//Print the queries list
	while(getline(input_queries, line_query)) 
	{
		istringstream iss(line_query);
		iss >> x_query >> c1 >> y_query >> c2 >>r_query;
		cout << x_query << ", " << y_query << ", " << r_query << endl;
	}
	cout << endl;
	cout << "The output should be as follows: " << endl;

	//Return to the beginning of the file
	input_queries.clear();
	input_queries.seekg(0);
	while(getline(input_queries, line_query)) 
	{
		istringstream iss(line_query);
		iss >> x_query >> c1 >> y_query >> c2 >>r_query;
		if( x_query <= x_cor_max && y_query <= y_cor_max)
		{
			myquad.search(myquad.root, x_query, y_query, r_query, travelled, result);

			//Print the linked lists accordingly to the given query
			//Print "result" linked list
			if(result.gethead() != nullptr)
				result.display(result.head);
			else 
			{
				result.add_node("<None>");
				result.display(result.head);
			}
			deleteList(result.head);

			//Print "travelled" linked list
			travelled.display(travelled.head);	
			deleteList(travelled.head);
		}
		cout << endl;
	}
	return 0; 
} 