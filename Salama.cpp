#include "Header.h"




void Get_Current(vector<Node> &Nodes, double& Current, int kind, int mark, int& Node1, int &Node2)//Node1,2 &
{
	double V1, V2; int series_R, helping_Node1 = -1, helping_Node2 = -1; double helping_V1, helping_V2;
	GetNodesVoltage(Nodes);
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		if (kind == 1)
		{
			for (unsigned int k = 0; k < Nodes[i].Resistors.size(); k++)
			{
				if (Nodes[i].Resistors[k].mark == mark)
				{

					GetTwoNodesConnectedWith(Nodes, kind, mark, Node1, Node2);// get the 2 nodes connected with the resistance
					for (unsigned int j = 0; j < Nodes.size(); j++)
					{
						if (j == Node1)
							V1 = Nodes[j].NodeVoltage;//having the 1st node voltage
						else if (j == Node2)
							V2 = Nodes[j].NodeVoltage;//having the 2nd node voltage
					}

					Current = fabs((fabs(V1) - fabs(V2)) / Nodes[i].Resistors[k].value);//geting the voltage difference the divide by resistance value
					if (V1<V2) swap(Node1, Node2); // if voltage of node 1 < voltage of node 2 swap them
					return;
				}
			}
		}

		else if (kind == 3)//current source
		{
			for (unsigned int k = 0; k < Nodes[i].J_Sources.size(); k++)

				if (Nodes[i].J_Sources[k].mark == mark)

				{
					Current = fabs(Nodes[i].J_Sources[k].value);// the current of J is it's value
					GetTwoNodesConnectedWith(Nodes, kind, mark, Node1, Node2);// do not check on nodes voltages as J doesnot depend on that
					for (unsigned int f = 0; f < Nodes[Node1].J_Sources.size(); k++)
					{
						if (Nodes[Node1].J_Sources[f].value == Current*-1)
							return;
						else if (Nodes[Node1].J_Sources[f].value == Current)
						{
							swap(Node1, Node2);
							return;
						}

					}




				}
		}

		else if (kind == 2)//voltage source
		{
			GetTwoNodesConnectedWith(Nodes, kind, mark, Node1, Node2);

			// getting voltage of the series resistance by its value to get Current that will be equal to E current
			for (unsigned int j = 0; j < Nodes.size(); j++)
			{
				if (j == Node1 || j == Node2)
				{
					if (Nodes[j].No_elements == 2)
					{
						for (unsigned int l = 0; l < Nodes[i].Resistors.size(); l++)
						{
							if (Nodes[j].Resistors[l].value != 0) // getting the node that having only 1 resistance and it's series with E 
								series_R = Nodes[j].Resistors[l].mark;


							GetTwoNodesConnectedWith(Nodes, 1, series_R, helping_Node1, helping_Node2);
							for (unsigned int m = 0; m < Nodes.size(); m++)
							{
								if (m == helping_Node1)
									helping_V1 = Nodes[m].NodeVoltage;
								else if (m == helping_Node2)
									helping_V2 = Nodes[m].NodeVoltage;
							}

							Current = fabs((fabs(helping_V1) - fabs(helping_V2)) / Nodes[i].Resistors[l].value);//Helping voltages are voltages of the 2 nodes connecting to the series resistance
																												// just getting the 2 nodes voltages to Get values of node 1 and node 2
							for (unsigned int z = 0; z < Nodes.size(); z++)
							{
								if (z == Node1)
									V1 = Nodes[z].NodeVoltage;
								else if (z == helping_Node2)
									V2 = Nodes[z].NodeVoltage;
							}

							if (V1 < V2) swap(Node1, Node2);
							return;
						}
					}
				}
			}
		}


	}
}
