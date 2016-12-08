// inputs&&check
#include "Header.h"

int main()
{

	vector<Node> Nodes;
	int n;
	cout << "How many nodes ? " << endl;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		int choice;
		Node N;

		cout << "Node" << i << endl;
		while (1)
		{
			cout << "select corresponding No. OF element " << endl;
			cout << "1.RESISTANCE\n" << "2.VOLTAGE.SOURCE\n" << "3.CURRENT.SOURCE\n" << "0.Done";
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



		}



		Nodes.push_back(N);

	}
































	return 0;
}