// equations and Requvilat
#include "Header.h"
// circuit input test 4 1 11 5 1 7 6 3 2 2 0 1 7 6 1 8 2 3 3 -5 0 3 3 5 3 2 -2 1 12 4 0 1 12 4 1 8 2 1 11 5 0 circuit problem set b (5)
// circuit input test 5 1 7 5 3 1 4 1 3 4 0 1 3 4 1 2 1 3 2 10 0 1 2 1 3 2 -10 1 1 2 1 4 40 0 1 4 40 2 20 10 0 2 20 -10 1 7 5 3 1 -4 1 1 2 0  circuit problem set b last one
// circuit input test 6 1 1 20000 2 1 100 0 1 1 20000 1 2 80000 1 3 3000 0 1 3 3000 3 1 0.012 1 5 60000 1 6 5000 0 1 6 5000 1 7 10000 0 1 7 10000 1 5 60000 3 1 -0.012 1 4 1000 0 1 4 1000 1 2 80000 2 1 -100 0 circuit problem set c (4)
// 5 1 1 5 1 5 5 2 6 -15 3 8 -5 0 1 5 5 3 8 5 1 4 4 0 1 3 1 3 7 5 1 4 4 0 1 3 1 1 2 5 1 1 5 3 7 -5 0 1 2 5 2 6 15 0 y 1 
extern int Ref_index;


void GetNodesVoltage(vector<Node>& Nodes)// always selecting last node as ref(GroundNode) then adjust all node voltage
{

	vector<Node>FakeNodes = Nodes;
	for (unsigned int i = 0; i < FakeNodes.size(); i++)
	{
		if (FakeNodes[i].No_elements == 0)
			continue;
		for (unsigned int j = 0; j < FakeNodes[i].V_Sources.size(); j++)
			voltage_to_current(FakeNodes, FakeNodes[i].V_Sources[j].mark);
	}

	DeleteDeadNodes(FakeNodes);
	double** Matrix = new double*[int(FakeNodes.size()) - 1];
	for (unsigned int i = 0; i < FakeNodes.size() - 1; i++)
		Matrix[i] = new double[int(FakeNodes.size())];

	for (unsigned int i = 0; i < FakeNodes.size() - 1; i++)
		for (unsigned int j = 0; j < FakeNodes.size(); j++)
			Matrix[i][j] = 0;



	unsigned int k = 0;
	while (k < FakeNodes.size() - 1)//first node compare with others
	{

		for (unsigned int S = 0; S < FakeNodes[k].Resistors.size(); S++) //Sum Rs connectod to node
			Matrix[k][k] += 1 / FakeNodes[k].Resistors[S].value;

		for (unsigned int S = 0; S < FakeNodes[k].J_Sources.size(); S++) //Sum Rs connectod to node
			Matrix[k][FakeNodes.size() - 1] += FakeNodes[k].J_Sources[S].value;

		for (unsigned int i = k; i < FakeNodes.size() - 2; i++)
		{
			for (unsigned int D = 0; D < FakeNodes[k].Resistors.size(); D++)
			{
				for (unsigned int P = 0; P < FakeNodes[((i + 1) % FakeNodes.size())].Resistors.size(); P++)
					if (FakeNodes[k].Resistors[D].mark == FakeNodes[((i + 1) % FakeNodes.size())].Resistors[P].mark)
					{
						Matrix[k][(i + 1) % FakeNodes.size()] -= 1 / FakeNodes[k].Resistors[D].value;
						Matrix[(i + 1) % FakeNodes.size()][k] = Matrix[k][(i + 1) % FakeNodes.size()];
					}

			}

		}
		k++;
	}


	double* Ans = NULL;

	SolveMatrix(Matrix, int(FakeNodes.size() - 1), Ans); // solve equations

	for (unsigned int i = 0; i < FakeNodes.size() - 1;i++) // assign voltage to essential nodes
	{
		for (unsigned int j = 0; j < Nodes.size(); j++)
		{
			if (FakeNodes[i].mark == Nodes[j].mark)
				Nodes[j].NodeVoltage = Ans[i];

		}

	}

	delete[] Ans;

	for (unsigned int i = 0; i < Nodes.size(); i++) // assign voltage to non essential nodes
		if (!Nodes[i].ref&& Nodes[i].No_elements == 2 && Nodes[i].V_Sources.size())
			Nodes[i].NodeVoltage = Nodes[i].V_Sources[0].value + Nodes[GetSecondNode(Nodes, i, 2, Nodes[i].V_Sources[0].mark)].NodeVoltage;


	//assing all nodes Voltage according to orignal reference or last node as ref
	double V = 0;
	int i = 0;

	while (!Nodes[i].ref)
		i++;

	V = Nodes[i].NodeVoltage;


	for (unsigned int i = 0; i < Nodes.size(); i++) // adjust all nodes due to ref node
	{
		Nodes[i].NodeVoltage -= V;
	}

}


