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
	int mark;
	int No_elements;
};


// FuncsPrototypes

void PrintTest(const vector<Node>&);
void Input(vector<Node>&);
double GetRin(vector<Node>,int,int);
void DisableSourcesExceptOne(vector<Node>&, int, int);
void DeleteDeadNodes(vector<Node>&);
void voltage_to_current(vector<Node>&,int);


//Node Analysis

void GetNodesVoltage(vector<Node>,vector<Node>&);



//EquationSolver

void SolveMatrix(double**, int,double*&);
void swaprows(double**, int, int);
void DeallocateMatrix(double**, int);


//











