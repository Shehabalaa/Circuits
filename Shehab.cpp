// equations and Requvilat
#include "Header.h"
// circuit input test 4 1 11 5 1 7 6 3 2 2 0 1 7 6 1 8 2 3 2 -5 0 3 3 5 3 2 -2 1 12 4 0 1 12 4 1 8 2 1 11 5 0 circuit proble set b (5)

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
	SolveMatrix(Matrix,NonOriginal.size()-1,Ans);

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

		PrintTest(Original);

		//
	

}