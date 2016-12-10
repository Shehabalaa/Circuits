// inputs&&check
#include "Header.h"

void Input(vector<Node>& Nodes)
{
	int n;
	cout << "How many nodes ? " << endl;
	cin >> n;
	if (n == 0)
	{
		return;
	}
	for (int i = 0;i < n;i++)
	{
		Node N;
		N.ref = false;
		N.NodeVoltage = 0;
		N.No_elements = 0;
		cout << "Node" << i+1 << endl;
		while (1)
		{
			cout << "Select corresponding No. OF element " << endl;
			cout << "1.Resistance\n" << "2.VoltageSourse\n" << "3.Current.Sourse\n" << "0.EndOfOutput\n";
			int choice;
			cin >> choice;
			if (choice == 0) break;
			if (choice == 1)
			{
				R resistor;
				cout << "Resistor_num = ";
				cin >> resistor.mark;
				cout << "Resistance_value =  ";
				cin >> resistor.value;
				N.Resistors.push_back(resistor);
			}
			else if (choice == 2)
			{
				E V_sources;
				cout << "Voltage Source_num = ";
				cin >> V_sources.mark;
				cout << "Voltage Source_value =  ";
				cin >> V_sources.value;
				N.V_Sources.push_back(V_sources);
			}
			else if (choice == 3)
			{
				J J_Source;
				cout << "Current Source_num = ";
				cin >> J_Source.mark;
				cout << "Current Source_value =  ";
				cin >> J_Source.value;
				N.J_Sources.push_back(J_Source);
			}

			
			N.No_elements++;
		}

		Nodes.push_back(N);

	}
	return;

}
/*
for (unsigned int i = 0; i < Nodes.size(); i++)
{
	for (unsigned int j = 0; j < Nodes[i].J_Sources.size(); j++)
	{
		cout << "node " << i;
		cout << Nodes[i].J_Sources[j].mark << " ";
	}


	for (unsigned int j = 0; j < Nodes[i].V_Sources.size(); j++)
	{
		cout << "node " << i;
		cout << Nodes[i].V_Sources[j].mark << " ";

	}


	for (unsigned int j = 0; j < Nodes[i].Resistors.size(); j++)
	{
		cout << "node " << i;
		cout << Nodes[i].Resistors[j].mark << " ";

	}

	int x;
	cin >> x;

	return 0;
}*/