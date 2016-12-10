// equations and Requvilat
#include "Header.h"
// circuit input test 4 1 11 5 1 7 6 3 2 2 0 1 7 6 1 8 2 3 2 -5 0 3 3 5 3 2 -2 1 12 4 0 1 12 4 1 8 2 1 11 5 0 circuit problem set b (5)

void GetNodesVoltage(vector<Node>NonOriginal,vector<Node>& Original)
{
	NonOriginal[3].ref = true;// will be deleted later <<<<<<<<<<<<<<-------------------------------

	double** Matrix = new double*[int(NonOriginal.size())-1];
	for (unsigned int i = 0; i < NonOriginal.size() - 1; i++)
		Matrix[i] = new double[int(NonOriginal.size())];

	for (unsigned int i = 0; i < NonOriginal.size()-1; i++)
		for (unsigned int j = 0; j < NonOriginal.size(); j++)
			Matrix[i][j] = 0;

	unsigned int k = 0;
	while (k < NonOriginal.size()-1)//first node compare with others
	{
		if (NonOriginal[k].ref)
			continue;

		for (unsigned int S = 0; S < NonOriginal[k].Resistors.size(); S++) //Sum Rs connectod to node
			Matrix[k][k] += 1/NonOriginal[k].Resistors[S].value;

		for (unsigned int S = 0; S < NonOriginal[k].J_Sources.size(); S++) //Sum Rs connectod to node
			Matrix[k][NonOriginal.size()-1] += NonOriginal[k].J_Sources[S].value;

		for (unsigned int i = k; i < NonOriginal.size() - 2; i++)
		{
			for (unsigned int D = 0; D < NonOriginal[k].Resistors.size(); D++)
			{
				for (unsigned int P = 0; P < NonOriginal[((i + 1) % NonOriginal.size())].Resistors.size(); P++)
					if (NonOriginal[k].Resistors[D].mark == NonOriginal[((i + 1) % NonOriginal.size())].Resistors[P].mark)
					{
						Matrix[k][(i + 1) % NonOriginal.size()] -= 1/NonOriginal[k].Resistors[D].value;
						Matrix[(i + 1) % NonOriginal.size()][k] = Matrix[k][(i + 1) % NonOriginal.size()];
					}

			}

		}
		k++;
	}



	//Deleted later <<<<<<<<<<<<<<-------------------------------
	for (unsigned int i = 0; i < NonOriginal.size()-1; i++)
	{
		for (unsigned int j = 0; j < NonOriginal.size(); j++)
			cout << Matrix[i][j] << " ";
		cout << endl;
	}
	//

	double* Ans = NULL;
	SolveMatrix(Matrix,int(NonOriginal.size()-1),Ans);

	unsigned int i = 0;
	while(i < Original.size()-1)
	{
		if (Original[i].ref)
			continue;
		Original[i].NodeVoltage = Ans[i];
		i++;
	}
	delete[] Ans;
		//delete later <<<<<<<<<<<<<<-------------------------------

		//PrintTest(Original);

		//
	

}











double GetRin(vector<Node>Nodes,int kind,int mark) // get R equvilant
{
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		Nodes[i].No_elements -= int(Nodes[i].J_Sources.size());
		Nodes[i].J_Sources.clear();

	}


	// assig current source andd resistor will help to get rin ass it will equal 1/(vn1-vn2)-1

	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		bool Temp = true;

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

				}
			}


		}
		else
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

			}

		}

	}





//delete dead nodes nodes fe hwa

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
					for (unsigned int k = 0; k < Nodes.size() - 1; k++)
					{
						
						for (unsigned int D = 0; D < Nodes[(i + 1) % Nodes.size()].Resistors.size(); D++)
						{
							if (Nodes[i].Resistors[0].mark == Nodes[(i + 1) % Nodes.size()].Resistors[D].mark)
							{
								Nodes[i].No_elements = 0;
								Nodes[(i + 1) % Nodes.size()].No_elements--;
								Nodes[(i + 1) % Nodes.size()].Resistors.erase(Nodes[(i + 1) % Nodes.size()].Resistors.begin()+D);
								break;
							}
						}
						if (Nodes[i].No_elements == 0)
							break;
					}

				}
				else if (Nodes[i].J_Sources.size() == 1)
				{

					for (unsigned int k = 0; k < Nodes.size() - 1; k++)
					{
						for (unsigned int D = 0; D < Nodes[(i + 1) % Nodes.size()].J_Sources.size(); D++)
						{
							if (Nodes[i].J_Sources[0].mark == Nodes[(i + 1) % Nodes.size()].J_Sources[D].mark)
							{
								Nodes[i].No_elements = 0;
								Nodes[(i + 1) % Nodes.size()].No_elements--;
							}
						}

					}

				}
				else if (Nodes[i].V_Sources.size() == 1)
				{
					for (unsigned int k = 0; k < Nodes.size() - 1; k++)
					{
						for (unsigned int D = 0; D < Nodes[(i + 1) % Nodes.size()].V_Sources.size(); D++)
						{
							if (Nodes[i].V_Sources[0].mark == Nodes[(i + 1) % Nodes.size()].V_Sources[D].mark)
							{
								Nodes[i].No_elements = 0;
								Nodes[(i + 1) % Nodes.size()].No_elements--;
							}
						}
					}

					
				}

				
			}


		}


	}



	int Deleted = 0;
	for (unsigned int i = 0; i <Nodes.size(); i++)
	{
		if (Nodes[i].No_elements==0)
		{
			Nodes.erase(Nodes.begin() + i - Deleted);
			Deleted++;
		}
	}

	PrintTest(Nodes);

	int Node_A = -1;
	int Node_B = -1;
	mark = 111111;
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{

		if (kind == 1)
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
		else if (kind == 2)
		{
			for (unsigned int k = 0; k < Nodes[i].V_Sources.size(); k++)
			{
				if (mark == Nodes[i].V_Sources[k].mark)
					if (Node_A == -1)
						Node_A = i;
					else
						Node_B = i;
			}


		}
		else
		{
			for (unsigned int k = 0; k < Nodes[i].J_Sources.size(); k++)
			{
				if (mark == Nodes[i].J_Sources[k].mark)
				{
					if (mark == Nodes[i].J_Sources[k].mark)
						if (Node_A == -1)
							Node_A = i;
						else
							Node_B = i;
				}
			}


		}

	}









	PrintTest(Nodes);


		return -1;



	

}







