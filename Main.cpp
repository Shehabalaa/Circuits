#include "Header.h"


void main()
{
	vector<Node> Nodes;
	Input(Nodes);
	GetNodesVoltage(Nodes);
	double current;
	int n1, n2;
	Get_Current(Nodes, current, 1, 8, n1, n2);
	cout << current<<endl;
	//PrintTest(Nodes,1);

	//double Rin = GetRin(Nodes, 2, 50);
    //cout << endl << Rin << endl;
}


///////////****************///////////////////////////////////

// when we take order to get any output in such place or element in curuit we will have to check if this place or element exists or not or will cause fatal erorrs


//*************************************//////////////////////