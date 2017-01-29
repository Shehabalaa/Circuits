#include"Header.h"
void output(vector<Node>& Nodes)
{

	int Choice;int EquivChoice;int Response_Choice;int Regular_Response;
	double Current;int Node1, Node2;int Break;double Voltage, Power, Pmax, Rmax;
	int n1, n2; int First_Node, Second_Node; double Voltage_Difference;char element;
	while (1)

	{
		cout << "Is The Required a Response OR an Equivalent Circuit ?" << endl;
		cout << "For Respone Enter 1 \n" << "For Equivalent Circuit Enter 2 \n";
		cin >> Choice;
		system("cls");
		if (Choice == 2)
		{

			cout << "For Thevenin Circuit Enter 1 \n" << "-For Norton Circuit Enter 2 \n";
			cin >> EquivChoice;


			
			if (EquivChoice == 1)
			{
				cout << "enter the element kind and number" << endl;
				cout << "1.Res" << endl << "2.V_source" << endl << "3.C_source";
				int kind; cin >> kind; cout << "number ="; int number; cin >> number;

				double vth = GetInortonOrVth(Nodes, 1, kind, number);
				double rth = GetRin(Nodes, kind, number);
				cout << "Vth= " << vth << endl;;
			    cout << "Rth= " << rth;
				
			}

			else if (EquivChoice == 2)
			{
				cout << "enter the element kind and number" << endl;
				cout << "1.Res" << endl << "2.V_source" << endl << "3.C_source";
				int kind; cin >> kind; cout << "number ="; int number; cin >> number;
				
				double rn = GetRin(Nodes, kind, number);
				double in= GetInortonOrVth(Nodes, 0, kind, number);

				cout << "R_Nort= "<<rn<<endl;
				cout << "I_Nort="<<in;
				
			}

		}
		else if (Choice == 1)
		{
			cout << "Is The Required a Regular Response OR a Response due to a Source";
			cout << "For Regular Response Enter 1 \n" << "For Response due to One Source Enter 2 \n";
			cin >> Response_Choice;
			if (Response_Choice == 1)
			{
				while (1)
				{
					cout << "Select corresponding No. OF Response " << endl;
					cout << "1.Current \n" << "2.Voltage \n" << "3.Power \n" << "4.Rmax & Pmax \n ";
					cin >> Regular_Response;
					if (Regular_Response == 1)//for Current i do that
					{
						while (1)
						{
							cout << "Enter element's Kind and number \n";
							cout << "1.Resistance\n" << "2.VoltageSourse\n" << "3.Current.Sourse\n";
							int kind;   cout << "kind =";     cin >> kind;
							int number; cout << "Element number = \n";    cin >> number;

							Get_Current(Nodes, Current, kind, number, Node1, Node2);
							cout << "Current= " << Current << "\n" << "Current flows frome Node " << Node1 << "to Node " << Node2;
							cout << "To choose another Response Enter 0 To continue Getting Current Enter 1 ";
							cin >> Break;
							if (Break == 0) break;
						}
					}
					if (Regular_Response == 2)//for voltage i first ask an element voltage or voltage difference between 2 nodes
					{
						while (1)
						{
							GetNodesVoltage(Nodes);
							cout << "Required Element Voltage Or Voltage difference Between 2 Nodes \n";
							int V_Req;
							cout << "For Element Voltage Enter 1 \n" << "For Voltage difference Enter 2 \n";
							cin >> V_Req;
							if (V_Req == 1)
							{
								cout << "Select corresponding No. OF element " << endl;
								cout << "1.Resistance\n" << "2.Current.Sourse\n";
								int kind;        cin >> kind;

								cout << "Element number= \n";   int number;
								cin >> number;

								for (unsigned int i = 0; i < Nodes.size(); i++)
								{
									if (kind == 1)//resistance
									{
										for (unsigned int k = 0; k < Nodes[i].Resistors.size(); k++)
										{
											if (Nodes[i].Resistors[k].mark == number)
											{
												Get_Current(Nodes, Current, kind, number, Node1, Node2);

												Voltage = Current*Nodes[i].Resistors[k].value;

												cout << "Voltage= " << Voltage << "\n";
											}

										}

										if (kind == 2)//J_cource
										{
											for (unsigned int k = 0; k < Nodes[i].J_Sources.size(); k++)
											{
												if (Nodes[i].J_Sources[k].mark == number)
												{
													GetTwoNodesConnectedWith(Nodes, kind, number, n1, n2);
													Voltage = Nodes[n1].NodeVoltage - Nodes[n2].NodeVoltage;
													cout << "Voltage= " << Voltage << "\n";
												}
											}

										}
									}
								}
							}

							if (V_Req == 2)//then here if the required is the voltage difference between 2 nodes 
							{

								GetNodesVoltage(Nodes);
								cout << "Enter the number of the first node " << endl;
								cin >> First_Node;
								cout << "Enter the number of the second Node ";
								cin >> Second_Node;
								Voltage_Difference = Nodes[First_Node].NodeVoltage - Nodes[Second_Node].NodeVoltage;
							}

							cout << "To choose another Response Enter 0 To continue Getting Voltage Enter 1 ";
							cin >> Break;
							if (Break == 0) break;

						}

					}

					if (Regular_Response == 3)//power
					{
						GetNodesVoltage(Nodes);

						while (1)
						{
							cout << "Enter Element's Kind and number \n";
							cout << "Select  No. OF element " << endl;
							cout << "1.Resistance\n" << "2.V_Sourse\n" << "3.C_Sourse\n"; int kind;
							cin >> kind;
							cout << "Element number= \n"; int number;
							cin >> number;

							for (unsigned int i = 0; i < Nodes.size(); i++)
							{
								if (kind == 1)//resistance
								{
									for (unsigned int k = 0; k < Nodes[i].Resistors.size(); k++)
									{
										if (Nodes[i].Resistors[k].mark == number)
										{
											Get_Current(Nodes, Current, kind, number, Node1, Node2);

											Power = (Current*Current)*Nodes[i].Resistors[k].value;

											cout << "Power= " << Power << "\n";
										}

									}
									if (kind == 2)//V_source
									{
										for (unsigned int k = 0; k < Nodes[i].V_Sources.size(); k++)
										{
											if (Nodes[i].V_Sources[k].mark == number)
											{
												Get_Current(Nodes, Current, kind, number, Node1, Node2);
												Power = Current* Nodes[i].V_Sources[k].value;
												cout << "Power= " << Power << "\n";
											}
										}
									}

									if (kind == 3)//J_source
									{
										for (unsigned int k = 0; k < Nodes[i].J_Sources.size(); k++)
										{
											if (Nodes[i].J_Sources[k].mark == number)
											{
												GetTwoNodesConnectedWith(Nodes, kind, number, n1, n2);
												Voltage = Nodes[n1].NodeVoltage - Nodes[n2].NodeVoltage;
												Power = Voltage* Nodes[i].J_Sources[k].value;
												cout << "Power= " << Power << "\n";
											}
										}
									}
								}
							}
							cout << "To choose another Response Enter 0 To continue Getting Power Enter 1 ";
							cin >> Break;
							if (Break == 0) break;
						}

					}
					if (Regular_Response == 4) //Rmax & Pmax
					{
						while (1)
						{
							cout << "Enter Element's Kind and number \n";
							cout << "Select  No. OF element " << endl;
							cout << "1.Resistance\n" << "2.V_Sourse\n" << "3.C_Sourse\n"; int kind;
							cin >> kind;
							cout << "Element number= \n"; int number;
							cin >> number;
							double vth = GetInortonOrVth(Nodes, 1, kind, number);
							double rth = GetRin(Nodes, kind, number);
							double pmax = (pow(vth, 2)) / (4 * rth);
							cout << "Pmax = " << pmax << endl;
							cout << "Rmax =" << rth;

							cout << "To choose another Response Enter 0 To continue Getting Pmax & Rmax Enter 1 ";
							cin >> Break;
							if (Break == 0) break;
						}
					}
				}
			}
			if (Response_Choice == 1) //super position (responce duo to a source) 
			{
				cout << "enter source kind and number";
				cout << "1.V_source" << endl;
				cout << "2.C_source";
				int kind; int number;
				cin >> kind;
				cout << "number = " << number;



				// estlm ya shehab :)




			}
		}
	}
}
