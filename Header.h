#include<iostream>
#include<vector>
#include<cmath>
using namespace std;


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
	double NodeVoltage;
	int No_elements;
};


// FuncsPrototypes

void PrintTest(const vector<Node>&);


//Node Analysis

void GetNodesVoltage(vector<Node>,vector<Node>&);



//EquationSolver by Shehab :D

void SolveMatrix(double**, int,double*);
void swaprows(double**, int, int);


//











