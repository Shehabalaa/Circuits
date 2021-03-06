#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<iomanip>

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

void PrintTest(const vector<Node>&,bool);
void Input(vector<Node>&);
double GetRin(vector<Node>,int,int);
void DisableSourcesExceptOne(vector<Node>&, int, int);
void DeleteDeadNodes(vector<Node>&);
void voltage_to_current(vector<Node>&,int);
void DeleteDeadBranches(vector<Node>& Nodes);
int GetSecondNode(const vector<Node>&, int, int, int);
void GetTwoNodesConnectedWith(const vector<Node>&, int, int, int&, int&);
double GetInortonOrVth(const vector<Node>&,bool,int,int);
double SuperPosition(vector<Node>, bool, int, int, int, int);
void Get_Current(const vector<Node>& , double&, int, int, int&, int&);
bool output(vector<Node>&);
bool inputcheck(const vector<Node>&, int , int , double );
double GetPw(const vector<Node>&, int, int);
bool SpeacialCheck(const vector<Node> &, int &, int &,double&);
//Node Analysis

void GetNodesVoltage(vector<Node>&);



//EquationSolver

void SolveMatrix(double**, int,double*&);
void swaprows(double**, int, int);
void DeallocateMatrix(double**, int);


//


