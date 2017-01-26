#include "Header.h"




void main()
{
	vector<Node> Nodes;
	Input(Nodes);
	int n1, n2;
	int kind=3;
	int mark=2;
	GetTwoNodesConnectedWith(Nodes,kind,mark,n1,n2);
	GetNodesVoltage(Nodes);
	PrintTest(Nodes);
	//double Rin = GetRin(Nodes, 2, 50);
    //cout << endl << Rin << endl;
}


///////////****************///////////////////////////////////

// when we take order to get any output in such place or element in curuit we will have to check if this place or element exists or not or will cause fatal erorrs


//*************************************//////////////////////