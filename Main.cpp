#include "Header.h"


void main()
{
	vector<Node> Nodes;
	Input(Nodes);
	GetNodesVoltage(Nodes);
	double Ans;
	int n1, n2;

	cout << GetInortonOrVth(Nodes,0,1, 7);
	cout << GetInortonOrVth(Nodes, 0, 2,7 );
	cout << GetInortonOrVth(Nodes, 0, 3, 7);

	//PrintTest(Nodes,1);

}


///////////****************///////////////////////////////////

// when we take order to get any output in such place or element in curuit we will have to check if this place or element exists or not or will cause fatal erorrs


//*************************************//////////////////////