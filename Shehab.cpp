// equations and Requvilat
#include "Header.h"
// circuit input test 4 1 11 5 1 7 6 3 2 2 0 1 7 6 1 8 2 3 3 -5 0 3 3 5 3 2 -2 1 12 4 0 1 12 4 1 8 2 1 11 5 0 circuit problem set b (5)

void GetNodesVoltage(vector<Node>& Nodes)
{
	double** Matrix = new double*[int(Nodes.size())-1];
	for (unsigned int i = 0; i < Nodes.size() - 1; i++)
		Matrix[i] = new double[int(Nodes.size())];

	for (unsigned int i = 0; i < Nodes.size()-1; i++)
		for (unsigned int j = 0; j < Nodes.size(); j++)
			Matrix[i][j] = 0;

	int Ref_Original_index;
	for (unsigned int i = 0; i < Nodes.size(); i++) // put ref node at last nad save it index to birng it back
	{
		if (Nodes[i].ref)
		{
			Ref_Original_index = i;
			swap(Nodes[i], Nodes[int(Nodes.size() - 1)]);
		}
	}



	unsigned int k = 0;
	while (k < Nodes.size()-1)//first node compare with others
	{
	
		for (unsigned int S = 0; S < Nodes[k].Resistors.size(); S++) //Sum Rs connectod to node
			Matrix[k][k] += 1/Nodes[k].Resistors[S].value;

		for (unsigned int S = 0; S < Nodes[k].J_Sources.size(); S++) //Sum Rs connectod to node
			Matrix[k][Nodes.size()-1] += Nodes[k].J_Sources[S].value;

		for (unsigned int i = k; i < Nodes.size() - 2; i++)
		{
			for (unsigned int D = 0; D < Nodes[k].Resistors.size(); D++)
			{
				for (unsigned int P = 0; P < Nodes[((i + 1) % Nodes.size())].Resistors.size(); P++)
					if (Nodes[k].Resistors[D].mark == Nodes[((i + 1) % Nodes.size())].Resistors[P].mark)
					{
						Matrix[k][(i + 1) % Nodes.size()] -= 1/Nodes[k].Resistors[D].value;
						Matrix[(i + 1) % Nodes.size()][k] = Matrix[k][(i + 1) % Nodes.size()];
					}

			}

		}
		k++;
	}


	/*//Deleted later <<<<<<<<<<<<<<-------------------------------
	for (unsigned int i = 0; i < Nodes.size()-1; i++)
	{
		for (unsigned int j = 0; j < Nodes.size(); j++)
			cout << Matrix[i][j] << " ";
		cout << endl;
	}
	//
	*/
	double* Ans = NULL;
	SolveMatrix(Matrix,int(Nodes.size()-1),Ans);

	unsigned int i = 0;
	while(i < Nodes.size()-1)
	{
	
		Nodes[i].NodeVoltage = Ans[i];
		i++;
	}


	swap(Nodes[Ref_Original_index], Nodes[int(Nodes.size() - 1)]);

	delete[] Ans;
		//delete later <<<<<<<<<<<<<<-------------------------------

		//PrintTest(Nodes);

		//
	

}






double GetRin(vector<Node>Nodes,int kind,int mark) // get R equvilant
{
	// delete all current soruces except if there is one as element of interest
	for (unsigned int i = 0; i < Nodes.size(); i++) 
	{
		unsigned int j = 0;
		while( j <Nodes[i].J_Sources.size())
		{
			if (Nodes[i].J_Sources[j].mark != mark)
			{
				Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + j);
				Nodes[i].No_elements--;
				continue;
			}

			j++;
		}
	} 


	/////////////////////////////////////////////////////////////////////////////////////////////// hyzhr nodes fel hwa hyt3mlha mark wb3d keda ttshatl

	
	//mark dead nodes nodes fel hwa
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
					for (unsigned int k = i; k < Nodes.size()-1; k++)
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

	// delete on air node
	for (unsigned int i = 0; i <Nodes.size(); i++)
	{
		if (Nodes[i].No_elements == 0)
		{
			Nodes.erase(Nodes.begin() + i);
			continue;
		}
		i++;
	}

	// delete all voltage soruces as short circuit

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
	unsigned int i = 0;
		while(i <Nodes.size())
		{
			if (Nodes[i].No_elements == 0)
			{
				Nodes.erase(Nodes.begin() + i);
				continue;
			}
			i++;
		}

// delete all voltage soruces except if there is one as element of interest
		for (unsigned int i = 0; i < Nodes.size(); i++) 
		{
			unsigned int j = 0;
			while (j <Nodes[i].V_Sources.size())
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

		PrintTest(Nodes);



	// assig current source andd resistor will help to get rin ass it will equal 1/(vn1-vn2)-1 and delete element of interesr
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
						Nodes[i].Resistors.erase(Nodes[i].Resistors.begin() + k); // delete element of interesr
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
						Nodes[i].Resistors.erase(Nodes[i].Resistors.begin() + k); // delete element of interesr
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
					Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + k); // delete element of interesr
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
					Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + k); // delete element of interesr
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
					Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + k); // delete element of interesr
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
					Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + k); // delete element of interesr
					Nodes[i].No_elements++;
				}
			}

		}



	}











	for (unsigned int i = 0; i <Nodes.size(); i++)
	{
		if (Nodes[i].No_elements==0)
		{
			Nodes.erase(Nodes.begin() + i);
			continue;
		}
		i++;
	}




//	PrintTest(Nodes);

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







