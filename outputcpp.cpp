#include"Header.h"
void output(vector<Node>& Nodes)
{

	int Choice = 0;int EquivChoice = 0;int Response_Choice = 0;int Regular_Response = 0;
	double Current = 0;int Node1 = 0, Node2 = 0;int Break = 0;double Voltage = 0, Power = 0, Pmax = 0, Rmax = 0;
	int n1 = -1, n2 = -1; int First_Node = -1, Second_Node = -1; double Voltage_Difference = -1;char element = -1;
	while (1)
	{
		system("CLS");
		cout << "Please Enter The Coressponding number to a required output:\n";
		cout << "Is The Required a Response OR an Equivalent Circuit ?" << endl;
		cout << "1.Respone in Circuit:\n" << "2.Equivalent Circuit:\n"<<"3.PowerBalanceCheck:\n";
		cin >> Choice;
		system("cls");
		if (Choice == 2)
		{

			cout << "For Thevenin Circuit Enter: 1 \n" << "For Norton Circuit Enter: 2 \n";
			cin >> EquivChoice;



			if (EquivChoice == 1)
			{
				cout << "Enter the element of interest kind and number:" << endl;
				cout << "1.Res" << endl << "2.V_source" << endl << "3.C_source\n";
				int kind = 0;
				int number = 0;
				cout << "kind =";
				cin >> kind;
				cout << "number ="; cin >> number;

				double vth = GetInortonOrVth(Nodes, 1, kind, number);
				double rth = GetRin(Nodes, kind, number);
				cout << "Vth= " << vth << endl;
				cout << "Rth= " << rth << endl;
				cout << "Press Enter To Continue:";
				cin.ignore();
				cin.get();

			}

			else if (EquivChoice == 2)
			{
				cout << "Enter the element of interest kind and number" << endl;
				cout << "1.Res" << endl << "2.V_source" << endl << "3.C_source\n";
				int kind = 0;
				cout << "kind =";
				cin >> kind;
				cout << "number ="; int number; cin >> number;

				double rn = GetRin(Nodes, kind, number);
				double in = GetInortonOrVth(Nodes, 0, kind, number);

				cout << "R_Nort= " << rn << endl;
				cout << "I_Nort=" << in << endl;
				cout << "Press Enter To Continue:";
				cin.ignore();
				cin.get();

			}

		}
		else if (Choice == 1)
		{
			cout << "Please Enter The Coressponding number to a required output:\n";
			cout << "1.For Regular Response:\n" << "2.For Response due to One Source (SuperPosition):\n";
			cin >> Response_Choice;
			if (Response_Choice == 1)
			{
				while (1)
				{
					system("CLS");
					cout << "Select corresponding No. OF Response:" << endl;
					cout << "1.Current \n" << "2.Voltage \n" << "3.Power \n" << "4.Rmax & Pmax \n ";
					cin >> Regular_Response;
					if (Regular_Response == 1)//for Current i do that
					{
						while (1)
						{
							system("CLS");
							cout << "Enter element's Kind and number to get current in that element: \n";
							cout << "1.Resistance\n" << "2.VoltageSourse\n" << "3.Current.Sourse\n";
							int kind = 0;
							cout << "kind =";
							cin >> kind;
							int number;
							cout << "number = ";
							cin >> number;
							cout << endl;
							Get_Current(Nodes, Current, kind, number, Node1, Node2);
							cout << "Current= " << Current << "\n" << "Current flows from Node " << Nodes[Node1].mark + 1 << " to Node " << Nodes[Node2].mark + 1 << endl;
							cout << "To choose another Response Enter 0\n";
							cout << "To continue Getting Current Enter 1\n";
							cin >> Break;
							if (Break == 0)
								break;

						}
					}
					else if (Regular_Response == 2)//for voltage i first ask an element voltage or voltage difference between 2 nodes
					{
						while (1)
						{
							system("CLS");
							cout << "Please Enter Two Nodes to Get voltage difference:" << endl;
							cout << "Node1 =";
							cin >> Node1;
							cout << endl << "Node2 =";
							cin >> Node2;
							cout << endl;

							Voltage_Difference = Nodes[Node1 - 1].NodeVoltage - Nodes[Node2 - 1].NodeVoltage;
							cout << "Node1_Voltage-Node2_Voltage = " << Voltage_Difference;

							cout << "\nTo choose another Response Enter 0\n";
							cout << "To continue Getting Voltage Enter 1 " << endl;
							cin >> Break;
							if (Break == 0) break;


						}

					}

					else if (Regular_Response == 3)//power
					{

						while (1)
						{
							system("CLS");
							cout << "Enter Element's Kind and number to get power in that element\n";
							cout << "Select  No. OF element " << endl;
							cout << "1.Resistance\n" << "2.V_Sourse\n" << "3.C_Sourse\n";
							int kind = 0;
							int number = 0;
							cout << "kind =";
							cin >> kind;
							cout << endl;
							cout << "number= \n";
							cin >> number;

							Power = GetPw(Nodes, kind, number);
							

							cout << "Power= " << Power << "\n";
							cout << "To choose another Response Enter 0\n";
							cout << "To continue Getting Power Enter 1\n";
							cin >> Break;
							if (Break == 0) break;



						}
					}
					else if (Regular_Response == 4) //Rmax & Pmax
					{
						while (1)
						{
							system("CLS");
							cout << "Enter Element of interest Kind and number to get Rmax & Pmax \n";
							cout << "Select  No. OF element " << endl;
							cout << "1.Resistance\n" << "2.V_Sourse\n" << "3.C_Sourse\n";
							int kind;
							cout << "kind=";
							cin >> kind;
							cout << endl;
							cout << "number= \n"; int number;
							cin >> number;
							double vth = GetInortonOrVth(Nodes, 1, kind, number);
							double rth = GetRin(Nodes, kind, number);
							double pmax = (pow(vth, 2)) / (4 * rth);
							cout << "Pmax = " << pmax << endl;
							cout << "Rmax =" << rth << endl;

							cout << "To choose another Response Enter 0 To continue Getting Pmax & Rmax Enter 1 " << endl;
							cin >> Break;
							if (Break == 0) break;
						}
					}
				}
			}
			else
			{
				while (1)
				{
					system("CLS");
					cout << "SuperPosition:\n";
					cout << "Enter the type of responce" << endl;
					cout << "1.current due to one source" << endl;
					cout << "2.voltage difference duo to one source" << endl;
					bool op = 0;  int type = 0;
					cin >> type;
					if (type == 1)
						op = 1;
					if (type == 2)
						op = 0;
					cout << "Enter source kind and number" << endl;
					cout << "1.V_source" << endl;
					cout << "2.C_source" << endl;
					int source_kind = 0;  int source_number = 0;
					int Res_number = 0; int ch = 0;
					cout << "Sourece_kind =";
					cin >> source_kind;
					cout << endl;
					cout << "Sourece_number =";
					cin >> source_number;
					cout << endl;

					cout << "Resistance_number = " << endl;
					cin >> Res_number;
					double responce = 0;
					responce = SuperPosition(Nodes, op, source_kind + 1, source_number, 1, Res_number);

					if (op == 1)
						cout << "current = \n" << responce;
					else if (op == 0)
						cout << "voltage = " << responce;
					cout << "To choose another Response Enter 0";
					cout<<"To Keep Using SuperPosition Enter 1" << endl;
					cin >> Break;
					if (Break == 0) break;
				}

			}

		}
		else if (Choice == 3)
		{
			ofstream outfile;
			outfile.open("PowerBalance.txt",ios::out);

			double sum = 0;
			for (unsigned i = 0;i < Nodes.size();i++)

			{
				for (unsigned k = 0;k < Nodes[i].Resistors.size();k++)
				{
					outfile << "R" << Nodes[i].Resistors[k].mark << "->>>  ";
					Power = GetPw(Nodes, 1, Nodes[i].Resistors[k].mark);
					sum += Power;
					outfile << Power << endl;
				}
				for (unsigned k = 0;k < Nodes[i].V_Sources.size();k++)
				{
					outfile << "E" << Nodes[i].Resistors[k].mark << "->>>  ";
					Power = GetPw(Nodes, 2, Nodes[i].V_Sources[k].mark);
					sum -= Power;
					outfile << Power << endl;
				}
				for (unsigned k = 0;k < Nodes[i].J_Sources.size();k++)
				{
					outfile << "J" << Nodes[i].Resistors[k].mark << "->>>  ";
					Power = GetPw(Nodes, 3, Nodes[i].J_Sources[k].mark);
					sum -= Power;
					outfile << Power << endl;
				}


			}
			outfile << "Sum =" << sum;
			cout << "Please Check PowerBalance File and Press Enter to continue:\n";
			cin.ignore();
			cin.get();

			outfile.close();
		}
	}
}