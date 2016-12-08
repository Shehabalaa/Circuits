#include<iostream>
using namespace std;
#include<vector>



struct R
{
	double value;
	int mark;
};

struct E
{
	double value;
	int mark;
};

struct J
{
	double value;
	int mark;
};


struct Node {

	vector<R> Resistors;
	vector<E> V_Sources;
	vector<J> J_Sources;
	bool ref;
};
