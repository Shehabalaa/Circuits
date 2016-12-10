#include "Header.h"




void main()
{
	vector<Node> Nodes;
	Input(Nodes);
	PrintTest(Nodes);
	//GetNodesVoltage(Nodes,Nodes);
	double x = GetRin(Nodes,int kind,int mark);
	

}