double GetInortonOrVth(const vector<Node>& Nodes, bool Choice, int kind, int mark)
{
	/*choice 0,1
	1.Getting Vth only and show it on screen 1 true
	2.Getting Inorton only and show it on screen 0 false

	*/
	//neccessary statments  in all cases
	double Rin = GetRin(Nodes, kind, mark);
	int Nv1 = -1, Nv2 = -1; //arrangement acording to voltage
	int Nc1 = -1, Nc2 = -1; //arrangement according to current
	double curr = 0;

	Get_Current(Nodes, curr, kind, mark, Nc1, Nc2);
	Nv1 = Nc1;
	Nv2 = Nc2;

	if (Nodes[Nv1].NodeVoltage < Nodes[Nv2].NodeVoltage)
		swap(Nv1, Nv2);
	//end
	if (Choice)
	{
		if (Nc1 == Nv1)
			return fabs(curr*Rin + Nodes[Nv1].NodeVoltage - Nodes[Nv2].NodeVoltage);
		else
			return fabs(-1 * curr*Rin + Nodes[Nv1].NodeVoltage - Nodes[Nv2].NodeVoltage);
	}
	else
	{
		if (Nc1 == Nv1)
			return fabs((fabs(curr*Rin + Nodes[Nv1].NodeVoltage - Nodes[Nv2].NodeVoltage)) / Rin);
		else
			return fabs((fabs(-1 * curr*Rin + Nodes[Nv1].NodeVoltage - Nodes[Nv2].NodeVoltage)) / Rin);
	}

}

double SuperPosition(vector<Node> newNodes, bool choice, int Source_kind, int Source_mark, int element_kind, int element_mark)
{/*two choices here
 1.current duo to one source ture 1
 2.voltage difference duo to one source false 0
 */
	DisableSourcesExceptOne(newNodes, Source_kind, Source_mark);
	for (unsigned i = 0;i < newNodes.size();i++)
	{
		newNodes[i].NodeVoltage = 0;
		newNodes[i].ref = 0;
	}
	newNodes[newNodes.size() - 1].ref = 1;

	GetNodesVoltage(newNodes);

	if (choice)
	{
		double curr = 0;
		int n1 = 0, n2 = 0;
		Get_Current(newNodes, curr, element_kind, element_mark, n1, n2);
		return curr;

	}
	else
	{
		int n1 = 0, n2 = 0;
		GetTwoNodesConnectedWith(newNodes, element_kind, element_mark, n1, n2);
		return fabs(newNodes[n1].NodeVoltage - newNodes[n2].NodeVoltage);

	}

	/*getcurrentfunction
	get voltage diff function
	*/


	return 0;
}

double GetPw(const vector<Node>& Nodes, int kind, int number)
{
	double Current = 0, Power = 0;
	double Voltage = 0;
	int Node1 = 0, Node2 = 0;

	Get_Current(Nodes, Current, kind, number, Node1, Node2);

	if (kind == 1)//resistance
	{


		for (unsigned int k = 0; k < Nodes[Node1].Resistors.size(); k++)
		{
			if (Nodes[Node1].Resistors[k].mark == number)
			{


				Power = (Current*Current)*Nodes[Node1].Resistors[k].value;


				break;
			}

		}


	}

	if (kind == 2)//V_source
	{
		for (unsigned int k = 0; k < Nodes[Node1].V_Sources.size(); k++)
		{
			if (Nodes[Node1].V_Sources[k].mark == number)
			{

				if (Nodes[Node1].V_Sources[k].value >= 0)
					Power = -1 * Current* fabs(Nodes[Node1].V_Sources[k].value);
				else
					Power = Current* fabs(Nodes[Node1].V_Sources[k].value);



				break;
			}
		}
	}

	if (kind == 3)//J_source
	{

		if (Nodes[Node1].NodeVoltage < Nodes[Node2].NodeVoltage)
			swap(Node1, Node2);

		for (unsigned int k = 0; k < Nodes[Node1].J_Sources.size(); k++)
		{
			if (Nodes[Node1].J_Sources[k].mark == number)
			{

				if (Nodes[Node1].J_Sources[k].value >= 0)

				{
					Voltage = fabs(Nodes[Node1].NodeVoltage - Nodes[Node2].NodeVoltage);
					Power = Voltage* fabs(Nodes[Node1].J_Sources[k].value);
				}
				else
				{
					Voltage = fabs(Nodes[Node1].NodeVoltage - Nodes[Node2].NodeVoltage);
					Power = -1 * Voltage* fabs(Nodes[Node1].J_Sources[k].value);

				}


				break;


			}
		}
	}


	return Power;
}

