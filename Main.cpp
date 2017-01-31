#include "Header.h"


void main()
{
	int badmark = -1;
	int badkind = -1;
	double value = -1;
	vector<Node> Nodes;
	Input(Nodes);
	if (SpeacialCheck(Nodes, badkind, badmark,value))
	{
		int num = 0;
		if (badkind == 1)
		{
			PrintTest(Nodes, 0);
			cout << "R" << badmark << "  appeared only in one Node\n";
			cout << "Please Select the Seconod Node to be inserted in:\n";
			cout << "Num =";
			cin >> num;
			R r;
			r.value = value;
			r.mark = badmark;
			Nodes[num - 1].Resistors.push_back(r);
			Nodes[num - 1].No_elements++;

		}
		else if(badkind == 2)
		{
			PrintTest(Nodes, 0);
			cout << "E" << badmark << " appeared only in one Node\n";
			cout << "Please Select the Seconod Node to be inserted in:\n";
			cout << "Num =";
			cin >> num;
			E e;
			e.value = -1*value;
			e.mark = badmark;
			Nodes[num - 1].V_Sources.push_back(e);
			Nodes[num - 1].No_elements++;


		}
		else
		{
			PrintTest(Nodes, 0);
			cout << "J" << badmark << " appeared only in one Node\n";
			cout << "Please Select the Seconod Node to be inserted in:\n";
			cout << "Num =";
			cin >> num;
			J j;
			j.value = -1 * value;
			j.mark = badmark;
			Nodes[num - 1].J_Sources.push_back(j);
			Nodes[num - 1].No_elements++;
		}

	}


	GetNodesVoltage(Nodes);
	bool x=false;
	do 
	{
		x = output(Nodes);

	} while (x);
}


///////////****************///////////////////////////////////

// when we take order to get any output in such place or element in curuit we will have to check if this place or element exists or not or will cause fatal erorrs


//*************************************//////////////////////