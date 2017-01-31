// inputs
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
				bool check = false;
				do {
					cout << "Resistor_num = ";
					cin >> resistor.mark;
					cout << "Resistance_value =  ";
					cin >> resistor.value;
					double s = (resistor.value);
					check = inputcheck(Nodes, resistor.mark, 1, s);
				} while (!check);
				N.Resistors.push_back(resistor);

			}
			else if (choice == 2)
			{
				E V_sources;
				bool check = false;
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
		PrintTest(Nodes, 0);
		cout << "Nodes on Screen Please enter number of ground Node:\n";
		cout << "Num = ";
		cin >> Ref_index;
		Ref_index--;
	}
	Nodes[Ref_index].ref = true;

	system("CLS");
	return;

}