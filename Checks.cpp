// inputs
#include "Header.h"




bool inputcheck(const vector<Node> &nodes, int m, int type, double val)
{
	if (type == 1)
	{

		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			for (unsigned int j = 0; j < nodes[i].Resistors.size(); j++)
			{
				if (nodes[i].Resistors[j].mark == m && nodes[i].Resistors[j].value != (val))
				{
					cout << "error : repeated resistance mark "; cout << endl;
					return false;
				}
			}



		}
	}
	else if (type == 2)
	{

		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			for (unsigned int j = 0; j < nodes[i].V_Sources.size(); j++)
			{
				if (nodes[i].V_Sources[j].mark == m && nodes[i].V_Sources[j].value != val)
				{
					cout << "error : repeated source mark OR wrong direction"; cout << endl;
					return false;
				}
			}



		}
	}
	else if (type == 3)
	{

		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			for (unsigned int j = 0; j < nodes[i].J_Sources.size(); j++)
			{
				if (nodes[i].J_Sources[j].mark == m && nodes[i].J_Sources[j].value != val)
				{
					cout << "error : repeated source mark OR wrong direction"; cout << endl;
					return false;
				}
			}



		}
	}

	return true;
}


bool SpeacialCheck(const vector<Node> &Nodes,int &kind,int &mark,double value)
{
	kind = -1;
	mark = -1;
	bool found1 = false;
	bool found2=false;
	int N1 = -1, N2 = -1;

	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		for (unsigned int j = 0; j < Nodes[i].Resistors.size(); j++)
		{
			GetTwoNodesConnectedWith(Nodes, 1, Nodes[i].Resistors[j].mark, N1, N2);

			if (N1 ==- 1 || N2 == -1)
			{
				kind = 1;
				mark = Nodes[i].Resistors[j].mark;
				value= Nodes[i].Resistors[j].value;
				return true;
			}

		}

		for (unsigned int j = 0; j < Nodes[i].V_Sources.size(); j++)
		{



			GetTwoNodesConnectedWith(Nodes, 2, Nodes[i].V_Sources[j].mark, N1, N2);

			if (N1== - 1 || N2 == -1)
			{
				kind = 2;
				mark = Nodes[i].V_Sources[j].mark;
				value = Nodes[i].V_Sources[j].value;
				return true;
			}

		}

		for (unsigned int j = 0; j < Nodes[i].J_Sources.size(); j++)
		{


			GetTwoNodesConnectedWith(Nodes, 3, Nodes[i].J_Sources[j].mark, N1, N2);

			if (N1== - 1 || N2 == -1)
			{
				kind = 3;
				mark = Nodes[i].J_Sources[j].mark;
				value = Nodes[i].J_Sources[j].value;
				return true;
			}


		}



	}


	return false;
}