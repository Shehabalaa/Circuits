#include "Header.h"

void voltage_to_current(vector<Node>  &nodes, int mark)
{
	int n1 = 0, n2 = 0; int n3 = 0; double v_value = 0; int  r1 = 0; 	double j = 0; double res = 0;
	bool x = false;
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].No_elements == 0)
		{
			continue;
		}
		for (unsigned int j = 0; j < nodes[i].V_Sources.size(); j++)
		{

			if (nodes[i].V_Sources[j].mark == mark)
			{

				n1 = i;
				v_value = nodes[i].V_Sources[j].value;
				x = true;
				break;

			}
		}
		if (x)
		{
			break;
		}
	}

	x = false;
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].No_elements == 0 || i == n1)
		{
			continue;
		}
		for (unsigned int j = 0; j < nodes[i].V_Sources.size(); j++)
		{


			if (nodes[i].V_Sources[j].mark == mark)
			{

				n2 = i;
				x = true;
				break;
			}

		}
		if (x)
			break;

	}

	if (nodes[n2].No_elements == 2 && nodes[n2].Resistors.size() == 1)
	{
		r1 = nodes[n2].Resistors[0].mark;
		res = nodes[n2].Resistors[0].value;
		x = false;
		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].No_elements == 0 || i == n2)
			{
				continue;
			}
			for (unsigned int j = 0; j < nodes[i].Resistors.size(); j++)
			{


				if (nodes[i].Resistors[j].mark == r1 && i != n2)

				{
					n3 = i;
					x = true;
					break;
				}

			}
			if (x)
				break;
		}

		j = v_value / res;


		J  j_source;
		R  r;
		r.value = res;
		r.mark = r1;
		j_source.value = j;
		j_source.mark = n1 * 10 + n3;
		nodes[n2].No_elements = 0;
		nodes[n1].J_Sources.push_back(j_source);
		nodes[n1].Resistors.push_back(r);
		j_source.value *= -1;
		nodes[n3].J_Sources.push_back(j_source);

		for (unsigned int k = 0;k < nodes[n1].V_Sources.size();k++)
		{
			if (nodes[n1].V_Sources[k].mark == mark)
			{
				nodes[n1].V_Sources.erase(nodes[n1].V_Sources.begin() + k);
				break;
			}
		}
		nodes[n1].No_elements++;
		nodes[n3].No_elements++;
	}


	else

	{
		r1 = nodes[n1].Resistors[0].mark;
		res = nodes[n1].Resistors[0].value;
		x = false;
		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].No_elements == 0)
			{
				continue;
			}
			for (unsigned int j = 0; j < nodes[i].Resistors.size(); j++)
			{


				if (nodes[i].Resistors[j].mark == r1 && i != n1)

				{
					n3 = i;
					x = true;
					break;
				}

			}
			if (x)
				break;

		}


		j = v_value / res;


		J  j_source;
		R  r;
		r.value = res;
		r.mark = r1;
		j_source.value = j;
		j_source.mark = n2 * 10 + n3;
		nodes[n1].No_elements = 0;
		nodes[n3].J_Sources.push_back(j_source);
		j_source.value *= -1;
		nodes[n2].J_Sources.push_back(j_source);
		nodes[n2].Resistors.push_back(r);


		for (unsigned int k = 0;k < nodes[n2].V_Sources.size();k++)
		{
			if (nodes[n2].V_Sources[k].mark == mark)
			{
				nodes[n2].V_Sources.erase(nodes[n2].V_Sources.begin() + k);
				break;
			}
		}
		nodes[n2].No_elements++;
		nodes[n3].No_elements++;

	}
}

void DisableSourcesExceptOne(vector<Node>& Nodes, int kind, int mark) // This one can be element of interst in Rin  or a source in superpostion
{
	// delete all current soruces except if there is one as element of interest
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		unsigned int j = 0;
		while (j <Nodes[i].J_Sources.size())
		{
			if (kind != 3)
			{
				Nodes[i].J_Sources.erase(Nodes[i].J_Sources.begin() + j);
				Nodes[i].No_elements--;
				continue;
			}
			else if (Nodes[i].J_Sources[j].mark != mark)
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


			if (kind != 2)
			{
				for (unsigned int N2 = i; N2 < Nodes.size() - 1; N2++)
				{
					if (Nodes[(N2 + 1) % Nodes.size()].No_elements == 0)
						continue;

					for (unsigned int v2 = 0; v2 < Nodes[(N2 + 1) % Nodes.size()].V_Sources.size(); v2++)
					{
						if (Nodes[i].V_Sources[v].mark == Nodes[(N2 + 1) % Nodes.size()].V_Sources[v2].mark)
						{

							for (unsigned int CSs = 0; CSs < Nodes[(N2 + 1) % Nodes.size()].J_Sources.size(); CSs++)
							{
								Nodes[i].J_Sources.push_back(Nodes[(N2 + 1) % Nodes.size()].J_Sources[CSs]);
								Nodes[i].No_elements++;
							}

							for (unsigned int Rs = 0; Rs < Nodes[(N2 + 1) % Nodes.size()].Resistors.size(); Rs++)
							{
								Nodes[i].Resistors.push_back(Nodes[(N2 + 1) % Nodes.size()].Resistors[Rs]);
								Nodes[i].No_elements++;
							}


							Nodes[(N2 + 1) % Nodes.size()].No_elements = 0;


						}

					}
				}

			}
			else if (Nodes[i].V_Sources[v].mark != mark)
			{
				for (unsigned int N2 = i; N2 < Nodes.size() - 1; N2++)
				{
					if (Nodes[(N2 + 1) % Nodes.size()].No_elements == 0)
						continue;

					for (unsigned int v2 = 0; v2 < Nodes[(N2 + 1) % Nodes.size()].V_Sources.size(); v2++)
					{
						if (Nodes[i].V_Sources[v].mark == Nodes[(N2 + 1) % Nodes.size()].V_Sources[v2].mark)
						{

							for (unsigned int CSs = 0; CSs < Nodes[(N2 + 1) % Nodes.size()].J_Sources.size(); CSs++)
							{
								Nodes[i].J_Sources.push_back(Nodes[(N2 + 1) % Nodes.size()].J_Sources[CSs]);
								Nodes[i].No_elements++;
							}

							for (unsigned int Rs = 0; Rs < Nodes[(N2 + 1) % Nodes.size()].Resistors.size(); Rs++)
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
	}

	DeleteDeadNodes(Nodes); //delte nodes -> look at line 362
							// secondly:
							// delete all voltage soruces except if there is one as element of interest
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		unsigned int j = 0;
		while (j <Nodes[i].V_Sources.size())
		{
			if (kind != 2)
			{
				Nodes[i].V_Sources.erase(Nodes[i].V_Sources.begin() + j);
				Nodes[i].No_elements--;
				continue;
			}
			else if (Nodes[i].V_Sources[j].mark != mark)
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
	DeleteDeadNodes(Nodes);
}

int GetSecondNode(const vector<Node>& Nodes, int Node1_index, int kind, int mark)
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

		else if (kind == 2)
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


void GetTwoNodesConnectedWith(const vector<Node>& Nodes, int kind, int mark, int &N1, int &N2)
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
