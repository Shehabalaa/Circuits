// equations and Requvilat
#include "Header.h"
// circuit input test 4 1 11 5 1 7 6 3 2 2 0 1 7 6 1 8 2 3 3 -5 0 3 3 5 3 2 -2 1 12 4 0 1 12 4 1 8 2 1 11 5 0 circuit problem set b (5)
// circuit input test 5 1 7 5 3 1 4 1 3 4 0 1 3 4 1 2 1 3 2 10 0 1 2 1 3 2 -10 1 1 2 1 4 40 0 1 4 40 2 20 10 0 2 20 -10 1 7 5 3 1 -4 1 1 2 0  circuit problem set b last one
extern int Ref_index;


void GetNodesVoltage(vector<Node>& Nodes )// always selecting last node as ref(GroundNode) then adjust all node voltage
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

	/*int Ref_Original_index;
	for (unsigned int i = 0; i < FakeNodes.size(); i++) // put ref node at last and save its index to birng it back
	{
		if (FakeNodes[i].ref)
		{
			Ref_Original_index = i;
			swap(FakeNodes[i], FakeNodes[int(FakeNodes.size() - 1)]);
		}
	}
	*/


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

	for (unsigned int i = 0; i < Nodes.size() - 1; i++) // assign voltage to non essential nodes
		if (Nodes[i].NodeVoltage == 0)
			Nodes[i].NodeVoltage = Nodes[i].V_Sources[0].value + Nodes[GetSecondNode(Nodes,i,2, Nodes[i].V_Sources[0].mark)].NodeVoltage;

	PrintTest(Nodes, 1);
	//assing all nodes Voltage according to orignal reference or last node as ref
	double V = Nodes[Ref_index].NodeVoltage;
	for (unsigned int i = 0; i < Nodes.size(); i++) // adjust all nodes due to ref node
	{
		Nodes[i].NodeVoltage -= V;
	}
	
}


double GetRin(vector<Node>Nodes,int kind,int mark) // get R equvilant
{


	DisableSourcesExceptOne(Nodes, kind, mark);//disable all sources


	// assig current source and resistor will help to get rin as it will equal 1/(vn1-vn2)-1 and delete element of interest
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
						R r1;
						r1.mark = 111111;
						r1.value = 1;
						Nodes[i].Resistors.push_back(r1);
						J j1;
						j1.mark = 111111;
						j1.value = 1;
						Nodes[i].J_Sources.push_back(j1);
						Nodes[i].Resistors.erase(Nodes[i].Resistors.begin() + k); // delete element of interest
						Nodes[i].No_elements++;
						Temp = false;

					}
					else
					{
						R r1;
						r1.mark = 111111;
						r1.value = 1;
						Nodes[i].Resistors.push_back(r1);
						J j1;
						j1.mark = 111111;
						j1.value = -1;
						Nodes[i].J_Sources.push_back(j1);
						Nodes[i].Resistors.erase(Nodes[i].Resistors.begin() + k); // delete element of interest
						Nodes[i].No_elements++;
					}


			}



		}
		else if (kind == 2)
		{
			for (unsigned int k = 0; k < Nodes[i].V_Sources.size(); k++)
			{
				if (Temp)

				{
					R r1;
					r1.mark = 111111;
					r1.value = 1;
					Nodes[i].Resistors.push_back(r1);
					J j1;
					j1.mark = 111111;
					j1.value = 1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + k); // delete element of interest
					Nodes[i].No_elements++;
					Temp = false;
				}
				else
				{
					R r1;
					r1.mark = 111111;
					r1.value = 1;
					Nodes[i].Resistors.push_back(r1);
					J j1;
					j1.mark = 111111;
					j1.value = -1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + k); // delete element of interes
					Nodes[i].No_elements++;
				}
			}


		}
		else
		{
			
			for (unsigned int k = 0; k < Nodes[i].J_Sources.size(); k++)
			{
				if (Temp)

				{
					R r1;
					r1.mark = 111111;
					r1.value = 1;
					Nodes[i].Resistors.push_back(r1);
					J j1;
					j1.mark = 111111;
					j1.value = 1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + k); // delete element of interes
					Temp = false;
					Nodes[i].No_elements++;
				}
				else
				{
					R r1;
					r1.mark = 111111;
					r1.value = 1;
					Nodes[i].Resistors.push_back(r1);
					J j1;
					j1.mark = 111111;
					j1.value = -1;
					Nodes[i].J_Sources.push_back(j1);
					Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + k); // delete element of interes
					Nodes[i].No_elements++;
				}
			}

		}



	}





	// get two nodes conected to element of interest
	int Node_A = -1;
	int Node_B = -1;
	mark = 111111;
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{


		for (unsigned int k = 0; k < Nodes[i].Resistors.size(); k++)
		{
			if (mark == Nodes[i].Resistors[k].mark)
				if (Node_A == -1)
					Node_A = i;
				else
					Node_B = i;
		}

	}

	Nodes[Node_B].ref = true;

	GetNodesVoltage(Nodes);
	double Rin = 1/(Nodes[Node_A].NodeVoltage- 1);
	if (Rin < 0)
		Rin*=-1;
	Rin--;

