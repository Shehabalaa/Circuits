// inputs&&check
#include "Header.h"



int Ref_index; // that is for reference node (global variable);

void Input(vector<Node>& Nodes)
{
	int n;
	cout << "How many nodes ? " << endl;
	cin >> n;
	if (n == 0)
	{
		return;
	}
	system("CLS");
	for (int i = 0;i < n;i++)
	{
		Node N;
		N.ref = false;
		N.NodeVoltage = 0;
		N.No_elements = 0;
		N.mark = i;
		while (1)
		{
			cout << "Node" << i + 1 << endl;
			cout << "Select corresponding No. OF element " << endl;
			cout << "1.Resistance\n" << "2.VoltageSource\n" << "3.Current.Source\n" << "0.EndOfOutput\n";
			int choice;
			cin >> choice;
			if (choice == 0) break;
			if (choice == 1)
			{
				R resistor;
				bool check =false;
				do {
					cout << "Resistor_num = ";
					cin >> resistor.mark;
					cout << "Resistance_value =  ";
					cin >> resistor.value;
					double s =  (resistor.value);
					check = inputcheck(Nodes, resistor.mark, 1, s);
				} while (!check);
				N.Resistors.push_back(resistor);
				
			}
			else if (choice == 2)
			{
				E V_sources;
				bool check=false;
				do {
					cout << "Voltage Source_num = ";
					cin >> V_sources.mark;
					cout << "Voltage Source_value =  ";
					cin >> V_sources.value;
					double s = (-1 * V_sources.value);
					check = inputcheck(Nodes, V_sources.mark, 2, s);
				} while (!check);
				N.V_Sources.push_back(V_sources);
			}
			else if (choice == 3)
			{
				J J_Source;
				bool check = false;
				do {
					cout << "Current Source_num = ";
					cin >> J_Source.mark;
					cout << "Current Source_value =  ";
					cin >> J_Source.value;
					double s = (-1 * J_Source.value);
					check = inputcheck(Nodes, J_Source.mark, 3, s);
				} while (!check);
				N.J_Sources.push_back(J_Source);
			}

			system("CLS");
			N.No_elements++;
		}

		Nodes.push_back(N);
		system("CLS");
	}
	
	Ref_index = int(Nodes.size() - 1);
	char choice = 'n';
	cout << "Do you want to select GroundNode(ReferenceNode)? (Y/N): if (No) last Node will be the reference in whole Program:\n";
	cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		PrintTest(Nodes,0);
		cout << "Nodes on Screen Please enter number of ground Node:\n";
		cout << "Num = ";
		cin >>  Ref_index;
		Ref_index--;
	}
	Nodes[Ref_index].ref = true;

	system("CLS");
	return;

}

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
