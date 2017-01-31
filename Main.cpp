#include "Header.h"


void main()
{
	vector<Node> Nodes;
	Input(Nodes);
	GetNodesVoltage(Nodes);
	bool x=false;
	do 
	{
		x = output(Nodes);

	} while (x);
}


///////////****************///////////////////////////////////

// when we take order to get any output in such place or element in curuit we will have to check if this place or element exists or not or will cause fatal erorrs


//*************************************//////////////////////