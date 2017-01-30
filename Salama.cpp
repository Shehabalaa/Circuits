#include "Header.h"

void Get_Current(const vector<Node>& Nodes, double& Current, int kind, int mark, int& Node1, int &Node2)
{
	//Node1,2 will be two nodes with any arrangement then they will indicate direction of curr

	double V1=0, V2=0;
	int  helping_Node = -1;
	double helping_V1=0, helping_V2=0;
	GetTwoNodesConnectedWith(Nodes, kind, mark, Node1, Node2);// get the 2 nodes connected element
	V1 = Nodes[Node1].NodeVoltage;
	V2 = Nodes[Node2].NodeVoltage;
	if (V1 < V2)
		swap(Node1, Node2); // here N1 and N2 temprorary indicate voltage directionl(high-low)

	if (kind == 1)
	{
		for (unsigned int k = 0; k < Nodes[Node1].Resistors.size(); k++)
		{
			if (Nodes[Node1].Resistors[k].mark == mark)
			{
				V1 = Nodes[Node1].NodeVoltage;//having the 1st node voltage
				V2 = Nodes[Node2].NodeVoltage;//having the 2nd node voltage

				Current = (V1 - V2) / Nodes[Node1].Resistors[k].value;//geting the voltage difference the divide by resistance value

				return;
			}
		}
	}

	else if (kind == 3) //current source
	{
		for (unsigned int k = 0; k < Nodes[Node1].J_Sources.size(); k++)

			if (Nodes[Node1].J_Sources[k].mark == mark)

			{
				Current = fabs(Nodes[Node1].J_Sources[k].value); // the current of J is it's value

				if (Nodes[Node1].J_Sources[k].value >= 0)
					swap(Node1, Node2);

				return;
			}
	}

	else if (kind == 2)//voltage source
	{
		if (Nodes[Node1].No_elements == 2)
		{
			if (int(Nodes[Node1].Resistors.size()) == 1)
			{
				helping_Node = GetSecondNode(Nodes, Node1, 1, Nodes[Node1].Resistors[0].mark);
				if (Nodes[helping_Node].NodeVoltage < Nodes[Node1].NodeVoltage)
					swap(Node1, Node2);

			}
			else if (Nodes[Node1].J_Sources.size() == 1)
			{
				if (Nodes[Node1].J_Sources[0].value < 0)
					swap(Node1, Node2);
			}
			else
			{
				helping_Node = Node1;
				int Mark = mark;

				do
				{

					if (Mark == Nodes[helping_Node].V_Sources[1].mark)
					{
						Mark = Nodes[helping_Node].V_Sources[0].mark;
						helping_Node = GetSecondNode(Nodes, helping_Node, 2, Mark);

					}
					else
					{
						Mark = Nodes[helping_Node].V_Sources[1].mark;
						helping_Node = GetSecondNode(Nodes, helping_Node, 2, Mark);

					}


				} while (int(Nodes[helping_Node].Resistors.size()) == 1 || int(Nodes[helping_Node].J_Sources.size()) == 1);

				if (int(Nodes[helping_Node].Resistors.size()) == 1)
				{
					int helping_Node2 = -1;

					helping_Node2 = GetSecondNode(Nodes, helping_Node, 1, Nodes[helping_Node].Resistors[0].mark);

					if (Nodes[helping_Node2].NodeVoltage < Nodes[helping_Node].NodeVoltage)
						swap(Node1, Node2);

				}
				else
				{

					if (Nodes[helping_Node].J_Sources[0].value < 0)
						swap(Node1, Node2);


				}

			}


		}
		else
		{

			if (Nodes[Node2].Resistors.size() == 1)
			{
				helping_Node = GetSecondNode(Nodes, Node2, 1, Nodes[Node2].Resistors[0].mark);
				if (Nodes[helping_Node].NodeVoltage > Nodes[Node2].NodeVoltage)
					swap(Node2, Node2);

			}
			else if (Nodes[Node2].J_Sources.size() == 1)
			{
				if (Nodes[Node2].J_Sources[0].value > 0)
					swap(Node2, Node2);
			}
			else
			{
				helping_Node = Node2;
				int Mark = mark;

				do
				{

					if (Mark == Nodes[helping_Node].V_Sources[1].mark)
					{

						helping_Node = GetSecondNode(Nodes, helping_Node, 2, Mark);

					}
					else
					{
						Mark = Nodes[helping_Node].V_Sources[1].mark;
						helping_Node = GetSecondNode(Nodes, helping_Node, 2, Mark);

					}


				} while (Nodes[helping_Node].Resistors.size() == 1 || Nodes[helping_Node].J_Sources.size() == 1);

				if (int(Nodes[helping_Node].Resistors.size()) == 1)
				{
					int helping_Node2 = -1;

					helping_Node2 = GetSecondNode(Nodes, helping_Node, 1, Nodes[helping_Node].Resistors[0].mark);

					if (Nodes[helping_Node2].NodeVoltage > Nodes[helping_Node].NodeVoltage)
						swap(Node1, Node2);
				}
				else
				{

					if (Nodes[helping_Node].J_Sources[0].value > 0)
						swap(Node2, Node2);


				}

			}


		}





	}



}
