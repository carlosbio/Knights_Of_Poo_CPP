// ------------------------------------------------------------------------------------------------------------	//
//																												//
// Descrição e implementação de um programa em C++ que consiste num jogo de estratégia do tipo Warcraft			//
//																												//
// Unidade curricular de Programação Orientada a Objectos 2014/2015 do curso de Engenharia Informática do ISEC	//
//																												//
// Trabalho realizado por Carlos da Silva (21220319)															//
//																												//
// Data: 06/01/2015																								//
//																												//
// ------------------------------------------------------------------------------------------------------------	//

#include "Jogo.h"

using namespace std;

void Jogo::DesenhaMapa(Consola& con,int x,int y)	// Draws the visible area of the map (45 x 81 --> 15 x 27)
{    
	con.gotoxy(1,1);

	for(int j=0;j<=50;j++)	// Clears the coordinates line
		cout<<" ";

	con.gotoxy(1,1);

	con.setTextColor(con.VERMELHO);		// Sets the text color to red

	cout<<"Coordenadas actuais: "<<(y/3)<<","<<(x/3)<<endl<<endl;	// Coordinates values truncated so they can show the square coordinates

	for(int j=0;j<=82;j++)		// Prints the top border of the map
		cout<<char(205);

	for(int i=y;i<(y+45);i++)
	{
		cout<<char(186);		// Prints the left border of the map

		for(int j=x;j<(x+81);j++)		// Cycle that prints the contents of the map
		{
			if(t.b[i][j].GetP()!=0)		// Checks if sector is visible or not
			{
				if(t.b[i][j].GetP()==1)	// Unknown sector
				{
					con.setTextColor(con.CINZENTO);	// Sets the text color to grey
					cout<<char(176);				// "Fog of war"
				}
				else if(t.b[i][j].GetP()==2)		// Open sector
				{
					if((i+j)%2==0)
						con.setTextColor(con.VERDE);		// Sets the text color to green
					else
						con.setTextColor(con.VERDE_CLARO);	// Sets the text color to light green

					cout<<char(176);
				}
				else if(t.b[i][j].GetP()==3)	// Occupied sector by unknown enemy unit or resource
				{
					con.setTextColor(con.CINZENTO);	// Sets the text color to grey
					cout<<char(176);				// "Fog of war"
				}
			}
			else if(p.size()!=0&&t.b[i][j].GetP()==0)		// Checks for existing populations		
			{
				for(unsigned int k=0;k<p.size();k++)		// Checks each population
				{
					if(p[k]->edif!=NULL)					// Check if population has buildings
					{
						for(unsigned int l=0;l<4;l++)		// Checks each type of building in the current population
						{
							if(p[k]->edif[l].size()!=0)		// If the current type is not empty
							{
								if(i%3==0)					// 1st line of object info
								{
									for(unsigned int z=0;z<p[k]->edif[l].size();z++)	// Goes through the buildings array
									{
										if((p[k]->edif[l][z]->GetX()==i)&&p[k]->edif[l][z]->GetY()==j)	// Checks the building's coordinates
										{
											if(k==0)	// Population 1
												con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
											if(k==1)	// Population 2
												con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
											if(k==2)	// Population 2
												con.setTextColor(con.ROXO);				// Sets the text color to purple
											if(k==3)	// Population 3
												con.setTextColor(con.BRANCO_CLARO);		// Sets the text color to white
											if(t.b[i][j].sector.size()>1)				// Multiple units in the sector
												con.setTextColor(con.VERMELHO);			// Sets the text color to red

											cout<<p[k]->edif[l][z]->GetId();			// Prints the building ID

											if(p[k]->edif[l][z]->GetN()<10)
												cout<<0<<p[k]->edif[l][z]->GetN();		// Prints the building order number
											else if(p[k]->edif[l][z]->GetN()>99)
												cout<<"++";								// It's over 99!!
											else
												cout<<p[k]->edif[l][z]->GetN();			// Between 10 and 99
											
										}
									}
								}
								else if((i-1)%3==0)		// 2nd line of object info
								{
									for(unsigned int z=0;z<p[k]->edif[l].size();z++)	// Goes through the building's array
									{
										if((p[k]->edif[l][z]->GetX()==i-1)&&p[k]->edif[l][z]->GetY()==j)	// Checks the building's coordinates
										{
											if(k==0)	// Population 1
												con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
											if(k==1)	// Population 2
												con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
											if(k==2)	// Population 2
												con.setTextColor(con.ROXO);				// Sets the text color to purple
											if(k==3)	// Population 3
												con.setTextColor(con.BRANCO_CLARO);		// Sets the text color to white
											if(t.b[i-1][j].sector.size()>1)				// Multiple units in the sector
												con.setTextColor(con.VERMELHO);			// Sets the text color to red

											cout<<"P"<<0<<k+1;		// Prints the population to which the building belongs
										}
									}
								}
								else if((i-2)%3==0)	// 3rd line of object info
								{
									for(unsigned int z=0;z<p[k]->edif[l].size();z++)	// Goes through the building's array
									{
										if((p[k]->edif[l][z]->GetX()==i-2)&&p[k]->edif[l][z]->GetY()==j)	// Checks the building's coordinates
										{
											if(k==0)	// Population 1
												con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
											if(k==1)	// Population 2
												con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
											if(k==2)	// Population 2
												con.setTextColor(con.ROXO);				// Sets the text color to purple
											if(k==3)	// Population 3
												con.setTextColor(con.BRANCO_CLARO);		// Sets the text color to white
											if(t.b[i-2][j].sector.size()>1)				// Multiple units in the sector
												con.setTextColor(con.VERMELHO);			// Sets the text color to red
										
											if(p[k]->edif[l][z]->GetVida()<10)
												cout<<"V"<<0<<p[k]->edif[l][z]->GetVida();	// Prints HP if less than 10
											else
												cout<<"V"<<p[k]->edif[l][z]->GetVida();		// Prints HP
										}
									}
								}
							}
						}
					}
					if(p[k]->unid!=NULL)					// Check if population has units
					{
						for(unsigned int l=0;l<5;l++)		// Checks each array of units in the current population
						{
							if(p[k]->unid[l].size()!=0)		// Checks if the unit type's array is empty
							{
								if(i%3==0)		// 1st line of object info
								{
									for(unsigned int z=0;z<p[k]->unid[l].size();z++)					// Goes through the units array
									{
										if((p[k]->unid[l][z]->GetX()==i)&&p[k]->unid[l][z]->GetY()==j)	// Checks the units' coordinates
										{
											int flagp=0;	// Occupation flag

											for(unsigned int v=0;v<t.b[i][j].sector.size();v++)	// Goes through the vector
											{
												if(p[k]->unid[l][z]==t.b[i][j].sector[v])		// Checks if the current unit exists in the sector
													flagp++;									// Signals the unit's existence

												if(v==0&&flagp==1)	// Only prints if there's a single unit in the sector and the current one exists
												{
													if(k==0)	// Population 1
														con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
													if(k==1)	// Population 2
														con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
													if(k==2)	// Population 2
														con.setTextColor(con.ROXO);				// Sets the text color to purple
													if(k==3)	// Population 3
														con.setTextColor(con.BRANCO_CLARO);		// Sets the text color to white
													if(t.b[i][j].sector.size()>1)				// Multiple units in the sector
														con.setTextColor(con.VERMELHO);			// Sets the text color to red

													cout<<p[k]->unid[l][z]->GetId();			// Prints the unit's ID

													if(p[k]->unid[l][z]->GetN()<10)
														cout<<0<<p[k]->unid[l][z]->GetN();		// Prints the unit's order number if less than 10
													else if(p[k]->unid[l][z]->GetN()>99)
														cout<<"++";								// It's over 99!!
													else
														cout<<p[k]->unid[l][z]->GetN();
												}
											}
										}
									}
								}
								else if((i-1)%3==0)		// 2nd line of object info
								{
									for(unsigned int z=0;z<p[k]->unid[l].size();z++)	// Goes through the units array
									{
										if((p[k]->unid[l][z]->GetX()==i-1)&&p[k]->unid[l][z]->GetY()==j)	// Checks the units' coordinates
										{
											int flagp=0;	// Occupation flag

											for(unsigned int v=0;v<t.b[i-1][j].sector.size();v++)	// Goes through the vector
											{
												if(p[k]->unid[l][z]==t.b[i-1][j].sector[v])			// Checks if the current unit exists in the sector
													flagp++;										// Signals the unit's existence

												if(v==0&&flagp==1)	// Only prints if there's a single unit in the sector and the current one exists
												{
													if(k==0)	// Population 1
														con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
													if(k==1)	// Population 2
														con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
													if(k==2)	// Population 2
														con.setTextColor(con.ROXO);				// Sets the text color to purple
													if(k==3)	// Population 3
														con.setTextColor(con.BRANCO_CLARO);		// Sets the text color to white
													if(t.b[i-1][j].sector.size()>1)				// Multiple units in the sector
														con.setTextColor(con.VERMELHO);			// Sets the text color to red

													cout<<"P"<<0<<k+1;							// Prints the population to which the unit belongs
												}
											}
										}
									}
								}
								else if((i-2)%3==0)	// 3rd line of object info
								{
									for(unsigned int z=0;z<p[k]->unid[l].size();z++)	// Goes through the units array
									{
										if((p[k]->unid[l][z]->GetX()==i-2)&&p[k]->unid[l][z]->GetY()==j)	// Checks the units' coordinates
										{
											int flagp=0;	// Occupation flag

											for(unsigned int v=0;v<t.b[i-2][j].sector.size();v++)	// Goes through the vector
											{
												if(p[k]->unid[l][z]==t.b[i-2][j].sector[v])			// Checks if the current unit exists in the sector
													flagp++;										// Signals the unit's existence

												if(v==0&&flagp==1)	// Only prints if there's a single unit in the sector and the current one exists
												{
													if(k==0)	// Population 1
														con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
													if(k==1)	// Population 2
														con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
													if(k==2)	// Population 2
														con.setTextColor(con.ROXO);				// Sets the text color to purple
													if(k==3)	// Population 3
														con.setTextColor(con.BRANCO_CLARO);		// Sets the text color to white
													if(t.b[i-2][j].sector.size()>1)				// Multiple units in the sector
														con.setTextColor(con.VERMELHO);			// Sets the text color to red
										
													if(p[k]->unid[l][z]->GetVida()<10)
														cout<<"V"<<0<<p[k]->unid[l][z]->GetVida();	// Prints HP if less than 10
													else
														cout<<"V"<<p[k]->unid[l][z]->GetVida();		// Prints HP
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if(f.size()!=0&&t.b[i][j].GetP()==0)		// Checks for existing resources sites
			{
				if(i%3==0)		// 1st line of object info
				{
					for(unsigned int z=0;z<f.size();z++)		// Goes through the resources array
					{
						if((f[z]->GetX()==i)&&f[z]->GetY()==j)	// Checks the site's coordinates
						{
							if(f[z]->GetId()=='M')
								con.setBackgroundColor(con.CYAN);		// If it's a mine
							if(f[z]->GetId()=='R')
								con.setBackgroundColor(con.CINZENTO);	// If it's a quarry
							if(f[z]->GetId()=='F')
								con.setBackgroundColor(con.AMARELO);	// If it's a forest

							con.setTextColor(con.PRETO);			// Sets the text color to black

							if(t.b[i][j].sector.size()>1)			// Multiple objects in the sector
								con.setTextColor(con.VERMELHO);		// Sets the text color to red

							cout<<f[z]->GetId();		// Prints the resource ID
							
							if(f[z]->GetN()<10)
								cout<<0<<f[z]->GetN();	// Prints the resource order number if less than 10
							else if(f[z]->GetN()>99)
								cout<<"++";				// Prints the resource order number if it's over 99
							else
								cout<<f[z]->GetN();		// Prints the resource order number

							con.setBackgroundColor(con.PRETO);
						}
					}
				}
				else if((i-1)%3==0)		// 2nd line of object info
				{
					for(unsigned int z=0;z<f.size();z++)	// Goes through the resources array
					{
						if((f[z]->GetX()==i-1)&&f[z]->GetY()==j)	// Checks the resource's coordinates
						{
							if(f[z]->GetId()=='M')
								con.setBackgroundColor(con.CYAN);
							if(f[z]->GetId()=='R')
								con.setBackgroundColor(con.CINZENTO);
							if(f[z]->GetId()=='F')
								con.setBackgroundColor(con.AMARELO);

							con.setTextColor(con.PRETO);			// Sets the text color to black

							if(t.b[i-1][j].sector.size()>1)			// Multiple objects in the sector
								con.setTextColor(con.VERMELHO);		// Sets the text color to red

							cout<<"   ";

							con.setBackgroundColor(con.PRETO);
						}
					}
				}
				else if((i-2)%3==0)	// 3rd line of object info
				{
					for(unsigned int z=0;z<f.size();z++)	// Goes through the resources array
					{
						if((f[z]->GetX()==i-2)&&f[z]->GetY()==j)	// Checks the resource's coordinates
						{
							if(f[z]->GetId()=='M')
								con.setBackgroundColor(con.CYAN);
							if(f[z]->GetId()=='R')
								con.setBackgroundColor(con.CINZENTO);
							if(f[z]->GetId()=='F')
								con.setBackgroundColor(con.AMARELO);

							con.setTextColor(con.PRETO);			// Sets the text color to black

							if(t.b[i-2][j].sector.size()>1)			// Multiple objects in the sector
								con.setTextColor(con.VERMELHO);		// Sets the text color to red
										
							if(f[z]->GetQuant()<10)
								cout<<"Q"<<0<<f[z]->GetQuant();		// Prints HP if less than 10
							else
								cout<<"Q"<<f[z]->GetQuant();		// Prints HP

							con.setBackgroundColor(con.PRETO);
						}
					}
				}
			}
		}

		con.setTextColor(con.VERMELHO);		// Sets the text color to red
		cout<<char(186);	// Prints the right border of the map
	}

	for(int j=0;j<=82;j++)	// Prints the bottom border of the map
		cout<<char(205);

	con.setTextColor(con.VERMELHO);
	con.gotoxy(3,75);
}

void Jogo::DesenhaInfo(Consola& con)	// Function that prints the info bar
{
	con.setTextColor(con.VERMELHO);		// Changes the text color to yellow
	con.gotoxy(1,50);					// Starting coordinates

	for(int i=0;i<81;i++)				// Prints the top limit
		cout<<"-";

	cout<<endl;

	for(int i=0;i<10;i++)				// Prints the side borders
		cout<<"|                                                                                 |";	// Exact amount of spaces

	con.gotoxy(1,61);

	for(int i=0;i<81;i++)				// Prints the bottom
		cout<<"-";

	con.gotoxy(1,63);
	cout<<" Comandos:";					// Lists the available commands
	con.setTextColor(con.VERDE);
	cout<<"   [reset] [sector] [stop] [pop] [setf] [sete] [setu] [load] [mina]";
	con.gotoxy(1,65);
	con.setTextColor(con.VERDE);
	cout<<"             [mostra]  [sair]  [sel]  [scroll]  [next]  [go]  [goto]  [ataca]";
	con.gotoxy(1,67);
	cout<<"             [conserta]  [deambula]  [mke]  [mku]  [ouro]  [pedra]  [madeira]";
}

void Jogo::Mostra(Consola& con,int pop)	// Function that writes the info
{
	if(pop==0)	// Population 1
		con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
	if(pop==1)	// Population 2
		con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
	if(pop==2)	// Population 2
		con.setTextColor(con.ROXO);				// Sets the text color to purple
	if(pop==3)	// Population 3
		con.setTextColor(con.BRANCO);			// Sets the text color to white

	con.gotoxy(2,52);
	cout<<"--> Populacao "<<pop+1<<": \""<<p[pop]->GetNome()<<"\"";	// Prints the population name

	int edifs[4]={},unids[5]={};		// Counters for the number of elements of each type

	for(unsigned int i=0;i<4;i++)		// Counts the number of buildings of each type
		for(unsigned int j=0;j<p[pop]->edif[i].size();j++)
			edifs[i]++;

	con.gotoxy(2,55);
	cout<<"Edificios - "<<"Castelos: "<<edifs[0]<<", Quarteis: "<<edifs[1]<<", Estabulos: "<<edifs[2]<<", Quintas: "<<edifs[3];

	for(unsigned int i=0;i<5;i++)		// Counts the number of units of each type
		for(unsigned int j=0;j<p[pop]->unid[i].size();j++)
			unids[i]++;

	con.gotoxy(2,57);
	cout<<"Unidades -  "<<"Soldados: "<<unids[0]<<", Camponeses: "<<unids[1]<<", C. a cavalo: "
		<<unids[2]<<", Cavaleiros: "<<unids[3]<<", Orcs: "<<unids[4];

	if(p[pop]->edif->size()!=0)
	{
		con.gotoxy(2,59);
		cout<<"Recursos -  "<<"Ouro: "<<p[pop]->edif[0][0]->GetOuro()<<", Pedra: "
			<<p[pop]->edif[0][0]->GetPedra()<<", Madeira: "<<p[pop]->edif[0][0]->GetMadeira();;		// Shows the resources available at the Castle
	}
}

void Jogo::Sector(Consola& con,int lin,int col)
{
	con.gotoxy(2,52);
	con.setTextColor(con.VERDE);
	cout<<"--> Info do sector:";
	con.gotoxy(4,55);

	int print=0;

	if(t.b[lin][col].sector.size()!=0)
	{
		if(p.size()!=0)			// Checks for existing populations		
		{
			for(unsigned int k=0;k<p.size();k++)	// Checks each population
			{
				if(p[k]->edif!=NULL)				// Check if population has buildings
				{
					for(unsigned int l=0;l<4;l++)	// Checks each type of building in the current population
					{
						if(p[k]->edif[l].size()!=0)	// If the current type is not empty
						{
							for(unsigned int z=0;z<p[k]->edif[l].size();z++)	// Goes through the building curret type array
							{
								if((p[k]->edif[l][z]->GetX()==lin)&&p[k]->edif[l][z]->GetY()==col)	// Checks the building's coordinates
								{
									if(print<14)
									{
										if(k==0)	// Population 1
											con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
										if(k==1)	// Population 2
											con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
										if(k==2)	// Population 2
											con.setTextColor(con.ROXO);				// Sets the text color to purple
										if(k==3)	// Population 3
											con.setTextColor(con.BRANCO);			// Sets the text color to white

										cout<<" ["<<p[k]->edif[l][z]->GetId();		// Prints the building ID
										cout<<0<<p[k]->edif[l][z]->GetN();			// Prints the building order number
										cout<<" P"<<0<<k+1;							// Prints the population to which the building belongs

										if(p[k]->edif[l][z]->GetVida()<10)
											cout<<" V"<<0<<p[k]->edif[l][z]->GetVida();		// Prints HP if less than 10
										else
											cout<<" V"<<p[k]->edif[l][z]->GetVida()<<"] ";	// Prints HP
									}
									else
									{
										con.gotoxy(68,59);
										cout<<" . . . ";
									}

									print++;

									if(print==5)
										con.gotoxy(4,57);
									if(print==10)
											con.gotoxy(4,59);
								}
							}
						}
					}
				}
				if(p[k]->unid!=NULL)				// Check if population has units
				{
					for(unsigned int l=0;l<5;l++)	// Checks each array of units in the current population
					{
						if(p[k]->unid[l].size()!=0)	// Checks if the unit type's array is empty
						{
							for(unsigned int z=0;z<p[k]->unid[l].size();z++)	// Goes through the units type array
							{
								if((p[k]->unid[l][z]->GetX()==lin)&&p[k]->unid[l][z]->GetY()==col)	// Checks the units' coordinates
								{
									if(print<14)
									{
										if(k==0)	// Population 1
											con.setTextColor(con.AZUL_CLARO);	// Sets the text color to light blue
										if(k==1)	// Population 2
											con.setTextColor(con.AMARELO_CLARO);// Sets the text color to light yellow
										if(k==2)	// Population 2
											con.setTextColor(con.ROXO);			// Sets the text color to purple
										if(k==3)	// Population 3
											con.setTextColor(con.BRANCO);		// Sets the text color to white
													
										cout<<" ["<<p[k]->unid[l][z]->GetId();		// Prints the unit ID

										if(p[k]->unid[l][z]->GetN()<10)
											cout<<0<<p[k]->unid[l][z]->GetN();	// Prints the unit order number if less than 10
										else
											cout<<p[k]->unid[l][z]->GetN();		// Prints the unit order number

										cout<<" P"<<0<<k+1;						// Prints the population to which the unit belongs

										if(p[k]->unid[l][z]->GetVida()<10)
											cout<<" V"<<0<<p[k]->unid[l][z]->GetVida();		// Prints HP if less than 10
										else
											cout<<" V"<<p[k]->unid[l][z]->GetVida()<<"] ";	// Prints HP
									}
									else
									{
										con.gotoxy(68,59);
										cout<<" . . . ";
									}

									print++;

									if(print==5)
										con.gotoxy(4,57);
									if(print==10)
										con.gotoxy(4,59);
								}
							}
						}
					}
				}
			}
		}
		if(f.size()!=0)
		{
			for(unsigned int i=0;i<f.size();i++)
			{
				if(f[i]->GetX()==lin&&f[i]->GetY()==col)
				{
					if(print<14)
					{
						if(f[i]->GetId()=='M')
							con.setTextColor(con.CYAN);
						if(f[i]->GetId()=='R')
							con.setTextColor(con.CINZENTO);
						if(f[i]->GetId()=='F')
							con.setTextColor(con.AMARELO);
													
						cout<<" ["<<f[i]->GetId();	// Prints the site ID

						if(f[i]->GetN()<10)
							cout<<0<<f[i]->GetN();	// Prints the site order number if less than 10
						else
							cout<<f[i]->GetN();		// Prints the site order number

						if(f[i]->GetQuant()<10)
							cout<<" --- Q"<<0<<f[i]->GetQuant();	// Prints amount available if less than 10
						else
							cout<<" --- Q"<<f[i]->GetQuant()<<"] ";	// Prints amount available
					}
					else
					{
						con.gotoxy(68,59);
						cout<<" . . . ";
					}

					print++;

					if(print==5)
						con.gotoxy(4,57);
					if(print==10)
						con.gotoxy(4,59);
				}	
			}
		}
	}
	else if(t.b[lin][col].GetP()==1)
		cout<<" Sector desconhecido";
	else
		cout<<" Sector vazio";
}

int Jogo::CriaPop(string n)	// Adds a new population to the game
{
	int flag=0;				// Flag for validation of population name

	if(p.size()==4)
		return 2;

	if(p.size()==0)			// If the vector is empty
		p.push_back(new Populacao(n));
	else
	{
		for(unsigned int i=0;i<p.size();i++)	// Checks the vector for existing names
			if(p[i]->GetNome()==n)
				flag=1;							// Flags if there's one already with that name

		if(flag==1)
			return 0;			// Returns error
		else
			p.push_back(new Populacao(n));		// Pushes the new population
	}

	return 1;					// Return success
}

int Jogo::Selecciona(Consola& con,string elem,string pop,int& x,int& y)		// Selects an element
{
	char arg1[3],arg2[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao;

	if(elem.length()!=3||pop.length()!=3)	// Checks for invalid input
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0

	if(populacao==0)	// Population 1
		con.setTextColor(con.AZUL_CLARO);		// Sets the text color to light blue
	if(populacao==1)	// Population 2
		con.setTextColor(con.AMARELO_CLARO);	// Sets the text color to light yellow
	if(populacao==2)	// Population 2
		con.setTextColor(con.ROXO);				// Sets the text color to purple
	if(populacao==3)	// Population 3
		con.setTextColor(con.BRANCO);			// Sets the text color to white
		
	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}

	int type;				// At this point the population is valid, so the element needs to be checked

	if(arg1[0]=='S'||arg1[0]=='C') type=0;		// If it is a soldier or a castle	
	else if(arg1[0]=='P'||arg1[0]=='A') type=1;	// If it is a peasant or an academy
	else if(arg1[0]=='K'||arg1[0]=='E') type=2;	// If it is a knight or a stable
	else if(arg1[0]=='B'||arg1[0]=='Q') type=3;	// If it is a riding peasant or a farm	
	else if(arg1[0]=='O') type=4;				// If it is an orc	
	else return 4;
			
	if(arg1[0]=='S'||arg1[0]=='P'||arg1[0]=='K'||arg1[0]=='B'||arg1[0]=='O')	// If it is an unit
	{
		int flagv=0;		// Flag for unit id validation
		int n;				// Auxiliar position variable

		for(unsigned int i=0;i<p[populacao]->unid[type].size();i++)	// Searches for the unit in the soldiers vector
			if(p[populacao]->unid[type][i]->GetN()==elemento)
			{
				flagv=1;	// The unit exists
				n=i;		// Saves the position of the unit in the vector
			}

		if(flagv!=1)		
			return 0;		// The unit does not exist
		else
		{
			con.gotoxy(4,54);
			cout<<"ID: "<<p[populacao]->unid[type][n]->GetN();
			
			if(type==0) cout<<", Tipo: Soldado";
			else if(type==1) cout<<", Tipo: Campones";
			else if(type==2) cout<<", Tipo: Cavaleiro";
			else if(type==3) cout<<", Tipo: Campones a Cavalo";
			else if(type==4) cout<<", Tipo: Orc";
			
			cout<<", Populacao: "<<populacao+1<<" - \""<<p[populacao]->GetNome()
				<<"\""<<", Coordenadas: ("<<(p[populacao]->unid[type][n]->GetX()/3)<<","<<(p[populacao]->unid[type][n]->GetY()/3)<<")";
			con.gotoxy(4,57);
			cout<<"Vida: "<<p[populacao]->unid[type][n]->GetVida()<<", Velocidade: "<<p[populacao]->unid[type][n]->GetVel()
				<<", Ataque: "<<p[populacao]->unid[type][n]->GetAtaque()<<", Defesa: "<<p[populacao]->unid[type][n]->GetDef()
				<<", Carga: "<<p[populacao]->unid[type][n]->GetCarga();

			int lin=p[populacao]->unid[type][n]->GetX();
			int col=p[populacao]->unid[type][n]->GetY();

			if((lin>x&&lin<x+45)&&(col>y&&col<y+81))	// Checks if the unit is within the current view
				return 1;
			else 
				CentraSel(con,x,y,lin,col);	// Sets the view where the unit is placed in the map
		}
	}
	else if(arg1[0]=='C'||arg1[0]=='A'||arg1[0]=='E'||arg1[0]=='Q')		// If it is a building
	{
		int flagv=0;		// Flag for building id validation
		int n;				// Auxiliar position variable

		for(unsigned int i=0;i<p[populacao]->edif[type].size();i++)	// Searches for the building in the castle vector
			if(p[populacao]->edif[type][i]->GetN()==elemento)
			{
				flagv=1;	// The building exists
				n=i;		// Saves the position of the unit in the vector
			}

		if(flagv!=1)		
			return 0;		// The building does not exist
		else
		{
			if(type==0)		// If it is a castle
			{
				con.gotoxy(4,52);
				
				cout<<"ID: "<<p[populacao]->edif[type][n]->GetN();
				cout<<", Tipo: Castelo";
				cout<<", Populacao: "<<populacao+1<<" - \""<<p[populacao]->GetNome()<<"\""
				<<", Coordenadas: ("<<(p[populacao]->edif[type][n]->GetX()/3)<<","<<(p[populacao]->edif[type][n]->GetY()/3)<<")";
				
				con.gotoxy(4,55);
				
				cout<<"Vida: "<<p[populacao]->edif[type][n]->GetVida();

				cout<<", Ouro: "<<p[populacao]->edif[type][n]->GetOuro()
					<<", Pedra: "<<p[populacao]->edif[type][n]->GetPedra()<<", Madeira: "<<p[populacao]->edif[type][n]->GetMadeira();

				con.gotoxy(4,59);

				cout<<"Treinar Campones (5 O, 10 M), Treinar Campones a cavalo (5 O, 5 P, 15 M)";
			
			}
			else
			{
				con.gotoxy(4,54);
				cout<<"ID: "<<p[populacao]->edif[type][n]->GetN();
			
				if(type==1) cout<<", Tipo: Quartel";
				else if(type==2) cout<<", Tipo: Estabulo";
				else if(type==3) cout<<", Tipo: Quinta";
			
				cout<<", Populacao: "<<populacao+1<<" - \""<<p[populacao]->GetNome()<<"\""
					<<", Coordenadas: ("<<(p[populacao]->edif[type][n]->GetX()/3)<<","<<(p[populacao]->edif[type][n]->GetY()/3)<<")";
				con.gotoxy(4,57);
				cout<<"Vida: "<<p[populacao]->edif[type][n]->GetVida();

				if(type==1)
					cout<<", Treinar Soldado (10 O, 10 M), Treinar Orc (10 O, 10 P, 15 M)";
				else if(type==2)
					cout<<", Treinar Cavaleiro (10 O, 5 P, 15 M)";
				else if(type==3)
					cout<<", Capacidade maxima de suporte (total de quintas): "<<p[populacao]->edif[3].size()*4<<" unidades";
			}

			int lin=p[populacao]->edif[type][n]->GetX();
			int col=p[populacao]->edif[type][n]->GetY();

			if((lin>x&&lin<x+45)&&(col>y&&col<y+81))	// Checks if the building is within the current view
				return 1;
			else 
				CentraSel(con,x,y,lin,col);	// Sets the view where the unit is placed in the map
		}
	}
	else
		return 4;	// If the input is invalid

	return 1;
}

int Jogo::Stop(std::string elem,string pop)		// Cancels the unit's duties
{
	char arg1[3],arg2[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao;

	if(elem.length()!=3||pop.length()!=3)	// Checks for invalid arguments
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0
		
	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}
			
	if(arg1[0]=='S'||arg1[0]=='P'||arg1[0]=='K'||arg1[0]=='B'||arg1[0]=='O')	// At this point the population is valid, so the unit needs to be checked
	{
		int flagv=0;		// Flag for unit id validation
		int n;				// Auxiliar position variable
		int m;				// Auxiliar type variable

		for(int j=0;j<5;j++)
			for(unsigned int i=0;i<p[populacao]->unid[j].size();i++)	// Searches for the unit in the units vector
				if(p[populacao]->unid[j][i]->GetN()==elemento&&p[populacao]->unid[j][i]->GetId()==arg1[0])
				{
					flagv=1;	// The unit exists
					n=i;		// Saves the position of the unit in the vector
					m=j;		// Saves the type of the unit in the vector
				}

			if(flagv!=1)		
				return 0;		// The unit does not exist
			else
			{
				p[populacao]->unid[m][n]->SetActual(0);
				p[populacao]->unid[m][n]->tarefas.clear();
			}
	}
	else
		return 4;

	return 1;
}

void Jogo::CentraSel(Consola& con,int& x,int& y,int lin,int col)	// Centers an object in the map when selected
{
	if(lin<=45&&col<=81)	// If the unit is in the first view (coordinates 0,0)
	{
		x=0;
		y=0;

		DesenhaMapa(con,x,y);
	}
	else if((linhas-lin)>45&&colunas-col>81)	// If it is not near the bottom and right limit
	{
		if(lin>45&&col>81)	// It's in the middle, away from the limits
		{
			x=col-40;
			y=lin-22;
					
			DesenhaMapa(con,x,y);
		}
		else if(col<=81&&lin>45)	// It's near the left limit
		{
			if(col<40)
				x=0;
			else
				x=col-40;

			y=lin-22;

			DesenhaMapa(con,x,y);
		}
		else if(col>81&&lin<45)	// It's near the top limit
		{
			if(lin<22)
				y=0;
			else
				y=lin-22;

			x=col-40;

			DesenhaMapa(con,x,y);
		}
	}
	else if(col<=81)	// It's near the bottom and the left limits
	{
		if(col<40)
			x=0;

		y=linhas-45;

		DesenhaMapa(con,x,y);
	}
	else if(col>81)	
	{
		if(colunas-col>81)			// It's near the bottom, away from the left and right limits
		{
			if(linhas-lin<22)
				y=linhas-45;
			else
				y=lin-22;

			x=col-40;
					
			DesenhaMapa(con,x,y);
		}
		else if(linhas-lin<=45)			// It´s near the bottom and the right limit
		{
			if(linhas-lin<22)
				y=linhas-45;
			else
				y=lin-22;

			x=colunas-81;
					
			DesenhaMapa(con,x,y);
		}
		else if(linhas-lin>45)			// It's near the right limit and away from top and bottom
		{
			if(colunas-col<40)
				x=colunas-81;
			else
				x=col-40;

			y=lin-22;
				
			DesenhaMapa(con,x,y);
		}
		else						// It's on the top right
		{
			if(colunas-col<40)
				x=colunas-81;
			else
				x=col-40;
				
			if(lin<22)
				y=0;
			else
				y=lin-22;
				
			DesenhaMapa(con,x,y);
		}
	}
}

int Jogo::Goto(string elem,string pop,int lin,int col)		// Moves the unit
{
	char arg1[3],arg2[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao;

	if(elem.length()!=3||pop.length()!=3)	// Checks for invalid arguments
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0
		
	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}

	int type;		// At this point the population is valid, so the element needs to be checked

	if(arg1[0]=='S') type=0;		// If it is a soldier
	else if(arg1[0]=='P') type=1;	// If it is a peasant
	else if(arg1[0]=='K') type=2;	// If it is a knight
	else if(arg1[0]=='B') type=3;	// If it is a riding peasant
	else if(arg1[0]=='O') type=4;	// If it is an orc
	else return 4;
		
	int flagv=0;		// Flag for unit id validation
	int n;				// Auxiliar position variable

	for(unsigned int i=0;i<p[populacao]->unid[type].size();i++)	// Searches for the unit in the units vector
		if(p[populacao]->unid[type][i]->GetN()==elemento)
		{
			flagv=1;	// The unit exists
			n=i;		// Saves the position of the unit in the vector
		}

	if(flagv!=1)		
		return 0;		// The unit does not exist
	else
	{
		p[populacao]->unid[type][n]->tarefas.clear();
		p[populacao]->unid[type][n]->tarefas.push_back(1);
		p[populacao]->unid[type][n]->SetDestlin(lin);
		p[populacao]->unid[type][n]->SetDestcol(col);
		p[populacao]->unid[type][n]->SetActual(1);
	}

	return 1;
}

int Jogo::Go(string elem,string pop,int lin,int col,int mlin,int mcol)		// Moves the unit
{
	char arg1[3],arg2[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao;

	if(elem.length()!=3||pop.length()!=3)	// Checks for invalid arguments
		return 5;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0
		
	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}

	int type;		// At this point the population is valid, so the element needs to be checked

	if(arg1[0]=='S') type=0;		// If it is a soldier
	else if(arg1[0]=='P') type=1;	// If it is a peasant
	else if(arg1[0]=='K') type=2;	// If it is a knight
	else if(arg1[0]=='B') type=3;	// If it is a riding peasant
	else if(arg1[0]=='O') type=4;	// If it is an orc
	else return 5;

	int flagv=0;		// Flag for unit id validation
	int n;				// Auxiliar position variable

	for(unsigned int i=0;i<p[populacao]->unid[type].size();i++)	// Searches for the unit in the units vector
		if(p[populacao]->unid[type][i]->GetN()==elemento)
		{
			flagv=1;	// The unit exists
			n=i;		// Saves the position of the unit in the vector
		}

	if(flagv!=1)		
		return 0;		// The unit does not exist
	else
	{
		int cl=p[populacao]->unid[type][n]->GetX()+(lin*p[populacao]->unid[type][n]->GetVel());
		int cc=p[populacao]->unid[type][n]->GetY()+(col*p[populacao]->unid[type][n]->GetVel());

		if(cl<0||cl>=mlin||cc<0||cc>=mcol)
			return 4;
		else
		{
			p[populacao]->unid[type][n]->tarefas.clear();
			p[populacao]->unid[type][n]->tarefas.push_back(1);
			p[populacao]->unid[type][n]->SetDestlin(cl);
			p[populacao]->unid[type][n]->SetDestcol(cc);
			p[populacao]->unid[type][n]->SetActual(1);
		}
	}

	return 1;
}

void Jogo::Next()		// Executes the automatic duties of each element in the game
{
	if(p.size()!=0)		// Checks for existing populations		
	{
		for(unsigned int i=0;i<p.size();i++)		// Checks each population
		{
			if(p[i]->unid!=NULL)					// Check if population has units
			{
				for(unsigned int j=0;j<5;j++)		// Checks each array of units in the current population
				{
					if(p[i]->unid[j].size()!=0)		// Checks if the unit type's array is empty
					{
						for(unsigned int k=0;k<p[i]->unid[j].size();k++)
						{
							if(p[i]->unid[j][k]->GetActual()!=0)
							{
								if(p[i]->unid[j][k]->GetActual()==1)
									Mover(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==2&&p[i]->unid[j][k]->tarefas.size()==2&&(p[i]->unid[j][k]->GetId()=='S'||p[i]->unid[j][k]->GetId()=='K'||p[i]->unid[j][k]->GetId()=='O'))
									Atacar(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==2&&p[i]->unid[j][k]->tarefas.size()==2&&(p[i]->unid[j][k]->GetId()=='P'||p[i]->unid[j][k]->GetId()=='B'))
									Recolher(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==3)
									Mover(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==4&&p[i]->unid[j][k]->tarefas.size()==4&&(p[i]->unid[j][k]->GetId()=='P'||p[i]->unid[j][k]->GetId()=='B'))
									Depositar(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==4&&p[i]->unid[j][k]->tarefas.size()==4&&(p[i]->unid[j][k]->GetId()=='S'||p[i]->unid[j][k]->GetId()=='K'||p[i]->unid[j][k]->GetId()=='O'))
									Demolir(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==5)
									Mover(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==6&&p[i]->unid[j][k]->tarefas.size()==6)
									Construir(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==7)
									Mover(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==8&&p[i]->unid[j][k]->tarefas.size()==8)
									Consertar(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==9)
									Mover(p[i]->unid[j][k]);
								else if(p[i]->unid[j][k]->GetActual()==10&&p[i]->unid[j][k]->tarefas.size()==10)
									Deambular(p[i]->unid[j][k]);
								else
								{
									p[i]->unid[j][k]->SetActual(0);
									p[i]->unid[j][k]->tarefas.clear();
								}
							}
						}
					}
				}
			}
		}
	}
}

void Jogo::Deambular(Unidade* s)
{
	if(s->GetTipocarga()=='S')		// Flagged South
	{
		s->SetDestcol(s->GetY()+18);
		s->SetTipocarga('E');
		s->SetActual(9);	
	}
	else if(s->GetTipocarga()=='E')	// Flagged East
	{
		s->SetDestlin(s->GetX()-18);
		s->SetTipocarga('N');
		s->SetActual(9);	
	}
	else if(s->GetTipocarga()=='N')	// Flagged North
	{
		s->SetDestcol(s->GetY()-18);
		s->SetTipocarga('O');
		s->SetActual(9);	
	}
	else if(s->GetTipocarga()=='O')	// Flagged West
	{
		s->SetDestlin(s->GetX()+18);
		s->SetTipocarga('S');
		s->SetActual(9);	
	}
}

void Jogo::Mover(Unidade* s)
{
	int l=s->GetX();	// Saves the x coordinates
	int c=s->GetY();	// Saves the y coordinates

	if(s->GetPop()==0)	// If it is the first population (player)
	{
		if(t.b[l][c].sector.size()==1)	// Checks if the current sector has more than one unit
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					t.b[l+i][c+j].SetP(2);	// Sets the ground flag to 2 (green patch)
	}
	else
	{
		if(t.b[l][c].sector.size()==1)	// Checks if the current sector has more than one unit
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(t.b[l+i][c+j].GetP()==3)			// If it's flagged as unknown
						t.b[l+i][c+j].SetP(1);			// Flags the ground as fog
					else if(t.b[l+i][c+j].GetP()==0)	// If it's flagged as known
						t.b[l+i][c+j].SetP(2);			// Sets the ground flag to 2 (green patch)
	}

	vector<Bloco*>temp;	// Temporary vector

	for(unsigned int v=0;v<t.b[l][c].sector.size();v++)	// Pushes the objects to the temporary vector except the moving one
		if(t.b[l][c].sector[v]!=s)
			temp.push_back(t.b[l][c].sector[v]);

	t.b[l][c].sector.clear();	// Clears the current sector

	for(unsigned int v=0;v<temp.size();v++)		// Updates the current sector
		t.b[l][c].sector.push_back(temp[v]);


	int linha=0,coluna=0;					// Auxiliar variables

	if(s->GetDestlin()>s->GetX())			// If the destination line is higher than the current
		linha=s->GetDestlin()-s->GetX();	// Calculates the difference between them
	else if(s->GetDestlin()<s->GetX())		// If the destination line is lower than the current
		linha=s->GetX()-s->GetDestlin();	// Calculates the difference between them

	if(s->GetDestcol()>s->GetY())			// If the destination column is higher than the current
		coluna=s->GetDestcol()-s->GetY();	// calculates the difference between them
	else if(s->GetDestcol()<s->GetY())		// If the destination column is lower than the current
		coluna=s->GetY()-s->GetDestcol();	// Calculates the difference between them

	if(linha>=coluna&&linha>=s->GetVel())					// If the number of lines is higher than the columns
	{
		if(s->GetDestlin()>s->GetX())			// If the destination line is higher than the current
			s->SetX(s->GetX()+s->GetVel()*3);	// Sets the unit's new coordinates according to its speed
		else if(s->GetDestlin()<s->GetX())		// If the destination line is lower than the current
			s->SetX(s->GetX()-s->GetVel()*3);	// Sets the unit's new coordinates according to its speed
	}
	else if(linha<coluna&&coluna>=s->GetVel())			// If the number of lines is lower than the columns
	{
		if(s->GetDestcol()>s->GetY())			// If the destination column is higher than the current
			s->SetY(s->GetY()+s->GetVel()*3);	// Sets he unit's new coordinates according to its speed
		else if(s->GetDestcol()<s->GetY())		// If the destination column is lower than the current
			s->SetY(s->GetY()-s->GetVel()*3);	// Sets he unit's new coordinates according to its speed
	}

	if((s->GetVel()==2||s->GetVel()==3)&&s->GetDestlin()-s->GetX()==3)			// Adjusts the coordinates accordingly with the unit's speed
		s->SetX(s->GetX()+3);
	else if((s->GetVel()==2||s->GetVel()==3)&&s->GetX()-s->GetDestlin()==3)
		s->SetX(s->GetX()-3);
	else if((s->GetVel()==2||s->GetVel()==3)&&s->GetDestcol()-s->GetY()==3)
		s->SetY(s->GetY()+3);
	else if((s->GetVel()==2||s->GetVel()==3)&&s->GetY()-s->GetDestcol()==3)
		s->SetY(s->GetY()-3);

	if(linha>=0&&linha<s->GetVel()&&coluna>=0&&coluna<s->GetVel())		// When it reaches the destination, sets for the next task
	{
		s->SetX(s->GetDestlin());
		s->SetY(s->GetDestcol());
		s->SetActual(s->GetActual()+1);
	}

	int lin=s->GetX();	// Saves the x coordinates
	int col=s->GetY();	// Saves the y coordinates

	t.b[lin][col].sector.push_back(s);	// Adds the soldier to the new position vector

	if(s->GetPop()==0)	// If it is the first population (player)
	{
		for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the soldier will be placed
			for(int j=-6;j<9;j++)
				if(lin+i>=0&&col+j>=0&&lin+i<t.GetLinhas()&&col+j<t.GetColunas())
				{
					if(i>=0&&i<3&&j>=0&&j<3)
						t.b[lin+i][col+j].SetP(0);
					else if(t.b[lin+i][col+j].GetP()==1)	// If the sector is flagged as fog of war
						t.b[lin+i][col+j].SetP(2);			// Flags as clear sector
					else if(t.b[lin+i][col+j].GetP()==3)	// If the sector is flagged as enemy unit or resource
						t.b[lin+i][col+j].SetP(0);			// Flags as occupied sector
				}
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(t.b[lin+i][col+j].GetP()==2)			// If it's flagged as known field
					t.b[lin+i][col+j].SetP(0);			// Shows itself as known
				else if(t.b[lin+i][col+j].GetP()==1)	// If it's flagged as fog of war
					t.b[lin+i][col+j].SetP(3);			// Remains out of sight
	}
}

void Jogo::Atacar(Unidade* s)	// Attacks a target unit
{
	if(s->GetAlvo()!=NULL)
	{
		Unidade* a=s->GetAlvo();

		if(s->GetX()!=a->GetX()||s->GetY()!=a->GetY())	// If the coordinates of both units do not match
		{
			s->SetDestlin(a->GetX());	// Updates the destination x coordinates of the attacker
			s->SetDestcol(a->GetY());	// Updates the destination y coordinates of the attacker
			s->SetActual(1);			// Updates the duties state of the attacking unit in order to move to the new coordinates before the next duty
		}
		else	// Both the units coordinates match, so the fight can start
		{
			if(s->GetVida()>0&&a->GetVida()>0)
			{
				int at=s->GetAtaque();	// Attacker's attack value
				int def=a->GetDef();	// Target's defense value

				at=(((at*100)-(at*def))/100);

				a->SetVida(a->GetVida()-at);	// Sets the target's health acoording with the attack and defense values

				at=a->GetAtaque();	// Target's attack value
				def=s->GetDef();	// Attacker's defense value
				at=(((at*100)-(at*def))/100);

				s->SetVida(s->GetVida()-at);	// Sets the attacker's health acoording with the attack and defense values

				if(a->GetId()=='P'||a->GetId()=='B')	// If the target is a peasant or a riding peasant, it runs to the castle after being attacked
				{
					if(a->GetActual()!=1&&a->tarefas.size()!=1)
					{
						a->SetDestino(p[a->GetPop()]->edif[0][0]);			// Sets the castle as destination
						a->SetDestlin(p[a->GetPop()]->edif[0][0]->GetX());	// Sets the destination x coordinate
						a->SetDestcol(p[a->GetPop()]->edif[0][0]->GetY());	// Sets the destination y coordinate
						a->tarefas.clear();									// Clears the unit's duties
						a->tarefas.push_back(1);							// Sets the order to move to the castle
						a->SetActual(1);									// Sets the current state
					}
				}
			}

			if(a->GetVida()<=0)	// If the target dies
			{
				int l=a->GetX();		// Saves the x coordinates
				int c=a->GetY();		// Saves the y coordinates
				int pop=a->GetPop();	// Saves the population
				int type;				// Saves the units type

				if(a->GetId()=='S')
					type=0;
				else if(a->GetId()=='P')
					type=1;
				else if(a->GetId()=='K')
					type=2;
				else if(a->GetId()=='B')
					type=3;
				else if(a->GetId()=='O')
					type=4;

				vector<Bloco*>temp;	// Temporary vector

				for(unsigned int v=0;v<t.b[l][c].sector.size();v++)	// Pushes the objects to the temporary vector except the moving one
					if(t.b[l][c].sector[v]!=a)
						temp.push_back(t.b[l][c].sector[v]);

				t.b[l][c].sector.clear();	// Clears the current sector

				for(unsigned int v=0;v<temp.size();v++)		// Updates the current sector
					t.b[l][c].sector.push_back(temp[v]);
			

				if(p[pop]->unid[type].size()==1)
					p[pop]->unid[type].clear();	// Clears the current type vector
				else
				{
					vector<Unidade*>temp2;

					for(unsigned int v=0;v<p[pop]->unid[type].size();v++)
						if(p[pop]->unid[type][v]!=a)
							temp2.push_back(p[pop]->unid[type][v]);

					p[pop]->unid[type].clear();	// Clears the current type vector

					for(unsigned int v=0;v<temp2.size();v++)		// Updates the current type vector
						p[pop]->unid[type].push_back(temp2[v]);
				}

				for(unsigned int j=0;j<p.size();j++)	// Warns all the units targeting this unit that it no longer exists
					for(int k=0;k<5;k++)
						for(unsigned int i=0;i<p[j]->unid[k].size();i++)
							if(p[j]->unid[k][i]->GetAlvo()==a)
							{
								p[j]->unid[k][i]->SetActual(3);
								p[j]->unid[k][i]->SetAlvo(NULL);
							}

				delete a;	// Deletes the object

				if(t.b[l][c].sector.size()==0)	// Checks if the current sector has more than one unit
					for(int i=0;i<3;i++)
						for(int j=0;j<3;j++)
							t.b[l+i][c+j].SetP(2);	// Sets the ground flag to 2 (green patch)
			}

			if(s->GetVida()<=0)	// If the attacker dies
			{
				int l=s->GetX();	// Saves the x coordinates
				int c=s->GetY();	// Saves the y coordinates
				int pop=s->GetPop();	// Saves the population
				int type;	// Saves the units type

				if(s->GetId()=='S')
					type=0;
				else if(s->GetId()=='P')
					type=1;
				else if(s->GetId()=='K')
					type=2;
				else if(s->GetId()=='B')
					type=3;
				else if(s->GetId()=='O')
					type=4;

				vector<Bloco*>temp;	// Temporary vector

				for(unsigned int v=0;v<t.b[l][c].sector.size();v++)	// Pushes the objects to the temporary vector except the moving one
					if(t.b[l][c].sector[v]!=s)
						temp.push_back(t.b[l][c].sector[v]);

				t.b[l][c].sector.clear();	// Clears the current sector

				for(unsigned int v=0;v<temp.size();v++)		// Updates the current sector
					t.b[l][c].sector.push_back(temp[v]);

				if(p[pop]->unid[type].size()==1)
					p[pop]->unid[type].clear();	// Clears the current type vector
				else
				{
					vector<Unidade*>temp2;

					for(unsigned int v=0;v<p[pop]->unid[type].size();v++)
						if(p[pop]->unid[type][v]!=s)
							temp2.push_back(p[pop]->unid[type][v]);

					p[pop]->unid[type].clear();	// Clears the current type vector

					for(unsigned int v=0;v<temp2.size();v++)		// Updates the current type vector
						p[pop]->unid[type].push_back(temp2[v]);
				}

				for(unsigned int j=0;j<p.size();j++)	// Warns all the units targeting this unit that it no longer exists
					for(int k=0;k<5;k++)
						for(unsigned int i=0;i<p[j]->unid[k].size();i++)
							if(p[j]->unid[k][i]->GetAlvo()==s)
							{
								p[j]->unid[k][i]->SetActual(3);
								p[j]->unid[k][i]->SetAlvo(NULL);
							}

				delete s;	// Deletes the object

				if(t.b[l][c].sector.size()==0)	// Checks if the current sector has more than one unit
					for(int i=0;i<3;i++)
						for(int j=0;j<3;j++)
							t.b[l+i][c+j].SetP(2);	// Sets the ground flag to 2 (green patch)
			}
		}
	}
	else	// The target unit does not exists
	{
		s->SetActual(0);
		s->tarefas.clear();
	}
}

void Jogo::Demolir(Unidade* s)	// Attacks a target building
{
	if(s->GetDestino()!=NULL)	// Checks if target building still exists
	{
		Edificio* a=s->GetDestino();

		if(a->GetVida()>0)	// If the HP of the target is above zero
			a->SetVida(a->GetVida()-s->GetAtaque());	// Sets the target's health acoording with the attacker's attack value

		if(a->GetVida()<=0)			// If the target is destroyed
		{
			int l=a->GetX();		// Saves the x coordinates
			int c=a->GetY();		// Saves the y coordinates
			int pop=a->GetPop();	// Saves the population
			int type;				// Saves the units type

			if(a->GetId()=='C')
				type=0;
			else if(a->GetId()=='A')
				type=1;
			else if(a->GetId()=='E')
				type=2;
			else if(a->GetId()=='Q')
				type=3;

			vector<Bloco*>temp;	// Temporary vector

			for(unsigned int v=0;v<t.b[l][c].sector.size();v++)	// Pushes the objects to the temporary vector except the moving one
				if(t.b[l][c].sector[v]!=a)
					temp.push_back(t.b[l][c].sector[v]);

			t.b[l][c].sector.clear();	// Clears the current sector

			for(unsigned int v=0;v<temp.size();v++)		// Updates the current sector
				t.b[l][c].sector.push_back(temp[v]);
			
			if(p[pop]->edif[type].size()==1)
				p[pop]->edif[type].clear();	// Clears the current type vector
			else
			{
				vector<Edificio*>temp2;

				for(unsigned int v=0;v<p[pop]->edif[type].size();v++)
					if(p[pop]->edif[type][v]!=a)
						temp2.push_back(p[pop]->edif[type][v]);

				p[pop]->edif[type].clear();	// Clears the current type vector

				for(unsigned int v=0;v<temp2.size();v++)		// Updates the current type vector
					p[pop]->edif[type].push_back(temp2[v]);
			}

			for(unsigned int j=0;j<p.size();j++)	// Warns all the units targeting this building that it no longer exists
				for(int k=0;k<5;k++)
					for(unsigned int i=0;i<p[j]->unid[k].size();i++)
						if(p[j]->unid[k][i]->GetDestino()==a)
						{
							//p[j]->unid[k][i]->SetActual(3);
							p[j]->unid[k][i]->SetDestino(NULL);
						}

			delete a;	// Deletes the object

			if(t.b[l][c].sector.size()==0)	// Checks if the current sector is empty
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						t.b[l+i][c+j].SetP(2);	// Sets the ground flag to 2 (green patch)
		}	
	}
	else	// The target building does not exists
	{
		s->SetActual(0);
		s->tarefas.clear();
	}
}

void Jogo::Recolher(Unidade* s)	// Harvests the target resource site
{
	if(s->GetRecurso()!=NULL)	// If the resource node exists
	{
		Fonte* a=s->GetRecurso();

		if(s->GetCarga()!=0&&a->GetQuant()!=0)	// If the unit's bag is not full and the site is not depleted
		{
			a->SetQuant(a->GetQuant()-1);		// Sets the target's amount

			s->SetCarga(s->GetCarga()-1);		// Sets the unit's capacity
		}

		if(a->GetQuant()==0)	// If the site depletes
		{
			int l=a->GetX();	// Saves the x coordinates
			int c=a->GetY();	// Saves the y coordinates

			vector<Bloco*>temp;	// Temporary vector

			for(unsigned int v=0;v<t.b[l][c].sector.size();v++)	// Pushes the objects to the temporary vector except the moving one
				if(t.b[l][c].sector[v]!=a)
					temp.push_back(t.b[l][c].sector[v]);

			t.b[l][c].sector.clear();	// Clears the current sector

			for(unsigned int v=0;v<temp.size();v++)		// Updates the current sector
				t.b[l][c].sector.push_back(temp[v]);
			
			vector<Fonte*>temp2;	// Temporary vector

			for(unsigned int v=0;v<f.size();v++)	// Pushes the resources to the temporary vector except the depleted one
				if(f[v]!=a)
					temp2.push_back(f[v]);

			f.clear();	// Clears the resources vector

			for(unsigned int v=0;v<temp2.size();v++)	// Updates the resources vector
				f.push_back(temp2[v]);

			for(unsigned int j=0;j<p.size();j++)	// Warns all the units targeting this unit that it no longer exists
				for(int k=0;k<5;k++)
					for(unsigned int i=0;i<p[j]->unid[k].size();i++)
						if(p[j]->unid[k][i]->GetRecurso()==a)
							p[j]->unid[k][i]->SetRecurso(NULL);

			delete a;	// Deletes the object

			if(t.b[l][c].sector.size()==0)	// Checks if the current sector has more than one unit
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						t.b[l+i][c+j].SetP(2);	// Sets the ground flag to 2 (green patch)
		}

		if(s->GetCarga()==0)	// If the bag is full the cargo needs to be deposited
			if(p[s->GetPop()]->edif[0][0]!=NULL)	// If the population's Castle still exists
			{
				s->SetDestino(p[s->GetPop()]->edif[0][0]);			// Sets the Castle as the destination
				s->SetDestlin(p[s->GetPop()]->edif[0][0]->GetX());	// Sets the destination x coordinate
				s->SetDestcol(p[s->GetPop()]->edif[0][0]->GetY());	// Sets the destination y coordinate
				s->SetActual(3);
				s->tarefas.push_back(3);
				s->tarefas.push_back(4);
			}
	}
	else	// If the resource node does no longer exists
	{
		int flagr=0;	// Same type resources flag

		for(int i=-12;i<15;i++)		// Looks for a node in field of vision of the castle
			for(int j=-12;j<15;j++)
				if(p[s->GetPop()]->edif[0][0]->GetX()+i>=0&&p[s->GetPop()]->edif[0][0]->GetY()+j>=0
					&&p[s->GetPop()]->edif[0][0]->GetX()+i<t.GetLinhas()&&p[s->GetPop()]->edif[0][0]->GetY()+j<t.GetColunas())	// Map limit validation
					if(f.size()!=0)										// Checks if there are more resources available
						for(unsigned int k=0;k<f.size();k++)			// Goes through the resources vector
							if(f[k]->GetX()==p[s->GetPop()]->edif[0][0]->GetX()+i&&f[k]->GetY()==p[s->GetPop()]->edif[0][0]->GetY()+j)		// Checks if there's a resource in the current sector
								if(f[k]->GetId()==s->GetTipocarga())	// Checks if the resource is the same as the desired
								{
									s->SetRecurso(f[k]);
									flagr=1;
								}
			
		if(flagr==1)	// If there's more of the same resource
		{
			s->SetDestlin(s->GetRecurso()->GetX());		// Sets destination x coordinate
			s->SetDestcol(s->GetRecurso()->GetY());		// Sets destination y coordinate

			s->tarefas.clear();			// Clears the duties
			s->tarefas.push_back(1);
			s->tarefas.push_back(2);
			s->SetActual(1);			// Sets the new state
		}
		else if(p[s->GetPop()]->edif[0][0]!=NULL) 	// Return to castle, if it exists
		{
			s->SetDestlin(p[s->GetPop()]->edif[0][0]->GetX());		// Sets destination x coordinate
			s->SetDestcol(p[s->GetPop()]->edif[0][0]->GetY());		// Sets destination y coordinate

			s->tarefas.clear();			// Clears the duties
			s->tarefas.push_back(1);
			s->tarefas.push_back(2);
			s->tarefas.push_back(3);
			s->tarefas.push_back(4);
			s->SetActual(3);
		}
		else	// Stops and clears the duties list
		{
			s->tarefas.clear();
			s->SetActual(0);
		}
	}
}

void Jogo::Depositar(Unidade* s)
{
	if(s->GetDestino()!=NULL)
	{
		Edificio* a=s->GetDestino();

		if(s->GetTipocarga()=='M'&&s->GetId()=='P')			// Uploads all the cargo at once, accordingly with the harvester type and the amount
			a->SetOuro(a->GetOuro()+(3-s->GetCarga()));
		else if(s->GetTipocarga()=='R'&&s->GetId()=='P')
			a->SetPedra(a->GetPedra()+(3-s->GetCarga()));
		else if(s->GetTipocarga()=='F'&&s->GetId()=='P')
			a->SetMadeira(a->GetMadeira()+(3-s->GetCarga()));
		else if(s->GetTipocarga()=='M'&&s->GetId()=='B')
			a->SetOuro(a->GetOuro()+(5-s->GetCarga()));
		else if(s->GetTipocarga()=='R'&&s->GetId()=='B')
			a->SetPedra(a->GetPedra()+(5-s->GetCarga()));
		else if(s->GetTipocarga()=='F'&&s->GetId()=='B')
			a->SetMadeira(a->GetMadeira()+(5-s->GetCarga()));

		if(s->GetId()=='P')		// Empties the bag of the harvester
			s->SetCarga(3);
		else if(s->GetId()=='B')
			s->SetCarga(5);

		if(s->GetRecurso()!=NULL)	// If the resource node still exists
		{
			s->SetDestlin(s->GetRecurso()->GetX());		// Sets destination x coordinate
			s->SetDestcol(s->GetRecurso()->GetY());		// Sets destination y coordinate

			s->tarefas.clear();			// Clears the duties
			s->tarefas.push_back(1);
			s->tarefas.push_back(2);
			s->SetActual(1);			// Sets the new state
		}
		else
		{
			int flagr=0;	// Same type resources flag

			for(int i=-12;i<15;i++)		// Looks for a node in field of vision of the castle
				for(int j=-12;j<15;j++)
					if(p[s->GetPop()]->edif[0][0]->GetX()+i>=0&&p[s->GetPop()]->edif[0][0]->GetY()+j>=0
						&&p[s->GetPop()]->edif[0][0]->GetX()+i<t.GetLinhas()&&p[s->GetPop()]->edif[0][0]->GetY()+j<t.GetColunas())	// Map limit validation
						if(f.size()!=0)										// Checks if there are more resources available
							for(unsigned int k=0;k<f.size();k++)			// Goes through the resources vector
								if(f[k]->GetX()==p[s->GetPop()]->edif[0][0]->GetX()+i&&f[k]->GetY()==p[s->GetPop()]->edif[0][0]->GetY()+j)		// Checks if there's a resource in the current sector
									if(f[k]->GetId()==s->GetTipocarga())	// Checks if the resource is the same as the desired
									{
										s->SetRecurso(f[k]);
										flagr=1;
									}

			if(flagr==1)	// If there's more of the same resource
			{
				s->SetDestlin(s->GetRecurso()->GetX());		// Sets destination x coordinate
				s->SetDestcol(s->GetRecurso()->GetY());		// Sets destination y coordinate

				s->tarefas.clear();			// Clears the duties
				s->tarefas.push_back(1);
				s->tarefas.push_back(2);
				s->SetActual(1);			// Sets the new state
			}
			else	// Stops and clears the duties list
			{
				s->tarefas.clear();
				s->SetActual(0);
			}
		}
	}
	else	// Stops and clears the duties list if the target building does no longer exists
	{
		s->tarefas.clear();
		s->SetActual(0);
	}
}

void Jogo::Construir(Unidade* s)
{
	int lin=s->GetDestlin(),i;
	int col=s->GetDestcol();
	char type=s->GetTipocarga();

	if(lin==3&&s->GetCarga()==1)	// If the building is meant to be placed in the top line
	{
		if(t.b[lin-3][col].sector.size()==0)	// If the sector is still available for construction
		{
			if(type=='C')
				i=p[s->GetPop()]->AddEdificio("cas",lin-3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());
			else if(type=='A')
				i=p[s->GetPop()]->AddEdificio("quar",lin-3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());
			else if(type=='E')
				i=p[s->GetPop()]->AddEdificio("est",lin-3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());
			else if(type=='Q') 
				i=p[s->GetPop()]->AddEdificio("quin",lin-3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());

			if(i==1)	// Withdraws from the castle the resources needed for the building construction
			{
				if(type=='A'||type=='E')
				{
					p[s->GetPop()]->edif[0][0]->SetOuro(p[s->GetPop()]->edif[0][0]->GetOuro()-20);
					p[s->GetPop()]->edif[0][0]->SetPedra(p[s->GetPop()]->edif[0][0]->GetPedra()-20);
					p[s->GetPop()]->edif[0][0]->SetMadeira(p[s->GetPop()]->edif[0][0]->GetMadeira()-20);
				}
				else if(type=='Q')
				{
					p[s->GetPop()]->edif[0][0]->SetOuro(p[s->GetPop()]->edif[0][0]->GetOuro()-15);
					p[s->GetPop()]->edif[0][0]->SetPedra(p[s->GetPop()]->edif[0][0]->GetPedra()-15);
					p[s->GetPop()]->edif[0][0]->SetMadeira(p[s->GetPop()]->edif[0][0]->GetMadeira()-15);
				}
			}
		}
	}
	else	// If the building is not meant to be placed in the top line
	{
		if(t.b[lin+3][col].sector.size()==0)	// If the sector is still available for construction
		{
			if(type=='C')
				i=p[s->GetPop()]->AddEdificio("cas",lin+3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());
			else if(type=='A')
				i=p[s->GetPop()]->AddEdificio("quar",lin+3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());
			else if(type=='E')
				i=p[s->GetPop()]->AddEdificio("est",lin+3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());
			else if(type=='Q') 
				i=p[s->GetPop()]->AddEdificio("quin",lin+3,col,t.b,s->GetPop(),t.GetLinhas(),t.GetColunas());
		

			if(i==1)	// Withdraws from the castle the resources needed for the building construction
			{
				if(type=='A'||type=='E')
				{
					p[s->GetPop()]->edif[0][0]->SetOuro(p[s->GetPop()]->edif[0][0]->GetOuro()-20);
					p[s->GetPop()]->edif[0][0]->SetPedra(p[s->GetPop()]->edif[0][0]->GetPedra()-20);
					p[s->GetPop()]->edif[0][0]->SetMadeira(p[s->GetPop()]->edif[0][0]->GetMadeira()-20);
				}
				else if(type=='Q')
				{
					p[s->GetPop()]->edif[0][0]->SetOuro(p[s->GetPop()]->edif[0][0]->GetOuro()-15);
					p[s->GetPop()]->edif[0][0]->SetPedra(p[s->GetPop()]->edif[0][0]->GetPedra()-15);
					p[s->GetPop()]->edif[0][0]->SetMadeira(p[s->GetPop()]->edif[0][0]->GetMadeira()-15);
				}
			}
		}
	}

	s->tarefas.clear();	// Clears the duties
	s->SetActual(0);	// Resets the current state
	s->SetCarga(3);		// Resets the peasant's cargo variable
}

void Jogo::Consertar(Unidade* s)
{
	if(s->GetDestino()!=NULL)
	{
		Edificio* a=s->GetDestino();

		int dif=99-a->GetVida();	// Calculates the amount of HP to restore

		a->SetVida(99);				// Sets the building to full health
		
		p[a->GetPop()]->edif[0][0]->SetOuro(p[a->GetPop()]->edif[0][0]->GetOuro()-dif);	// Withdraws from the castle the gold needed for repair
	}

	s->tarefas.clear();	// Clears the duties list
	s->SetActual(0);
}

int Jogo::Ataca(string elem,string pop,string elemalvo,string popalvo)	// Sets the attack order to an unit
{
	char arg1[3],arg2[3],arg3[3],arg4[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao,alvo,inimigo;

	if(elem.length()!=3||pop.length()!=3||elemalvo.length()!=3||popalvo.length()!=3)	// Checks for invalid arguments
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
		arg3[i]=elemalvo[i];
		arg4[i]=popalvo[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0

	id1=arg3[1]-'0';		// Turns the char number to integer
	id2=arg3[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    alvo=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg4[1]-'0';		// Turns the char number to integer
	id2=arg4[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    inimigo=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0
		
	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist

		flagv=0;

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==inimigo)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}

	int atac;			// At this point the populations are valid, so the element needs to be checked
	int targ;

	if(arg1[0]=='S') atac=0;		// If it is a soldier
	else if(arg1[0]=='K') atac=2;	// If it is a knight
	else if(arg1[0]=='O') atac=4;	// If it is an orc
	else return 5;
		
	if(arg3[0]=='S'||arg3[0]=='C') targ=0;		// If it is a soldier or a castle
	else if(arg3[0]=='P'||arg3[0]=='A') targ=1;	// If it is a peasant or an academy
	else if(arg3[0]=='K'||arg3[0]=='E') targ=2;	// If it is a knight or a stable
	else if(arg3[0]=='B'||arg3[0]=='Q') targ=3;	// If it is a riding peasant or a farm
	else if(arg3[0]=='O') targ=4;				// If it is an orc
	else return 0;

	int e;	// Auxiliar element position variable
	int a;	// Auxiliar target position variable
			
	int flagv=0;		// Flag for attacker id validation

	for(unsigned int i=0;i<p[populacao]->unid[atac].size();i++)	// Searches for the attacker in the units vector
		if(p[populacao]->unid[atac][i]->GetN()==elemento)
		{
			flagv=1;	// The unit exists
			e=i;		// Saves the position of the unit in the vector
		}

	if(flagv!=1)		
		return 0;		// The unit does not exist

	flagv=0;			// Flag for target id validation

	if(arg3[0]=='S'||arg3[0]=='P'||arg3[0]=='K'||arg3[0]=='B'||arg3[0]=='O')	// If the target is an unit
	{
		for(unsigned int i=0;i<p[inimigo]->unid[targ].size();i++)	// Searches for the target in the units vector
			if(p[inimigo]->unid[targ][i]->GetN()==alvo)
			{
				flagv=1;	// The unit exists
				a=i;		// Saves the position of the unit in the vector
			}

		if(flagv!=1)		
			return 0;		// The unit does not exist

		int alvolin=p[inimigo]->unid[targ][a]->GetX();
		int alvocol=p[inimigo]->unid[targ][a]->GetY();
	
		p[populacao]->unid[atac][e]->tarefas.clear();			// Sets the attacking duties for the unit
		p[populacao]->unid[atac][e]->tarefas.push_back(1);
		p[populacao]->unid[atac][e]->tarefas.push_back(2);

		p[populacao]->unid[atac][e]->SetAlvo(p[inimigo]->unid[targ][a]);
		p[populacao]->unid[atac][e]->SetDestlin(alvolin);
		p[populacao]->unid[atac][e]->SetDestcol(alvocol);
		p[populacao]->unid[atac][e]->SetActual(1);
	}
	else if(arg3[0]=='C'||arg3[0]=='A'||arg3[0]=='E'||arg3[0]=='Q')	// If the target is a building
	{
		for(unsigned int i=0;i<p[inimigo]->edif[targ].size();i++)	// Searches for the target in the buildings vector
			if(p[inimigo]->edif[targ][i]->GetN()==alvo)
			{
				flagv=1;	// The building exists
				a=i;		// Saves the position of the building in the vector
			}

		if(flagv!=1)		
			return 0;		// The building does not exist

		int alvolin=p[inimigo]->edif[targ][a]->GetX();
		int alvocol=p[inimigo]->edif[targ][a]->GetY();
	
		p[populacao]->unid[atac][e]->tarefas.clear();			// Sets the attacking duties for the unit
		p[populacao]->unid[atac][e]->tarefas.push_back(1);
		p[populacao]->unid[atac][e]->tarefas.push_back(2);
		p[populacao]->unid[atac][e]->tarefas.push_back(3);
		p[populacao]->unid[atac][e]->tarefas.push_back(4);

		p[populacao]->unid[atac][e]->SetDestino(p[inimigo]->edif[targ][a]);
		p[populacao]->unid[atac][e]->SetDestlin(alvolin);
		p[populacao]->unid[atac][e]->SetDestcol(alvocol);
		p[populacao]->unid[atac][e]->SetActual(3);
	}
	
	return 1;
}

int Jogo::Recolhe(string elem,string pop,string elemalvo)	// Sets the harvest order to an unit
{
	char arg1[3],arg2[3],arg3[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao,alvo;

	if(elem.length()!=3||pop.length()!=3||elemalvo.length()!=3)	// Checks for invalid arguments
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
		arg3[i]=elemalvo[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0

	id1=arg3[1]-'0';		// Turns the char number to integer
	id2=arg3[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    alvo=(id1*pow+id2);	// Shifts the other variable and multiply the potency
		
	int e;	// Auxiliar element position variable
	int a;	// Auxiliar target position variable

	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist

		flagv=0;

		for(unsigned int i=0;i<f.size();i++)	// Checks if the resource site exists
			if(f[i]->GetN()==alvo&&f[i]->GetId()==arg3[0])
			{
				flagv=1;	// The site exists
				a=i;		// Saves the position of the resource in the vector
			}
			
		if(flagv!=1)		
			return 2;		// The site does not exist
	}

	int type;		// At this point the populations are valid, so the element needs to be checked

	if(arg1[0]=='P') type=1;		// If it is a peasant	
	else if(arg1[0]=='B') type=3;	// If it is a riding peasant	
	else return 0;
			
	int flagv=0;		// Flag for unit id validation

	for(unsigned int i=0;i<p[populacao]->unid[type].size();i++)	// Searches for the unit in the units vector
		if(p[populacao]->unid[type][i]->GetN()==elemento)
		{
			flagv=1;	// The unit exists
			e=i;		// Saves the position of the unit in the vector
		}

	if(flagv!=1)		
		return 0;		// The unit does not exist
	
	int elemlin=p[populacao]->unid[type][e]->GetX();
	int elemcol=p[populacao]->unid[type][e]->GetY();

	int alvolin=f[a]->GetX();
	int alvocol=f[a]->GetY();
	
	p[populacao]->unid[type][e]->tarefas.clear();			// Initiates the duties for the unit
	p[populacao]->unid[type][e]->tarefas.push_back(1);
	p[populacao]->unid[type][e]->tarefas.push_back(2);

	p[populacao]->unid[type][e]->SetRecurso(f[a]);
	p[populacao]->unid[type][e]->SetDestlin(alvolin);
	p[populacao]->unid[type][e]->SetDestcol(alvocol);
	p[populacao]->unid[type][e]->SetActual(1);
	p[populacao]->unid[type][e]->SetTipocarga(f[a]->GetId());
	
	return 1;
}

int Jogo::AddRecurso(string r,int x,int y)	// Adds a resource site to the territory
{
	static int rec,min,ped,flo;	// Static resources counter

	if(t.b[x][y].sector.size()!=0)	// If the sector is already occupied, avoids the placement of a resource
		return 2;

	if(f.size()==0)	// If the vector is empty, initializes the counters
		rec=min=ped=flo=0;
	
	if(r=="min")	// If it is a mine
	{
		rec++;	// Increments the resources counter
		min++;	// Increments the mine counter

		f.push_back(new Mina(x,y,min));		// Adds one mine to the vector

		t.b[x][y].sector.push_back(f[rec-1]);	// Adds the mine to the position vector

		for(int i=0;i<3;i++)	// Deactivates the "fog of war" flag in the coordinates where the mine will be placed
			for(int j=0;j<3;j++)
				t.b[x+i][y+j].SetP(3);
	}
	else if(r=="ped")	// If it is a quarry
	{
		rec++;	// Increments the resources counter
		ped++;	// Increments the quarry counter

		f.push_back(new Pedreira(x,y,ped));	// Adds one quarry to the vector

		t.b[x][y].sector.push_back(f[rec-1]);	// Adds the quarry to the position vector

		for(int i=0;i<3;i++)	// Deactivates the "fog of war" flag in the coordinates where the quarry will be placed
			for(int j=0;j<3;j++)
				t.b[x+i][y+j].SetP(3);
	}
	else if(r=="flo")	// If it is a forest
	{
		rec++;	// Increments the resources counter
		flo++;	// Increments the forest counter

		f.push_back(new Floresta(x,y,flo));	// Adds one forest to the vector

		t.b[x][y].sector.push_back(f[rec-1]);	// Adds the forest to the position vector

		for(int i=0;i<3;i++)	// Deactivates the "fog of war" flag in the coordinates where the forest will be placed
			for(int j=0;j<3;j++)
				t.b[x+i][y+j].SetP(3);
	}
	else
		return 0;

	return 1;	// Success
}

int Jogo::Constroi(string elem,string pop,string e,int l,int c)		// Sets the construct order to an unit
{
	char arg1[3],arg2[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao;

	if(elem.length()!=3||pop.length()!=3)	// Checks for invalid arguments
		return 5;

	if(t.b[l][c].sector.size()!=0)	// The sector is occupied, so it's not allowed to place a new building in it
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0
		
	if(p.size()==0)			// Checks if a population has already been created
		return 2;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}	

	if(e=="cas")	// Procedure to check the maximum number allowed for the building type and the resources needed to build it
	{
		if(p[populacao]->edif[0].size()!=0)	// The castle does not cost resources to build
			return 3;
	}
	else if(e=="quar")
	{
		if(p[populacao]->edif[1].size()!=0)	// If there's already one building of that type
			return 3;

		if(p[populacao]->edif[0].size()==0)	// If the population has no castle
			return 6;
		
		if(p[populacao]->edif[0][0]->GetOuro()<20&&p[populacao]->edif[0][0]->GetPedra()<20&&p[populacao]->edif[0][0]->GetMadeira()<20)
			return 6;
	}
	else if(e=="est")
	{
		if(p[populacao]->edif[2].size()!=0)
			return 3;

		if(p[populacao]->edif[0].size()==0)	// If the population has no castle
			return 6;
		
		if(p[populacao]->edif[0][0]->GetOuro()<20&&p[populacao]->edif[0][0]->GetPedra()<20&&p[populacao]->edif[0][0]->GetMadeira()<20)
			return 6;
	}
	else if(e=="quin")
	{
		if(p[populacao]->edif[0].size()==0)	// If the population has no castle
			return 6;
		
		if(p[populacao]->edif[0][0]->GetOuro()<15&&p[populacao]->edif[0][0]->GetPedra()<15&&p[populacao]->edif[0][0]->GetMadeira()<15)
			return 6;
	}

	if(arg1[0]=='P')	// If it is a peasant
	{
		int flagv=0;		// Flag for unit id validation
		int n;				// Auxiliar position variable

		for(unsigned int i=0;i<p[populacao]->unid[1].size();i++)	// Searches for the unit in the units vector
			if(p[populacao]->unid[1][i]->GetN()==elemento)
			{
				flagv=1;	// The unit exists
				n=i;		// Saves the position of the unit in the vector
			}

		if(flagv!=1)		
			return 2;	// The unit does not exist
		else
		{
			if(l==0)	// If the castle is going to be placed in the top line, the peasant is placed in the sector below
			{
				p[populacao]->unid[1][n]->SetDestlin(l+3);		// Sets the x coordinate
				p[populacao]->unid[1][n]->SetCarga(1);			// Uses the unused variable to signal construction placement
			}
			else
			{
				p[populacao]->unid[1][n]->SetDestlin(l-3);		// Sets the x coordinate
				p[populacao]->unid[1][n]->SetCarga(0);			// Uses the unused variable to signal construction placement
			}

			p[populacao]->unid[1][n]->SetDestcol(c);		// Sets the y coordinate
			p[populacao]->unid[1][n]->tarefas.clear();		// Sets the duties order for the construction to begin
			p[populacao]->unid[1][n]->tarefas.push_back(1);
			p[populacao]->unid[1][n]->tarefas.push_back(2);
			p[populacao]->unid[1][n]->tarefas.push_back(3);
			p[populacao]->unid[1][n]->tarefas.push_back(4);
			p[populacao]->unid[1][n]->tarefas.push_back(5);
			p[populacao]->unid[1][n]->tarefas.push_back(6);
			p[populacao]->unid[1][n]->SetActual(5);

			if(e=="cas") p[populacao]->unid[1][n]->SetTipocarga('C');	// Using the cargo variable to save the building type
			if(e=="quar") p[populacao]->unid[1][n]->SetTipocarga('A');
			if(e=="est") p[populacao]->unid[1][n]->SetTipocarga('E');
			if(e=="quin") p[populacao]->unid[1][n]->SetTipocarga('Q');
		}
	}
	else
		return 2;

	return 1;
}

int Jogo::Conserta(string elem,string pop,string elemalvo,string popalvo)	// Sets the repair order to an unit
{
	char arg1[3],arg2[3],arg3[3],arg4[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao,alvo,palvo;

	if(elem.length()!=3||pop.length()!=3||elemalvo.length()!=3||popalvo.length()!=3)	// Checks for invalid arguments
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
		arg3[i]=elemalvo[i];
		arg4[i]=popalvo[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0

	id1=arg3[1]-'0';		// Turns the char number to integer
	id2=arg3[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    alvo=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg4[1]-'0';		// Turns the char number to integer
	id2=arg4[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    palvo=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0
		
	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist

		flagv=0;

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==palvo)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}
			
	int targ;			// At this point the populations are valid, so the element needs to be checked

	if(arg1[0]!='P')	// If it is not a peasant
		return 0;

	if(populacao!=palvo)	// If the populations are diferent (avoids repairing enemies buildings)
		return 0;
		
	if(arg3[0]=='C') targ=0; 		// If it is a castle
	else if(arg3[0]=='A') targ=1;	// If it is an academy
	else if(arg3[0]=='E') targ=2;	// If it is a stable
	else if(arg3[0]=='Q') targ=3;	// If it is a farm
	else return 0;

	int e;	// Auxiliar element position variable
	int a;	// Auxiliar target position variable
			
	int flagv=0;		// Flag for peasant id validation

	for(unsigned int i=0;i<p[populacao]->unid[1].size();i++)	// Searches for the peasant in the peasants vector
		if(p[populacao]->unid[1][i]->GetN()==elemento)
		{
			flagv=1;	// The unit exists
			e=i;		// Saves the position of the unit in the vector
		}

	if(flagv!=1)		
		return 0;		// The unit does not exist

	flagv=0;			// Flag for target id validation

	for(unsigned int i=0;i<p[palvo]->edif[targ].size();i++)	// Searches for the target in the buildings vector
		if(p[palvo]->edif[targ][i]->GetN()==alvo)
		{
			flagv=1;	// The building exists
			a=i;		// Saves the position of the building in the vector
		}

	if(flagv!=1)		
		return 0;		// The building does not exist

	if(p[palvo]->edif[targ][a]->GetVida()<99)			// Checks if the building needs repairing
	{
		int dif=99-p[palvo]->edif[targ][a]->GetVida();

		if(dif>p[palvo]->edif[0][0]->GetOuro())			// Checks if there are enough resources for the repair
			return 6;
		else
		{
			int alvolin=p[palvo]->edif[targ][a]->GetX();
			int alvocol=p[palvo]->edif[targ][a]->GetY();
	
			p[populacao]->unid[1][e]->tarefas.clear();		// Sets the repairing duties for the unit
			p[populacao]->unid[1][e]->tarefas.push_back(1);
			p[populacao]->unid[1][e]->tarefas.push_back(2);
			p[populacao]->unid[1][e]->tarefas.push_back(3);
			p[populacao]->unid[1][e]->tarefas.push_back(4);
			p[populacao]->unid[1][e]->tarefas.push_back(5);
			p[populacao]->unid[1][e]->tarefas.push_back(6);
			p[populacao]->unid[1][e]->tarefas.push_back(7);
			p[populacao]->unid[1][e]->tarefas.push_back(8);

			p[populacao]->unid[1][e]->SetDestino(p[palvo]->edif[targ][a]);
			p[populacao]->unid[1][e]->SetDestlin(alvolin);
			p[populacao]->unid[1][e]->SetDestcol(alvocol);
			p[populacao]->unid[1][e]->SetActual(7);
		}
	}
	else
		return 5;
	
	return 1;
}

int Jogo::Treina(int populacao,string e)	// Sets the training order to a building
{
	if(e=="sold")	// Procedure to check the maximum number allowed for the unit type and the resources needed to build it
	{
		if(p[populacao]->edif[0].size()==0)			// If the population has no castle
			return 7;
		else if(p[populacao]->edif[1].size()==0)	// If the population has no academy
			return 8;
		else if(p[populacao]->edif[0][0]->GetOuro()<10||p[populacao]->edif[0][0]->GetMadeira()<10)
			return 6;
	}
	else if(e=="camp")
	{
		if(p[populacao]->edif[0].size()==0)			// If the population has no castle
			return 7;
		else if(p[populacao]->edif[0][0]->GetOuro()<5||p[populacao]->edif[0][0]->GetMadeira()<10)
			return 6;
	}
	else if(e=="cav")
	{
		if(p[populacao]->unid[3].size()!=0)			// If there is already one unit of that type
			return 3;
		else if(p[populacao]->edif[0].size()==0)	// If the population has no castle
			return 7;
		else if(p[populacao]->edif[2].size()==0)	// If the population has no stables
			return 9;
		else if(p[populacao]->edif[0][0]->GetOuro()<10||p[populacao]->edif[0][0]->GetPedra()<5||p[populacao]->edif[0][0]->GetMadeira()<15)
			return 6;
	}
	else if(e=="cv")
	{
		if(p[populacao]->edif[0].size()==0)			// If the population has no castle
			return 7;
		else if(p[populacao]->edif[0][0]->GetOuro()<5||p[populacao]->edif[0][0]->GetPedra()<5||p[populacao]->edif[0][0]->GetMadeira()<15)
			return 6;
	}
	else if(e=="orc")
	{
		if(p[populacao]->unid[4].size()!=0)			// If there is already one unit of that type
			return 3;
		else if(p[populacao]->edif[0].size()==0)	// If the population has no castle
			return 7;
		else if(p[populacao]->edif[1].size()==0)	// If the population has no academy
			return 8;
		else if(p[populacao]->edif[0][0]->GetOuro()<10||p[populacao]->edif[0][0]->GetPedra()<10||p[populacao]->edif[0][0]->GetMadeira()<15)
			return 6;
	}

	int nunids=0;			
	int nsuporte=p[populacao]->edif[3].size()*4;	// Gets the maximum support offered by the farms in order to feed the units

	for(unsigned int i=0;i<5;i++)		
		for(unsigned int j=0;j<p[populacao]->unid[i].size();j++)	// Counts the number of units of each type
			nunids++;

	if(nunids>=nsuporte)	// Checks if the number of units surpasses the amount supported by the farms
		return 1;
	else
	{
		int i;		// Spawns an unit at the coordinates of the training building

		if(e=="sold")
			i=p[populacao]->AddUnidade(e,p[populacao]->edif[1][0]->GetX(),p[populacao]->edif[1][0]->GetY(),t.b,populacao,t.GetLinhas(),t.GetColunas());
		else if(e=="camp")
			i=p[populacao]->AddUnidade(e,p[populacao]->edif[0][0]->GetX(),p[populacao]->edif[0][0]->GetY(),t.b,populacao,t.GetLinhas(),t.GetColunas());
		else if(e=="cav")
			i=p[populacao]->AddUnidade(e,p[populacao]->edif[2][0]->GetX(),p[populacao]->edif[2][0]->GetY(),t.b,populacao,t.GetLinhas(),t.GetColunas());
		else if(e=="cv") 
			i=p[populacao]->AddUnidade(e,p[populacao]->edif[0][0]->GetX(),p[populacao]->edif[0][0]->GetY(),t.b,populacao,t.GetLinhas(),t.GetColunas());
		else if(e=="orc") 
			i=p[populacao]->AddUnidade(e,p[populacao]->edif[1][0]->GetX(),p[populacao]->edif[1][0]->GetY(),t.b,populacao,t.GetLinhas(),t.GetColunas());

		if(i==1)	// Withdraws from the castle the resources needed for the unit training
		{
			if(e=="sold")
			{
				p[populacao]->edif[0][0]->SetOuro(p[populacao]->edif[0][0]->GetOuro()-10);
				p[populacao]->edif[0][0]->SetMadeira(p[populacao]->edif[0][0]->GetMadeira()-10);
			}
			else if(e=="camp")
			{
				p[populacao]->edif[0][0]->SetOuro(p[populacao]->edif[0][0]->GetOuro()-5);
				p[populacao]->edif[0][0]->SetMadeira(p[populacao]->edif[0][0]->GetMadeira()-10);
			}
			else if(e=="cav")
			{
				p[populacao]->edif[0][0]->SetOuro(p[populacao]->edif[0][0]->GetOuro()-10);
				p[populacao]->edif[0][0]->SetPedra(p[populacao]->edif[0][0]->GetPedra()-5);
				p[populacao]->edif[0][0]->SetMadeira(p[populacao]->edif[0][0]->GetMadeira()-15);
			}
			else if(e=="cv")
			{
				p[populacao]->edif[0][0]->SetOuro(p[populacao]->edif[0][0]->GetOuro()-5);
				p[populacao]->edif[0][0]->SetPedra(p[populacao]->edif[0][0]->GetPedra()-5);
				p[populacao]->edif[0][0]->SetMadeira(p[populacao]->edif[0][0]->GetMadeira()-15);
			}
			else if(e=="orc")
			{
				p[populacao]->edif[0][0]->SetOuro(p[populacao]->edif[0][0]->GetOuro()-10);
				p[populacao]->edif[0][0]->SetPedra(p[populacao]->edif[0][0]->GetPedra()-10);
				p[populacao]->edif[0][0]->SetMadeira(p[populacao]->edif[0][0]->GetMadeira()-15);
			}
		}
	}

	return 0;
}

int Jogo::Deambula(string elem,string pop,int lin,int col)		// Sets the patrol order to an unit
{
	char arg1[3],arg2[3];
	unsigned int id1,id2;
	unsigned int elemento,populacao;

	if(elem.length()!=3||pop.length()!=3)	// Checks for invalid arguments
		return 4;

	for(int i=0;i<3;i++)	// Gets each letter from the arguments into two supporting arrays
	{
		arg1[i]=elem[i];
		arg2[i]=pop[i];
	}

	id1=arg1[1]-'0';		// Turns the char number to integer
	id2=arg1[2]-'0';

	unsigned int pow=10;	// Declares a supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    elemento=(id1*pow+id2);	// Shifts the other variable and multiply the potency

	id1=arg2[1]-'0';		// Turns the char number to integer
	id2=arg2[2]-'0';

	pow=10;					// Redefines the supporting variable for the potency

    while(id2>=pow)			// Gets the number of digits of the variable that should come second
        pow*=10;

    populacao=(id1*pow+id2)-1;	// Shifts the other variable and multiply it the potency and reduces one because the first index is always 0
		
	if(p.size()==0)			// Checks if a population has already been created
		return 3;
	else
	{
		int flagv=0;		// Flag for population name validation

		for(unsigned int i=0;i<p.size();i++)	// Checks if the population already exists
			if(i==populacao)
				flagv=1;	// The population exists
			
		if(flagv!=1)		
			return 2;		// The population does not exist
	}

	int type,flagv=0,a;

	if(arg1[0]=='S') type=0;		// If it is a soldier
	else if(arg1[0]=='P') type=1;	// If it is a peasant
	else if(arg1[0]=='K') type=2;	// If it is a knight
	else if(arg1[0]=='B') type=3;	// If it is a riding peasant
	else if(arg1[0]=='O') type=4;	// If it is an orc
	else return 0;

	for(unsigned int i=0;i<p[populacao]->unid[type].size();i++)	// Searches for the target in the units vector
		if(p[populacao]->unid[type][i]->GetN()==elemento)
		{
			flagv=1;	// The unit exists
			a=i;		// Saves the position of the unit in the vector
		}

	if(flagv!=1)		
		return 5;		// The unit does not exist

	int l=p[populacao]->unid[type][a]->GetX();
	int c=p[populacao]->unid[type][a]->GetY();

	if(l+18<=linhas-l&&c+18<=colunas-c)			// If there's a valid sector 6 positions SE from the unit
	{
		p[populacao]->unid[type][a]->SetDestlin(l+18);
		p[populacao]->unid[type][a]->SetDestcol(c);
		p[populacao]->unid[type][a]->SetTipocarga('S');	// Uses the cargo type variable to flag the direction of patrol movement (South)
	}
	else if(l+18<=linhas-l&&c-18<=colunas-c)	// If there's a valid sector 6 positions SW from the unit
	{
		p[populacao]->unid[type][a]->SetDestlin(l);
		p[populacao]->unid[type][a]->SetDestcol(c-18);
		p[populacao]->unid[type][a]->SetTipocarga('O');	// Uses the cargo type variable to flag the direction of patrol movement (West)
	}
	else if(l-18<=linhas-l&&c-18<=colunas-c)	// If there's a valid sector 6 positions NW from the unit
	{
		p[populacao]->unid[type][a]->SetDestlin(l-18);
		p[populacao]->unid[type][a]->SetDestcol(c);
		p[populacao]->unid[type][a]->SetTipocarga('N');	// Uses the cargo type variable to flag the direction of patrol movement (North)
	}
	else if(l-18<=linhas-l&&c+18<=colunas-c)	// If there's a valid sector 6 positions NE from the unit
	{
		p[populacao]->unid[type][a]->SetDestlin(l);
		p[populacao]->unid[type][a]->SetDestcol(c+18);
		p[populacao]->unid[type][a]->SetTipocarga('E');	// Uses the cargo type variable to flag the direction of patrol movement (East)
	}

	p[populacao]->unid[type][a]->tarefas.clear();		// Sets the patrolling duties
	p[populacao]->unid[type][a]->tarefas.push_back(1);
	p[populacao]->unid[type][a]->tarefas.push_back(2);
	p[populacao]->unid[type][a]->tarefas.push_back(3);
	p[populacao]->unid[type][a]->tarefas.push_back(4);
	p[populacao]->unid[type][a]->tarefas.push_back(5);
	p[populacao]->unid[type][a]->tarefas.push_back(6);
	p[populacao]->unid[type][a]->tarefas.push_back(7);
	p[populacao]->unid[type][a]->tarefas.push_back(8);
	p[populacao]->unid[type][a]->tarefas.push_back(9);
	p[populacao]->unid[type][a]->tarefas.push_back(10);
	p[populacao]->unid[type][a]->SetActual(9);

	return 1;
}