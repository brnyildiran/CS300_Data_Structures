#include <iostream> 
#include "Modified_Priority_Queue.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//comparison function for sort()
bool compare (MPQ_Obj obj1, MPQ_Obj obj2)
{
	if((obj1.x_cor < obj2.x_cor) || ((obj1.x_cor == obj2.x_cor) && (obj1.height < obj2.height)))
		return true;
	else
		return false;
}

int main()
{
	ifstream input_buildings;
	int total_buildings;
	string otherlines;
	int x1, y_height, x2;
	int i = 1;

	vector<MPQ_Obj> mpq_arr;

	//Open the file
	input_buildings.open("input.txt");

	//If cannot open the file
	if(input_buildings.fail()) 
	{
		cout<<"File cannot be opened."<<endl;
		return 0;
	}
	//Read the first line
	input_buildings >> total_buildings;

	MPQ my_mpq(total_buildings);

	MPQ_Obj ZeroStartL(0, 0, true, false, 0);
	MPQ_Obj ZeroStartR(0, 0, false, true, 0);
	mpq_arr.push_back(ZeroStartL);
	mpq_arr.push_back(ZeroStartR);

	while(getline(input_buildings, otherlines)) 
	{
		input_buildings >> x1 >> y_height >> x2;

		MPQ_Obj LeftSide(x1, y_height, true, false, i);
		MPQ_Obj RightSide(x2, y_height, false, true, i);

		mpq_arr.push_back(LeftSide);
		mpq_arr.push_back(RightSide);

		i++;
	}

	sort(mpq_arr.begin(), mpq_arr.end(), compare);


	int M = 0;
	int tmpM = -1;
	unsigned int t = 0;
	int l = 0;

	while( t < mpq_arr.size())
	{
		//t = 0;
		if(mpq_arr[l].x_cor == mpq_arr[l+1].x_cor)
		{
			if(mpq_arr[l].height < mpq_arr[l+1].height)
			{
				mpq_arr.erase(mpq_arr.begin() + l);
			}
			else
			{
				mpq_arr.erase(mpq_arr.begin() + l + 1);
			}
		}
		else
		{
			l++;
		}
		t++;
	}


	//Process and output accordingly.
	//tmpM is to store the older value of M. (to see whether it is changed)

	for(unsigned int j = 0; j < mpq_arr.size(); j++){

		if(mpq_arr[j].isLeft == true)
		{
			my_mpq.insert(mpq_arr[j]);
			M = my_mpq.GetMax();

			if(M != tmpM){
				cout<< mpq_arr[j].x_cor << " " << M <<endl; //output when M changes.
				tmpM = M;
			}
		}
		else if(mpq_arr[j].isRight == true)
		{
			my_mpq.Remove(mpq_arr[j].height);
			M = my_mpq.GetMax();

			if(M != tmpM){
				cout<< mpq_arr[j].x_cor << " " << M <<endl; //output when M changes.
				tmpM = M;
			}
		}
	}

	input_buildings.close();
	cin.get();
	cin.ignore();

	return 0;
}