// for rounding numbers 3 numbers after floating piont{ accurate} :D
	Rin = Rin * pow(10, 3);
	if (Rin - int(Rin) > 0.5)
		Rin = ceil(Rin);
	else 
		Rin = floor(Rin);
	Rin = Rin / pow(10, 3);

return Rin;


}


void DisableSourcesExceptOne(vector<Node>& Nodes,int kind,int mark) // This one can be element of interst in Rin  or a source in superpostion
{
	// delete all current soruces except if there is one as element of interest
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		unsigned int j = 0;
		while (j <Nodes[i].J_Sources.size())
		{
			if (Nodes[i].J_Sources[j].mark != mark&&kind==3)
			{
				Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + j);
				Nodes[i].No_elements--;
				continue;
			}

			j++;
		}
	}


		DeleteDeadBranches(Nodes);

	// delete all voltage soruces as short circuit
	// 2 steps firstly adjust nodes some (nodes will be marked then deleted)
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		if (Nodes[i].No_elements == 0)
			continue;
		for (unsigned int v = 0; v < Nodes[i].V_Sources.size(); v++)
		{
			if (Nodes[i].V_Sources[v].mark == mark)
				continue;
			for (unsigned int N2 = i; N2 < Nodes.size() - 1; N2++)
			{
				if (Nodes[(N2 + 1) % Nodes.size()].No_elements == 0)
					continue;

				for (unsigned int v2 = 0; v2<Nodes[(N2 + 1) % Nodes.size()].V_Sources.size(); v2++)
				{
					if (Nodes[i].V_Sources[v].mark == Nodes[(N2 + 1) % Nodes.size()].V_Sources[v2].mark)
					{

						for (unsigned int CSs = 0; CSs<Nodes[(N2 + 1) % Nodes.size()].J_Sources.size(); CSs++)
						{
							Nodes[i].J_Sources.push_back(Nodes[(N2 + 1) % Nodes.size()].J_Sources[CSs]);
							Nodes[i].No_elements++;
						}

						for (unsigned int Rs = 0; Rs<Nodes[(N2 + 1) % Nodes.size()].Resistors.size(); Rs++)
						{
							Nodes[i].Resistors.push_back(Nodes[(N2 + 1) % Nodes.size()].Resistors[Rs]);
							Nodes[i].No_elements++;
						}


						Nodes[(N2 + 1) % Nodes.size()].No_elements = 0;


					}

				}
			}

		}

	}

	DeleteDeadNodes(Nodes); //delte nodes -> look at line 362
	// secondly:
	// delete all voltage soruces except if there is one as element of interest
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		unsigned int j = 0;
		while (j <Nodes[i].V_Sources.size() && kind == 2)
		{
			if (Nodes[i].V_Sources[j].mark != mark)
			{
				Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + j);
				Nodes[i].No_elements--;
				continue;
			}

			j++;
		}
	}

}


void DeleteDeadNodes(vector<Node>& Nodes) // will delete any nodes marked before as they become disconnet with circuit
{
	unsigned int i = 0;
	while (i <Nodes.size())
	{
		if (Nodes[i].No_elements == 0)
		{
			Nodes.erase(Nodes.begin() + i);
			continue;
		}
		i++;
	}

}

