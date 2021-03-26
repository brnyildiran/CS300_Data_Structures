#ifndef BOOKING_SYS_H
#define BOOKING_SYS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Hash Table Implementation with Separate Chaining
class HashTableSys
{
private:
	//row size of the hash table
	int CHAIN_ROWS;

	//column size of the hash table
	int CHAIN_COLS;

	//Vector for seats
	vector<vector<string>> v;
public:
	//Default Constructor
	HashTableSys()
	{}

	//Constructor
	HashTableSys(int rowNumber, int colNumber)
	{
		v = vector<vector<string>> (rowNumber,vector<string>(colNumber, "---"));
		this->CHAIN_ROWS = rowNumber;
		this->CHAIN_COLS = colNumber;
	}

	//Insert customer to the HashTable
	void insert(int row_index, int column_index, string customer);

	//Check if the requested place is empty or not
	bool is_seat_empty(int r, int c);

	//Cancel the reservation of the customer, remove his/her name from the HashTable
	int cancel_reservation(int current_row, int current_col, string key_tb_remove, string customer_name_org);

	//Find the seat of the customer
	int get_seat(string block_name, int current_row, vector<string> &r_names, int current_col, string key_customer_name, string customer_name_org);

	//Print the HashTable
	void display(vector<string> & block_n, vector<string> & row_n, int index);
};


//----------------------------------------------------------------------------------------------------------------------------
//For RESERVE_SEAT and RESERVE_SEAT_BY_ROW
void HashTableSys :: insert(int row_index, int column_index, string customer)
{
	if(v[row_index][column_index] == "---")
	{
		v[row_index][column_index] = customer;
	}
}

//----------------------------------------------------------------------------------------------------------------------------
//For Checking if the Given Seat is Empty or Not
bool HashTableSys :: is_seat_empty(int r, int c)
{
	bool status = true;
	if(v[r][c] != "---")
		status = false;
	return status;
}

//----------------------------------------------------------------------------------------------------------------------------
//For CANCEL_RESERVATION
int HashTableSys :: cancel_reservation(int current_row, int current_col, string key_tb_remove, string customer_name_org) 
{ 
	// If the entire column is traversed 
	if (current_col >= CHAIN_COLS) 
		return 0; 

	// If the entire row is traversed 
	if (current_row >= CHAIN_ROWS) 
		return 1; 

	// Print the value of the current cell of the matrix 
	if( v[current_row][current_col] ==  key_tb_remove)
	{
		v[current_row][current_col].pop_back();
		v[current_row][current_col] = "---";
		cout << "Cancelled the reservation of " << customer_name_org << endl;
	}

	// Recursive call to traverse the matrix in the Horizontal direction 
	if (cancel_reservation(current_row, current_col + 1, key_tb_remove, customer_name_org) == 1) 
		return 1; 

	// Recursive call for changing the row of the matrix 
	return cancel_reservation(current_row + 1, 0, key_tb_remove, customer_name_org); 
} 

//----------------------------------------------------------------------------------------------------------------------------
//For GET_SEAT
int HashTableSys :: get_seat(string block_name, int current_row, vector<string> &r_names, int current_col, string key_customer_name, string customer_name_org)
{
	// If the entire column is traversed 
	if (current_col >= CHAIN_COLS) 
		return 0; 

	// If the entire row is traversed 
	if (current_row >= CHAIN_ROWS) 
		return 1; 

	// Print the value of the current cell of the matrix 
	if( v[current_row][current_col] ==  key_customer_name)
	{
		cout << "Found that " << customer_name_org << " has a reservation in " << block_name << " " 
			<< r_names[current_row] << "-" << current_col << endl;
	}

	// Recursive call to traverse the matrix in the Horizontal direction 
	if (get_seat(block_name, current_row, r_names, current_col + 1, key_customer_name, customer_name_org) == 1) 
		return 1; 

	// Recursive call for changing the row of the matrix 
	return get_seat(block_name, current_row + 1, r_names, 0, key_customer_name, customer_name_org); 
}

//----------------------------------------------------------------------------------------------------------------------------
//For PRINT
void HashTableSys :: display(vector<string> & block_n, vector<string> & row_n, int index)
{
	// Display the contents
	cout << endl;
	cout << block_n[index] << endl;
	cout << "~~~~~~~" << endl;
	for (unsigned int i = 0; i < v.size(); i++) 
	{ 
		cout << row_n[i] << " :"; 
		for (unsigned int j = 0; j < v[i].size(); j++) 
			cout << " " << v[i][j]; 
		cout << endl; 
	}
	cout << "=======" <<endl;
}


#endif BOOKING_SYS_H