#include "Header.h"




void main()
{
	vector<Node> Nodes;
	Input(Nodes);
	//GetNodesVoltage(Nodes);
	double Rin = GetRin(Nodes, 1, 7);
	//cout << endl << Rin << endl;
}




// when we take order to get any output in such place or element in curuit we will have to check if this place or element exists or not or will coause fatal erorrs