void DeleteDeadBranches(vector<Node>& Nodes)
{	// Mark Nodes connected wth air to delete them :D
	bool NewCircuitReady = false;
	while (!NewCircuitReady)
	{
		NewCircuitReady = true;
		for (unsigned int i = 0; i < Nodes.size(); i++)
		{


			if (Nodes[i].No_elements == 1)
			{
				NewCircuitReady = false;

				if (Nodes[i].Resistors.size() == 1)
				{
					for (unsigned int k = i; k < Nodes.size() - 1; k++)
					{

						for (unsigned int D = 0; D < Nodes[(k + 1) % Nodes.size()].Resistors.size(); D++)
						{
							if (Nodes[i].Resistors[0].mark == Nodes[(k + 1) % Nodes.size()].Resistors[D].mark)
							{
								Nodes[i].No_elements = 0;
								Nodes[(k + 1) % Nodes.size()].No_elements--;
								Nodes[(k + 1) % Nodes.size()].Resistors.erase(Nodes[(k + 1) % Nodes.size()].Resistors.begin() + D);
								break;
							}
						}
						if (Nodes[i].No_elements == 0)
							break;

					}

				}
				else if (Nodes[i].J_Sources.size() == 1)
				{

					for (unsigned int k = i; k < Nodes.size() - 1; k++)
					{
						for (unsigned int D = 0; D < Nodes[(k + 1) % Nodes.size()].J_Sources.size(); D++)
						{
							if (Nodes[i].J_Sources[0].mark == Nodes[(k + 1) % Nodes.size()].J_Sources[D].mark)
							{
								Nodes[i].No_elements = 0;
								Nodes[(k + 1) % Nodes.size()].No_elements--;
								Nodes[(k + 1) % Nodes.size()].J_Sources.erase(Nodes[(k + 1) % Nodes.size()].J_Sources.begin() + D);
								break;
							}
						}

						if (Nodes[i].No_elements == 0)
							break;
					}

				}
				else if (Nodes[i].V_Sources.size() == 1)
				{
					for (unsigned int k = i; k < Nodes.size() - 1; k++)
					{
						for (unsigned int D = 0; D < Nodes[(i + 1) % Nodes.size()].V_Sources.size(); D++)
						{
							if (Nodes[i].J_Sources[0].mark == Nodes[(k + 1) % Nodes.size()].J_Sources[D].mark)
							{
								Nodes[i].No_elements = 0;
								Nodes[(k + 1) % Nodes.size()].No_elements--;
								Nodes[(k + 1) % Nodes.size()].V_Sources.erase(Nodes[(k + 1) % Nodes.size()].V_Sources.begin() + D);
								break;
							}
						}
						if (Nodes[i].No_elements == 0)
							break;
					}


				}


			}


		}


	}

	//Delete Nodes connected wth air
	DeleteDeadNodes(Nodes);}

int GetSecondNode(const vector<Node>& Nodes,int Node1_index,int kind,int mark)
{
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		if (i == Node1_index)
			continue;

		if (kind == 1)
			for (unsigned int j = 0; j < Nodes[i].Resistors.size(); j++)
			{
				if (Nodes[i].Resistors[j].mark == mark)
					return i;
			}

		else if (kind ==2)
			for (unsigned int j = 0; j < Nodes[i].V_Sources.size(); j++)
			{
				if (Nodes[i].V_Sources[j].mark == mark)
					return i;
			}
		else
		{
			for (unsigned int j = 0; j < Nodes[i].J_Sources.size(); j++)
			{
				if (Nodes[i].J_Sources[j].mark == mark)
					return i;
			}
		}


	}
	return -1;
}


void GetTwoNodesConnectedWith(const vector<Node>& Nodes,int kind, int mark,int &N1,int &N2)
{
	N1 = -1; ////
	N2 = -1; ////
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		if (kind == 1)
			for (unsigned int j = 0; j < Nodes[i].Resistors.size(); j++)
			{
				if (Nodes[i].Resistors[j].mark == mark)
				{
					if (N1 == -1)
						N1 = i;
					else
					{
						N2 = i;
						return;
					}
				}
				
			}

		else if (kind == 2)
			for (unsigned int j = 0; j < Nodes[i].V_Sources.size(); j++)
			{
				if (Nodes[i].V_Sources[j].mark == mark)
				{
					if (N1 == -1)
						N1 = i;
					else
					{
						N2 = i;
						return;
					}
				}

			}
		else
		{
			for (unsigned int j = 0; j < Nodes[i].J_Sources.size(); j++)
			{
				if (Nodes[i].J_Sources[j].mark == mark)
				{
					if (N1 == -1)
						N1 = i;
					else
					{
						N2 = i;
						return;
					}
				}

			}
		}


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
			return (fabs(curr*Rin + Nodes[Nv1].NodeVoltage - Nodes[Nv2].NodeVoltage))*Rin;
		else
			return (fabs(-1 * curr*Rin + Nodes[Nv1].NodeVoltage - Nodes[Nv2].NodeVoltage))*Rin;
	}

}



double SuperPosition(vector<Node> newNodes,bool choice, int Source_kind,int Source_mark , int element_kind,int element_mark)
{/*two choices here
 1.current duo to one source ture 1
 2.voltage difference duo to one source false 0
 */
	DisableSourcesExceptOne(newNodes, Source_kind, Source_mark);
	GetNodesVoltage(newNodes);

	if (choice)
	{
		double curr=0;
		int n1=0, n2=0;
		Get_Current(newNodes, curr, element_mark, element_kind, n1, n2);
		return curr;
		
	}
	else
	{
		int n1=0, n2=0;
		GetTwoNodesConnectedWith(newNodes, element_kind, element_mark, n1, n2);
		return fabs(newNodes[n1].NodeVoltage - newNodes[n2].NodeVoltage);

	}

	/*getcurrentfunction
	get voltage diff function
	*/


	return 0;
}