double GetRin(vector<Node>Nodes, int kind, int mark) // get R equvilant
{
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		Nodes[i].ref = 0;
		Nodes[i].NodeVoltage = 0;
	}

	DisableSourcesExceptOne(Nodes, kind, mark);//disable all sources


											   // assig current source and resistor will help to get rin as it will equal 1/(vn1-vn2)-1 and delete element of interes
	bool Temp = true;
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{


		if (kind == 1)
		{
			for (unsigned int k = 0; k < Nodes[i].Resistors.size(); k++)
			{
				if (mark == Nodes[i].Resistors[k].mark)
					if (Temp)

					{

						J j1;
						j1.mark = 111111;
						j1.value = 1;
						Nodes[i].J_Sources.push_back(j1);
						Nodes[i].Resistors.erase(Nodes[i].Resistors.begin() + k); // delete element of interesr

						Temp = false;

					}
					else
					{

						J j1;
						j1.mark = 111111;
						j1.value = -1;
						Nodes[i].J_Sources.push_back(j1);
						Nodes[i].Resistors.erase(Nodes[i].Resistors.begin() + k); // delete element of interesr

					}


			}



		}
		else if (kind == 2)
		{
			for (unsigned int k = 0; k < Nodes[i].V_Sources.size(); k++)
			{
				if (Temp)

				{

					J j1;
					j1.mark = 111111;
					j1.value = 1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + k); // delete element of interesr

					Temp = false;
				}
				else
				{

					J j1;
					j1.mark = 111111;
					j1.value = -1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + k); // delete element of interes

				}
			}


		}
		else
		{

			for (unsigned int k = 0; k < Nodes[i].J_Sources.size(); k++)
			{
				if (Temp)

				{

					J j1;
					j1.mark = 111111;
					j1.value = 1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + k); // delete element of interes
					Temp = false;

				}
				else
				{

					J j1;
					j1.mark = 111111;
					j1.value = -1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + k); // delete element of interes

				}
			}

		}



	}





	// get two nodes conected to element of interest
	int Node_A = -1;
	int Node_B = -1;
	mark = 111111;

	GetTwoNodesConnectedWith(Nodes, 3, mark, Node_A, Node_B);

	Nodes[Node_B].ref = true;

	GetNodesVoltage(Nodes);
	double Rin = fabs(Nodes[Node_A].NodeVoltage);

	// for rounding numbers 3 numbers after floating piont{ accurate} :D
	Rin = Rin * pow(10, 3);
	if (Rin - int(Rin) > 0.5)
		Rin = ceil(Rin);
	else
		Rin = floor(Rin);
	Rin = Rin / pow(10, 3);

	return Rin;


}


void Get_Current(const vector<Node>& Nodes, double& Current, int kind, int mark, int& Node1, int &Node2)
{
	//Node1,2 will be two nodes with any arrangement then they will indicate direction of curr

	double V1 = 0, V2 = 0;
	int  helping_Node = -1;
	double helping_V1 = 0, helping_V2 = 0;
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

				Current = fabs(Nodes[Node1].NodeVoltage - Nodes[helping_Node].NodeVoltage) / Nodes[Node1].Resistors[0].value;

				if (Nodes[helping_Node].NodeVoltage < Nodes[Node1].NodeVoltage)
					swap(Node1, Node2);
			}
			else if (Nodes[Node1].J_Sources.size() == 1)
			{

				Current = fabs(Nodes[Node1].J_Sources[0].value);

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

					Current = fabs(Nodes[helping_Node2].NodeVoltage - Nodes[helping_Node].NodeVoltage) / Nodes[helping_Node].Resistors[0].value;

				}
				else
				{

					if (Nodes[helping_Node].J_Sources[0].value < 0)
						swap(Node1, Node2);

					Current = fabs(Nodes[helping_Node].J_Sources[0].value);
				}

			}


		}
		else
		{

			if (Nodes[Node2].Resistors.size() == 1)
			{
				helping_Node = GetSecondNode(Nodes, Node2, 1, Nodes[Node2].Resistors[0].mark);


				Current = fabs(Nodes[Node2].NodeVoltage - Nodes[helping_Node].NodeVoltage) / Nodes[Node2].Resistors[0].value;

				if (Nodes[helping_Node].NodeVoltage > Nodes[Node2].NodeVoltage)
					swap(Node1, Node2);
			}
			else if (Nodes[Node2].J_Sources.size() == 1)
			{
				Current = fabs(Nodes[Node2].J_Sources[0].value);

				if (Nodes[Node2].J_Sources[0].value > 0)
					swap(Node1, Node2);

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

					Current = fabs(Nodes[helping_Node2].NodeVoltage - Nodes[helping_Node].NodeVoltage) / Nodes[helping_Node].Resistors[0].value;
				}
				else
				{

					if (Nodes[helping_Node].J_Sources[0].value > 0)
						swap(Node2, Node2);

					Current = fabs(Nodes[helping_Node].J_Sources[0].value);
				}

			}


		}





	}



}
