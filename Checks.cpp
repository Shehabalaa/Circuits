// inputs
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
