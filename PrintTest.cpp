#include"Header.h"




void PrintTest(const vector<Node>& vec1) 
{
	
	for (unsigned int i = 0; i < vec1.size(); i++)
	{
		cout << "Node" << i + 1<<endl;

		
		for (unsigned int i = 0; i < vec1.size(); i++)
		{
			cout << "Resistors" << endl;
			for (unsigned int i = 0; i < vec1.size(); i++)
			{
				cout << vec1[i].Resistors[i].mark << "  " << vec1[i].Resistors[i].value;
				cout << endl;
			}
			cout << "CurrentSources" << endl;
			for (unsigned int i = 0; i < vec1.size(); i++)
			{
				cout << vec1[i].J_Sources[i].mark << "  " << vec1[i].J_Sources[i].value;
				cout << endl;
			}
			cout << "VoltageSources" << endl;
			for (unsigned int i = 0; i < vec1.size(); i++)
			{
				cout << vec1[i].V_Sources[i].mark << "  " << vec1[i].V_Sources[i].value;
				cout << endl;
			}
			cout << "NodeVoltage: ";
			cout << vec1[i].NodeVoltage <<"\t";
			cout << "N_elemnts: " << endl;

		
		}






	}



}