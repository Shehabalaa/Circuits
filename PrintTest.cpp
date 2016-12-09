#include"Header.h"




void PrintTest(const vector<Node>& vec1)
{

	for (unsigned int i = 0; i < vec1.size(); i++)
	{
		cout << "Node" << i + 1 << endl;

		if (vec1[i].No_elements == 0)
		{
			cout << "EmptyNode\n";
			continue;
		}

		cout << "Resistors" << endl;
		for (unsigned int k = 0; k < vec1[i].Resistors.size(); k++)
		{
			cout << vec1[i].Resistors[k].mark << "  " << vec1[i].Resistors[k].value;
			cout << endl;
		}
		cout << "CurrentSources" << endl;
		for (unsigned int k = 0; k < vec1[i].J_Sources.size(); k++)
		{
			cout << vec1[i].J_Sources[k].mark << "  " << vec1[i].J_Sources[k].value;
			cout << endl;
		}
		cout << "VoltageSources" << endl;
		for (unsigned int k = 0; k < vec1[i].V_Sources.size(); k++)
		{
			cout << vec1[i].V_Sources[k].mark << "  " << vec1[i].V_Sources[k].value;
			cout << endl;
		}
		cout << "NodeVoltage: ";
		cout << vec1[i].NodeVoltage << "\t";
		cout << "N_elemnts: " <<vec1[i].No_elements<< endl;


	}
}