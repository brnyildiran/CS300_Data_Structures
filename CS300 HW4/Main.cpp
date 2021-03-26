//BERNA YILDIRAN
//CS300 - HW4
//December 28, 2020

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Booking_Sys.h"
#include <algorithm>

using namespace std;

int Scan_Return_Index(vector<string> & vec, string key)
{
	// Scan for the element
	for (unsigned int i = 0; i < vec.size(); i++)
	{ 
		//Return the address of the element
		if (vec[i] == key) 
		{ 
			return i; 
		} 
	} 
	return 0;
}

//For sorting the vector
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b) 
{ 
	return (a.second > b.second); 
}

int main()
{
	ifstream input;
	string lines, action, info, customer_name, customer_name_new, block_name, row_name, column_name, howManyWords, requested_row;
	int block_counter = 0, row_counter = 0, number_of_cols = 0, howManyWords_count = 0, which_block, which_row, which_column;
	freopen ("output.txt","w",stdout);
	input.open("input.txt");

	vector<string>row_names;
	vector<string>block_names;
	vector<string>customer_names;

	//Operations for the first 3 line of the .txt file, which are necessary for constructing HashTable
	for (int line_no = 0; getline(input, lines) && lines != "" && line_no < 3; line_no++)
	{
		istringstream iss(lines);
		string word;

		//BLOCK Info
		if (line_no == 0)
		{
			while(iss >> word)
			{
				block_names.push_back(word);
				block_counter++;
			}
		}

		//ROW Info
		else if (line_no == 1)
		{
			while(iss >> word)
			{
				row_names.push_back(word);
				row_counter++;
			}
		}

		//COLUMN Info
		else if (line_no == 2)
		{
			while(iss >> word)
			{
				number_of_cols = stoi(word);
			}
		}
	}

	//Create the HashTables of each Block
	vector<HashTableSys> blocks;
	for(int i = 0; i < block_counter; i++)
	{
		int row = row_counter;
		int col = number_of_cols;

		blocks.push_back(HashTableSys(row, col));
	}

	//Start from the beginning of the file
	input.seekg(0);
	//Skip the first 3 line about Stadium construction info. 
	getline(input, lines);
	getline(input, lines);
	getline(input, lines);

	//START READING THE COMMANDS in the input file
	while(getline(input, lines) && lines != "")
	{
		//If the command is PRINT
		if(lines == "print")
		{
			for(unsigned int i = 0; i < blocks.size(); i++)
			{
				//Display function prints the HashTable
				blocks[i].display(block_names, row_names, i);
			}
		}

		//Inputs for RESERVE_SEAT operation
		istringstream iss2(lines);
		while (iss2 >> action >> customer_name >> block_name >> row_name >> column_name)
		{
			//If the command is RESERVE_SEAT
			if (action == "reserve_seat")
			{
				which_block = Scan_Return_Index(block_names, block_name);
				which_row = Scan_Return_Index(row_names, row_name);
				which_column = stoi(column_name);
				customer_name_new = customer_name.substr(0,3);

				//If the seat is empty and customer did not made a reservation before
				if(blocks[which_block].is_seat_empty(which_row, which_column) 
				  && find(customer_names.begin(), customer_names.end(), customer_name) == customer_names.end())
				{
					//Insert customer to the seat s/he requested
					blocks[which_block].insert(which_row, which_column, customer_name_new);
					//Print the confirmation of the operation
					cout << customer_name << " has reserved " << block_names[which_block] << " " 
						 << row_names[which_row] << "-" << which_column << endl;
					//Add customer name to the vector of customer names
					customer_names.push_back(customer_name);
				}
				else
				{
					//Seat is full or customer made a reservation before
					cout << customer_name << " could not reserve a seat!" << endl;
				}
			}
		}

		//Inputs for CANCEL_RESERVATION and GET_SEAT operation
		istringstream iss3(lines);
		while(iss3 >> action >> customer_name)
		{
			//If the command is CANCEL_RESERVATION
			customer_name_new = customer_name.substr(0,3);
			if (action == "cancel_reservation")
			{
				//If Customer made a reservation before --> Her/His name is on the customer names vector
				if (find(customer_names.begin(), customer_names.end(), customer_name) != customer_names.end())
				{
					//Visit each block, find the seat that customer reserves --> cancel the reservation
					for (unsigned int i = 0; i < blocks.size(); i++)
					{
						blocks[i].cancel_reservation(0, 0, customer_name_new, customer_name);
					}
					customer_names.erase(remove(customer_names.begin(), customer_names.end(), customer_name), customer_names.end());
				}
				else
					//If name is not in the list, print the statement
					cout << "Could not cancel the reservation for " << customer_name << "; no reservation found!" << endl;
			}

			//If the command is GET_SEAT
			if (action == "get_seat")
			{
				//Visit each block and get_seat that is requested
				for (unsigned int i = 0; i < blocks.size(); i++)
				{
					blocks[i].get_seat(block_names[i], 0, row_names, 0, customer_name_new, customer_name);
				}

				//If name is not in the list --> customer did not made a reseervation
				if (find(customer_names.begin(), customer_names.end(), customer_name) == customer_names.end())
					cout << "There is no reservation made for " << customer_name << "!" << endl;
			}
		}

		//Inputs for RESERVE_SEAT_BY_ROW operation
		istringstream iss4 (lines);
		while(iss4 >> action >> customer_name >> requested_row)
		{
			//If the command is RESERVE_SEAT_BY_ROW
			if (action == "reserve_seat_by_row")
			{
				int r, emptycounter = 0;
				vector<pair <int,int>>Priority_Blocks_Rows;
				r = Scan_Return_Index(row_names, requested_row);
				customer_name_new = customer_name.substr(0,3);


				//Find the count of empty seats in the requested row for each block
				for (unsigned int i = 0; i < blocks.size(); i++)
				{
					//Visit each colum in the requested row
					for (int c = 0; c < number_of_cols; c++)
					{
						//If seat is empty
						if(blocks[i].is_seat_empty(r,c))
						{
							emptycounter++;
						}
					}
					//Block index of the requested row - empty seat counts of the requested row in each block
					Priority_Blocks_Rows.push_back(make_pair(i, emptycounter));
					emptycounter = 0;
				}
				// Using sort() function to sort by 2nd element of pair // decreasing order
				sort(Priority_Blocks_Rows.begin(), Priority_Blocks_Rows.end(), sortbysec);

				//Start from the left-most column insert the customer if seat is empty
				int col = 0;
				while (col < number_of_cols)
				{

					//If left-most seat is empty and the customer has not made reservation before -> MAKE RESERVATION
					if(blocks[Priority_Blocks_Rows[0].first].is_seat_empty(r, col) && (find(customer_names.begin(), customer_names.end(), customer_name) == customer_names.end()))
					{
						blocks[Priority_Blocks_Rows[0].first].insert(r, col, customer_name_new);
						cout << customer_name << " has reserved " << block_names[Priority_Blocks_Rows[0].first] << " " 
							<< row_names[r] << "-" << col << " by emptiest block" << endl;
						customer_names.push_back(customer_name);
						col = number_of_cols; //break out of the loop
					}
					else
					{
						//If  the customer already has a reserved seat or an empty seat isn’t found
						if (col == number_of_cols-1 && (find(customer_names.begin(), customer_names.end(), customer_name) != customer_names.end() 
							|| !blocks[Priority_Blocks_Rows[0].first].is_seat_empty(r, col)))
						{
							cout << customer_name << " could not reserve a seat!" << endl;
						}
					}
					col++;
				}
			}
		}
	}
	fclose (stdout);
	return 0;
}