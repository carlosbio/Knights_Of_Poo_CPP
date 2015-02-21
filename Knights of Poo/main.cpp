// ------------------------------------------------------------------------------------------------------------	//
//																												//
// Descrição e implementação de um programa em C++ que consiste num jogo de estratégia do tipo Warcraft			//
//																												//
// Unidade curricular de Programação Orientada a Objectos 2014/2015 do curso de Engenharia Informática do ISEC	//
//																												//
// Trabalho realizado por Carlos da Silva (21220319)															//
//																												//
// Data: 07/12/2014																								//
//																												//
// ------------------------------------------------------------------------------------------------------------	//

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "Consola.h"
#include "Blocos.h"
#include "Jogo.h"
#include "Territorio.h"
#include "Populacao.h"

using namespace std;

void Inicio(Consola& c);
void printGameOver(Consola& c);
void printVictory(Consola& c);
void Scroll(Consola& con,Jogo& jogo);
void Load(string n,Jogo& jogo);

int charx;	// Global variable that saves the x coordinate
int chary;	// Global variable that saves the y coordinate

int main()
{
	Consola c;
	bool invalido,fim,load=false,config=true;
	string com,ficheiro;
	int linhas=7,colunas=7;
	string go1,go2,goto1,goto2,mina1,mina2,mke1,mke2,ataca1,ataca2,conserta1,conserta2,deambula1,deambula2;	// Variables for the dot "." argument

	c.setTextSize(8,8);
	c.setScreenSize(78,83);

	Inicio(c);	// Function that prints the main menu
	
	c.setBackgroundColor(c.CINZENTO);	// Sequence of commands for the prompt decoration
	c.setTextColor(c.PRETO);
	c.gotoxy(0,70);
	c.drawTab(c.TOP,81);
	c.drawTab(c.MID,81);	
	c.drawTab(c.BOT,81);

	do
	{
		invalido=true;		// Flag that validades input commands
		load=false;			// Flag that validades startup file loaded

		c.setCursor(1);
		c.setTextColor(c.PRETO);
		c.setBackgroundColor(c.BRANCO);
		c.gotoxy(1,71);

		cout<<"[>                                                                               "; // Amount of spaces needed for a white background

		c.gotoxy(3,71);

		getline(cin,com);		// Reads the input

		c.setTextColor(c.VERMELHO);
		c.setBackgroundColor(c.PRETO);
		c.gotoxy(3,75);

		istringstream iss(com);
		string arg[5];
		int num=0;

		for(int i=0;i<5;i++)   // Reads a maximum of 5 arguments
		{
			getline(iss,arg[i],' ');
			if(arg[i]!="")++num;
		}

		if(num==1)
		{
			if(arg[0]=="sair")
				return 0;
			else
				cout<<"Comando invalido...                                    ";
		}
		else if(num==2)
		{		
			if(arg[0]=="load") 
			{
				config=false;		// Deactivates config commands (sete, setu, ouro, madeira and pedra)

				ifstream in(arg[1]);
				ficheiro=arg[1];
				string com;

				getline(in,com);

				istringstream iss(com);
				string arg[5];
				int num=0;

				for(int i=0;i<5;i++)   // Reads a maximum of 5 arguments
				{
					getline(iss,arg[i],' ');
					if(arg[i]!="")++num;
				}

				if(num==3)
				{	
					if(arg[0]=="mkgame") 
					{
						istringstream iss2(arg[1]);
						istringstream iss3(arg[2]);
	
						iss2>>linhas;
						iss3>>colunas;

						if(linhas>=15&&colunas>=27)
							invalido=false;
						else
						{
							c.gotoxy(3,75);
							cout<<"Dados invalidos...                                    ";
						}

						load=true;	// Flags that the file was loaded
						in.close();
					}
				}
			}
			else
				cout<<"Comando invalido...                                   ";			
		}
		else if(num==3)
		{	
			if(arg[0]=="mkgame") 
			{
				istringstream iss2(arg[1]);
				istringstream iss3(arg[2]);
	
				iss2>>linhas;
				iss3>>colunas;

				if(linhas>=15&&colunas>=27)
					invalido=false;
				else
					cout<<"Comando invalido...                                ";
			}
		}
		else
			cout<<"Comando invalido...                                      ";		
	}
	while(invalido);  // Returns to the main menu

	//=======================================SETUP DO JOGO==========================================//

	linhas=linhas*3;	// Normalizes the amount of lines
	colunas=colunas*3;	// Normalizes the amount of columns

	Jogo j(linhas,colunas);	// Creates a game object with the map coordinates

	for(int i=0;i<linhas;i++)		// Fills the matrix with the coordinates
		for(int k=0;k<colunas;k++)
		{
			j.GetTerritorio().b[i][k].SetX(i);
			j.GetTerritorio().b[i][k].SetY(k);
		}

	if(load==true)			// Signals that there's data to be loaded from a file
	{
		Load(ficheiro,j);	// Reads an initial state from a file

		cout<<"Ficheiro carregado... (Enter para continuar)                    ";
		cin.get();
	}

	c.clrscr();	// Clears the screen
	j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
	j.DesenhaInfo(c);	// Draws the info bar

	c.setBackgroundColor(c.CINZENTO);	// Sequence of commands for the prompt decoration
	c.setTextColor(c.PRETO);
	c.gotoxy(0,70);
	c.drawTab(c.TOP,81);
	c.drawTab(c.MID,81);	
	c.drawTab(c.BOT,81);

	do
	{
		fim=false;

		c.setCursor(1);
		c.setTextColor(c.PRETO);
		c.setBackgroundColor(c.BRANCO);
		c.gotoxy(1,71);

		cout<<"[>                                                                               "; // Amount of spaces needed for a white background

		c.gotoxy(3,71);

		getline(cin,com);		// Reads the input

		c.setTextColor(c.VERMELHO);
		c.setBackgroundColor(c.PRETO);
		c.gotoxy(3,75);

		istringstream iss(com);
		string arg[6];
		int num=0;

		for(int i=0;i<6;i++)   // Reads a maximum of 6 arguments
		{
			getline(iss,arg[i],' ');
			if(arg[i]!="")++num;
		}

		if(arg[0].empty())		// If the enter key is pressed, without any command, it acts like the "next" command 
		{
			j.Next();
			j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
			cout<<"Iteracao seguinte...                                                     "<<endl;
		}
		else if(num==1)
		{
			if(arg[0]=="sair")			// Quits the program
				return 0;
			else if(arg[0]=="scroll")	// Activates the scroll mode
			{
				cout<<"Modo Scroll (pressionar 'c' para sair)                               "<<endl;
				Scroll(c,j);
			}
			else if(arg[0]=="reset")	// Resets the coordinates and redraws the visible map
			{
				cout<<"Coordenadas reiniciadas...                                           "<<endl;
				charx=0;					// Reset x value
				chary=0;					// Reset y value
				j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
			}
			else if(arg[0]=="next")		// Next iteration
			{
				j.Next();
				j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
				cout<<"Iteracao seguinte...                                      "<<endl;
			}
			else
				cout<<"Comando invalido...                                       ";	// Invalid entry
		}
		else if(num==2)
		{
			if(arg[0]=="pop"&&config==true)	// Command for a population creation
			{
				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

				int t=j.CriaPop(arg[1]);	// Asks for a population creation inside the game object

				if(t==0)
					cout<<"Ja existe uma populacao com esse nome...                     ";	// If that population name already exists
				if(t==2)
					cout<<"Atingido o nro maximo de populacoes...                       ";	// If it's reached the max number of populations
				else
					cout<<"Populacao "<<arg[1]<<" criada...                             ";	// Confirms population creation
			}
			else if(arg[0]=="next")
			{
				istringstream iss(arg[1]);		// Strategy to avoid the user to enter characters instead
				int it;
				iss>>it;

				for(int i=0;i<it;i++)
					j.Next();

				j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
				
				cout<<"Apos "<<it<<" iteracoes...                                         "<<endl;
			}
			else if(arg[0]=="mostra")	// Command that shows the info of a population
			{
				if(j.p.size()==0)	// Checks if a population has already been created
					cout<<"Ainda nao foram criadas populacoes...                              ";
				else
				{
					int flagv=0;	// Flag for population name validation
					int pindex=0;

					transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

					for(unsigned int i=0;i<j.p.size();i++)	// Checks if the population already exists
						if(j.p[i]->GetNome()==arg[1])
						{
							flagv=1;
							pindex=i;	// Saves the index of the population
						}

					if(flagv==1)		// The population exists
					{
						cout<<"A mostrar info...				                             ";
						j.DesenhaInfo(c);	// Draws the info bar
						j.Mostra(c,pindex);	// Shows the info of the population identified by its index
					}
					else
						cout<<"Populacao nao existente...                                    ";	// The population does not exists
				}
			}
			else if(arg[0]=="load")	// Load a text file
			{
				config=false;		// Deactivates config commands (sete, setu, ouro, madeira and pedra)

				ifstream in(arg[1]);
				ficheiro=arg[1];

				Load(ficheiro,j);	// Reads an initial state from a file
				in.close();

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);
				cout<<"Dados carregados...                                           ";
			}
			else if(arg[0]=="sel")	// Command for selecting an object
			{
				string popul="P01";

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

				j.DesenhaInfo(c);	// Draws the info bar
				int i=j.Selecciona(c,arg[1],popul,charx,chary);	// Selects the object, with its name and population sent as arguments

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"A unidade indicada nao existe...                               ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                             ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                          ";
				else if(i==4)
					cout<<"Comando invalido... (sel <id>)                                 ";
				else
					cout<<"Unidade seleccionada...                                        ";
			}
			else if(arg[0]=="stop")	// Command for the unit to cancel its duties
			{
				string popul="P01";

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

				int i=j.Stop(arg[1],popul);

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"A unidade indicada nao existe...                              ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                            ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                         ";
				else if(i==4)
					cout<<"Comando invalido... (stop <id>)                               ";
				else
					cout<<"A unidade interrompeu a tarefa...                             ";
			}
			else if(arg[0]=="mku")	// Orders the building to train an unit
			{
				if(arg[1]=="camp"||arg[1]=="sold"||arg[1]=="cav"||arg[1]=="cv"||arg[1]=="orc")	// Checks is the unit name is valid
				{
					if(j.p.size()==0)	// Checks if a population has already been created
						cout<<"Ainda nao foram criadas populacoes...                        ";
					else
					{
						int i=j.Treina(0,arg[1]);	// Gives the command to train an unit
						j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
						
						if(i==1)
							cout<<"Nao existem quintas suficientes...                        ";
						else if(i==2)
							cout<<"Unidade invalida...                                       ";
						else if(i==3)
							cout<<"Ja existe uma unidade desse tipo...                       ";
						else if(i==5)
							cout<<"Comando invalido... (mku <oque>)                          ";
						else if(i==6)
							cout<<"Nao existem recursos suficientes...                       ";
						else if(i==7)
							cout<<"Nao existe um castelo...                                  ";
						else if(i==8)
							cout<<"Nao existe um quartel...                                  ";
						else if(i==9)
							cout<<"Nao existe um estabulo...                                 ";
						else if(i==0)
							cout<<"Instrucao recebida...                                     ";
					}
				}
				else
					cout<<"Nome de unidade invalido...                                   ";
			}
			else if(arg[0]=="deambula")		// Command to order an unit to perform a random patrol
			{
				int i;
				string popul="P01";

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]==".")
					i=j.Deambula(deambula1,popul,linhas,colunas);
				else
					i=j.Deambula(arg[1],popul,linhas,colunas);

				if(arg[1]!=".")
					deambula1=arg[1];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Impossivel mover a unidade...                                ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                           ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                        ";
				else if(i==4)
					cout<<"Comando invalido... (deambula <id>)                          ";
				else if(i==5)
					cout<<"A unidade nao existe...                                      ";
				else
					cout<<"Instrucao recebida...                                        ";
			}
			else
				cout<<"Comando invalido...                                        ";	// Invalid entry
		}
		else if(num==3)
		{
			if(arg[0]=="sel"&&config==true)	// Command for selecting an object
			{
				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

				j.DesenhaInfo(c);	// Draws the info bar
				int i=j.Selecciona(c,arg[1],arg[2],charx,chary);	// Selects the object, with its name and population sent as arguments

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"A unidade indicada nao existe...                          ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                        ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                     ";
				else if(i==4)
					cout<<"Comando invalido... (deambula <id>)                       ";
				else
					cout<<"Unidade seleccionada...                                   ";
			}
			else if(arg[0]=="sector")	// Get info of a sector
			{
				istringstream iss2(arg[1]);		// Strategy to avoid the user to enter characters instead
				istringstream iss3(arg[2]);		// of numbers, which can cause the program to crash
				int cx,cy;
	
				iss2>>cx;
				iss3>>cy;

				if(cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
					cout<<"Coordenadas invalidas...                                  ";
				else
				{
					j.DesenhaInfo(c);	// Draws the info bar
					j.Sector(c,cx*3,cy*3);

					c.setTextColor(c.VERMELHO);
					c.gotoxy(3,75);

					cout<<"Info do sector...                                       ";
				}
			}
			else if(arg[0]=="stop"&&config==true)	// Command for the unit to cancel its duties
			{
				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

				int i=j.Stop(arg[1],arg[2]);

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"A unidade indicada nao existe...                              ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                            ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                         ";
				else if(i==4)
					cout<<"Comando invalido... (stop <id>)                               ";
				else
					cout<<"A unidade interrompeu a tarefa...                             ";
			}
			else if(arg[0]=="mku"&&config==true)	// Orders the building to train an unit
			{
				if(arg[2]=="camp"||arg[2]=="sold"||arg[2]=="cav"||arg[2]=="cv"||arg[2]=="orc")	// Checks is the unit name is valid
				{
					if(j.p.size()==0)	// Checks if a population has already been created
						cout<<"Ainda nao foram criadas populacoes...                      ";
					else
					{
						int flagv=0;	// Flag for population name validation
						int pindex=0;

						transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

						for(unsigned int i=0;i<j.p.size();i++)	// Checks if the population already exists
							if(j.p[i]->GetNome()==arg[1])
							{
								flagv=1;
								pindex=i;	// Saves the index of the population
							}

						if(flagv==1)		// The population exists
						{
							int i=j.Treina(pindex,arg[2]);	// Gives the command to train an unit
							j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
						
							if(i==1)
								cout<<"Nao existem quintas suficientes...                        ";
							else if(i==2)
								cout<<"Unidade invalida...                                       ";
							else if(i==3)
								cout<<"Ja existe uma unidade desse tipo...                       ";
							else if(i==5)
								cout<<"Comando invalido... (mku <oque>)                          ";
							else if(i==6)
								cout<<"Nao existem recursos suficientes...                       ";
							else if(i==7)
								cout<<"Nao existe um castelo...                                  ";
							else if(i==8)
								cout<<"Nao existe um quartel...                                  ";
							else if(i==9)
								cout<<"Nao existe um estabulo...                                 ";
							else if(i==0)
								cout<<"Instrucao recebida...                                     ";
						}
						else
							cout<<"Populacao nao existente...                            ";	// The population does not exists
					}
				}
				else
					cout<<"Nome de unidade invalido...                                   ";
			}
			else if(arg[0]=="ouro"&&config==true)	// Command that adds gold to the population's castle
			{
				istringstream iss(arg[2]);
				int n;
				iss>>n;

				if(j.p.size()==0)	// Checks if a population has already been created
					cout<<"Ainda nao foram criadas populacoes...                            ";
				else
				{
					int flagv=0;	// Flag for population name validation
					int pindex=0;

					transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

					for(unsigned int i=0;i<j.p.size();i++)	// Checks if the population already exists
						if(j.p[i]->GetNome()==arg[1])
						{
							flagv=1;
							pindex=i;	// Saves the index of the population
						}

					if(flagv==1)		// The population exists
					{
						if(j.p[pindex]->edif[0].size()!=0)	// If the population's castle exists
						{
							j.p[pindex]->edif[0][0]->SetOuro(j.p[pindex]->edif[0][0]->GetOuro()+n);	// The gold is added
							cout<<"Ouro adicionado ao castelo...                     ";
						}
						else
							cout<<"Populacao nao tem castelo...                      ";	// The population has no castle
					}
					else
						cout<<"Populacao nao existente...                            ";	// The population does not exists
				}
			}
			else if(arg[0]=="pedra"&&config==true)	// Command that adds stone to the population's castle
			{
				istringstream iss(arg[2]);
				int n;
				iss>>n;

				if(j.p.size()==0)	// Checks if a population has already been created
					cout<<"Ainda nao foram criadas populacoes...                                    ";
				else
				{
					int flagv=0;	// Flag for population name validation
					int pindex=0;

					transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

					for(unsigned int i=0;i<j.p.size();i++)	// Checks if the population already exists
						if(j.p[i]->GetNome()==arg[1])
						{
							flagv=1;
							pindex=i;	// Saves the index of the population
						}

					if(flagv==1)		// The population exists
					{
						if(j.p[pindex]->edif[0].size()!=0)	// If the population's castle exists
						{
							j.p[pindex]->edif[0][0]->SetPedra(j.p[pindex]->edif[0][0]->GetPedra()+n);	// The stone is added
							cout<<"Pedra adicionada ao castelo...                     ";
						}
						else
							cout<<"Populacao nao tem castelo...                       ";	// The population has no castle
					}
					else
						cout<<"Populacao nao existente...                             ";	// The population does not exists
				}
			}
			else if(arg[0]=="madeira"&&config==true)	// Command that adds wood to the population's castle
			{
				istringstream iss(arg[2]);
				int n;
				iss>>n;

				if(j.p.size()==0)	// Checks if a population has already been created
					cout<<"Ainda nao foram criadas populacoes...                               ";
				else
				{
					int flagv=0;	// Flag for population name validation
					int pindex=0;

					transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

					for(unsigned int i=0;i<j.p.size();i++)	// Checks if the population already exists
						if(j.p[i]->GetNome()==arg[1])
						{
							flagv=1;
							pindex=i;	// Saves the index of the population
						}

					if(flagv==1)		// The population exists
					{
						if(j.p[pindex]->edif[0].size()!=0)	// If the population's castle exists
						{
							j.p[pindex]->edif[0][0]->SetMadeira(j.p[pindex]->edif[0][0]->GetMadeira()+n);	// The wood is added
							cout<<"Madeira adicionada ao castelo...                     ";
						}
						else
							cout<<"Populacao nao tem castelo...                         ";	// The population has no castle
					}
					else
						cout<<"Populacao nao existente...                               ";	// The population does not exists
				}
			}
			else if(arg[0]=="deambula"&&config==true)		// Command to order an unit to perform a random patrol
			{
				int i;

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]=="."&&arg[2]==".")
					i=j.Deambula(deambula1,deambula2,linhas,colunas);
				else
					i=j.Deambula(arg[1],arg[2],linhas,colunas);

				deambula1=arg[1];
				deambula2=arg[2];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Impossivel mover a unidade...                                ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                           ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                        ";
				else if(i==4)
					cout<<"Comando invalido... (deambula <id>)                          ";
				else if(i==5)
					cout<<"A unidade nao existe...                                      ";
				else
					cout<<"Instrucao recebida...                                        ";
			}
			else if(arg[0]=="mina")	// Gives the harvesting command
			{
				int i;
				string popul="P01";

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]==".")
					i=j.Recolhe(mina1,popul,arg[2]);	// Gives an unit the command to harvest resources
				else
					i=j.Recolhe(arg[1],popul,arg[2]);	// Gives an unit the command to harvest resources

				if(arg[1]!=".")
					mina1=arg[1];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Unidade invalida...                                          ";
				else if(i==2)
					cout<<"O recurso indicado nao existe...                             ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                        ";
				else if(i==4)
					cout<<"Comando invalido... (mina <id>)                              ";
				else
					cout<<"\"Ready to work!\"                                           ";
			}
			else if(arg[0]=="conserta")	// Gives the repairing command
			{
				int i;
				string popul="P01";

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]==".")
					i=j.Conserta(conserta1,popul,arg[2],popul);	// Selects the object, with its name and population sent as arguments
				else
					i=j.Conserta(arg[1],popul,arg[2],popul);	// Selects the object, with its name and population sent as arguments

				if(arg[1]!=".")
					conserta1=arg[1];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Unidade invalida...                                        ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                         ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                      ";
				else if(i==4)
					cout<<"Comando invalido... (conserta <id> <ide>)                  ";
				else if(i==5)
					cout<<"O edificio nao precisa conserto...                         ";
				else if(i==6)
					cout<<"Nao existem recursos suficientes...                        ";
				else
					cout<<"\"Ready to work!\"                                         ";
			}
			else
				cout<<"Comando invalido...                                            ";	// Invalid entry
		}
		else if(num==4)
		{
			if(arg[0]=="setf"&&config==true)	// If command is entered in order to place a resources site
			{
				if(arg[1]=="min"||arg[1]=="ped"||arg[1]=="flo")	// Checks is the resource name is valid
				{
					istringstream iss2(arg[2]);		// Strategy to avoid the user to enter characters instead
					istringstream iss3(arg[3]);		// of numbers, which can cause the program to crash
					int cx,cy;
	
					iss2>>cx;
					iss3>>cy;

					if (cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
						cout<<"Coordenadas invalidas...                                  ";
					else
					{
						int i=j.AddRecurso(arg[1],cx*3,cy*3);	// Adds a resource to the game object
						j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
						
						if(i==1)
							cout<<"Recurso colocado...                                   ";
						else if(i==2)
							cout<<"O sector esta ocupado...                              ";
						else
							cout<<"Erro ao colocar o recurso...                          ";
					}
				}
				else
					cout<<"Nome de recurso invalido...                                   ";
			}
			else if(arg[0]=="mina"&&config==true)	// Gives the harvesting command
			{
				int i;

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case
				transform(arg[3].begin(),arg[3].end(),arg[3].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]=="."&&arg[2]==".")
					i=j.Recolhe(mina1,mina2,arg[3]);	// Gives an unit the command to harvest resources
				else
					i=j.Recolhe(arg[1],arg[2],arg[3]);	// Gives an unit the command to harvest resources

				mina1=arg[1];
				mina2=arg[2];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Unidade invalida...                                        ";
				else if(i==2)
					cout<<"O recurso indicado nao existe...                           ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                      ";
				else if(i==4)
					cout<<"Comando invalido... (mina <id>)                            ";
				else
					cout<<"\"Ready to work!\"                                         ";
			}
			else if(arg[0]=="goto")	// Command to order an unit to perform a movement
			{
				istringstream iss2(arg[2]);		// Strategy to avoid the user to enter characters instead
				istringstream iss3(arg[3]);		// of numbers, which can cause the program to crash
				int cx,cy,i;
				string popul="P01";
	
				iss2>>cx;
				iss3>>cy;

				if (cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
					cout<<"Coordenadas invalidas...                                   ";
				else
				{
					transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

					if(arg[1]==".")
						i=j.Goto(goto1,popul,cx*3,cy*3);	// Moves the object, with its name and population sent as arguments
					else
						i=j.Goto(arg[1],popul,cx*3,cy*3);	// Moves the object, with its name and population sent as arguments

					if(arg[1]!=".")
						goto1=arg[1];

					c.setTextColor(c.VERMELHO);
					c.gotoxy(3,75);

					if(i==0)	// If the object does not exists
						cout<<"Impossivel mover a unidade...                                 ";
					else if(i==2)
						cout<<"A populacao indicada nao existe...                            ";
					else if(i==3)
						cout<<"Ainda nao foram criadas populacoes...                         ";
					else if(i==4)
						cout<<"Comando invalido... (goto <id> < linha> < coluna>)            ";
					else
						cout<<"Instrucao recebida...                                         ";
				}
			}
			else if(arg[0]=="go")	// Command to order an unit to perform a movement
			{
				istringstream iss2(arg[2]);		// Strategy to avoid the user to enter characters instead
				istringstream iss3(arg[3]);		// of numbers, which can cause the program to crash
				int cx,cy,i;
				string popul="P01";
	
				iss2>>cx;
				iss3>>cy;
				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]==".")
					i=j.Go(go1,popul,cx*3,cy*3,linhas,colunas);	// Moves the object, with its name and population sent as arguments
				else
					i=j.Go(arg[1],popul,cx*3,cy*3,linhas,colunas);	// Moves the object, with its name and population sent as arguments

				if(arg[1]!=".")
					go1=arg[1];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Impossivel mover a unidade...                                      ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                                 ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                              ";
				else if(i==4)
					cout<<"Coordenadas invalidas... (go <id> <delta_linha> <delta_coluna>     ";
				else if(i==5)
					cout<<"Comando invalido...                                                ";
				else
					cout<<"Instrucao recebida...                                              ";
			}
			else if(arg[0]=="ataca")	// Gives the attack command
			{
				int i;
				string popul="P01";

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case
				transform(arg[3].begin(),arg[3].end(),arg[3].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]==".")
					i=j.Ataca(ataca1,popul,arg[2],arg[3]);	// Selects the object, with its name and population sent as arguments
				else
					i=j.Ataca(arg[1],popul,arg[2],arg[3]);	// Selects the object, with its name and population sent as arguments

				if(arg[1]!=".")
					ataca1=arg[1];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Unidade invalida...                                        ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                         ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                      ";
				else if(i==4)
					cout<<"Comando invalido... (ataca <id> <idvitima>)                ";
				else if(i==5)
					cout<<"A unidade nao pode atacar...                               ";
				else
					cout<<"Instrucao recebida...                                      ";
			}
			else
				cout<<"Comando invalido...                                            ";
		}
		else if(num==5)
		{
			if(arg[0]=="sete"&&config==true)	// If command is entered in order to place a building
			{
				if(arg[2]=="cas"||arg[2]=="quar"||arg[2]=="est"||arg[2]=="quin")	// Checks is the building name is valid
				{
					istringstream iss2(arg[3]);		// Strategy to avoid the user to enter characters instead
					istringstream iss3(arg[4]);		// of numbers, which can cause the program to crash
					int cx,cy;
	
					iss2>>cx;
					iss3>>cy;

					if (cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
						cout<<"Coordenadas invalidas...                                                   ";
					else if(j.p.size()==0)	// Checks if a population has already been created
						cout<<"Ainda nao foram criadas populacoes...                                      ";
					else
					{
						int flagv=0;	// Flag for population name validation
						int pop=0;

						transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

						for(unsigned int i=0;i<j.p.size();i++)	// Checks if the population already exists
							if(j.p[i]->GetNome()==arg[1])
							{
								flagv=1;
								pop=i;	// Saves the index of the population
							}

						if(flagv==1)	// The population exists
						{
							int i=j.p[pop]->AddEdificio(arg[2],cx*3,cy*3,j.GetTerritorio().b,pop,linhas,colunas);	// Adds a building to the game object
							j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
						
							if(i==1)
								cout<<"Edificio colocado...                                          ";
							else if(i==2)
								cout<<"Ja existe um edificio desse tipo...                           ";
							else if(i==3)
								cout<<"O sector esta ocupado...                                      ";
							else
								cout<<"Erro ao colocar edificio...                                   ";
						}
						else
							cout<<"Populacao nao existente...                                        ";	// The population does not exists
					}
				}
				else
					cout<<"Nome de edificio invalido...                                ";
			}
			else if(arg[0]=="setu"&&config==true)	// If command is entered in order to place an unit
			{
				if(arg[2]=="camp"||arg[2]=="sold"||arg[2]=="cav"||arg[2]=="cv"||arg[2]=="orc")	// Checks is the unit name is valid
				{
					istringstream iss2(arg[3]);		// Strategy to avoid the user to enter characters instead
					istringstream iss3(arg[4]);		// of numbers, which can cause the program to crash
					int cx,cy;
	
					iss2>>cx;
					iss3>>cy;

					if (cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
						cout<<"Coordenadas invalidas...                                        ";
					else if(j.p.size()==0)	// Checks if a population has already been created
						cout<<"Ainda nao foram criadas populacoes...                           ";
					else
					{
						int flagv=0;	// Flag for population name validation
						int pop=0;

						transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

						for(unsigned int i=0;i<j.p.size();i++)	// Checks if the population already exists
							if(j.p[i]->GetNome()==arg[1])
							{
								flagv=1;
								pop=i;	// Saves the index of the population
							}

						if(flagv==1)	// The population exists
						{
							int i=j.p[pop]->AddUnidade(arg[2],cx*3,cy*3,j.GetTerritorio().b,pop,linhas,colunas);	// Adds an unit to the game object
							j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
						
							if(i==1)
								cout<<"Unidade colocada...                                       ";
							else if(i==2)
								cout<<"Ja existe uma unidade desse tipo...                       ";
							else
								cout<<"Erro ao colocar a unidade...                              ";
						}
						else
							cout<<"Populacao nao existente...                                    ";	// The population does not exists
					}
				}
				else
					cout<<"Nome de unidade invalido...                              ";
			}
			else if(arg[0]=="goto"&&config==true)	// Command to order an unit to perform a movement
			{
				istringstream iss2(arg[3]);		// Strategy to avoid the user to enter characters instead
				istringstream iss3(arg[4]);		// of numbers, which can cause the program to crash
				int cx,cy,i;
	
				iss2>>cx;
				iss3>>cy;

				if (cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
					cout<<"Coordenadas invalidas...                                      ";
				else
				{
					transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
					transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

					if(arg[1]=="."&&arg[2]==".")
						i=j.Goto(goto1,goto2,cx*3,cy*3);	// Moves the object, with its name and population sent as arguments
					else
						i=j.Goto(arg[1],arg[2],cx*3,cy*3);	// Moves the object, with its name and population sent as arguments

					goto1=arg[1];
					goto2=arg[2];

					c.setTextColor(c.VERMELHO);
					c.gotoxy(3,75);

					if(i==0)	// If the object does not exists
						cout<<"Impossivel mover a unidade...                                     ";
					else if(i==2)
						cout<<"A populacao indicada nao existe...                                ";
					else if(i==3)
						cout<<"Ainda nao foram criadas populacoes...                             ";
					else if(i==4)
						cout<<"Comando invalido... (goto <id> < linha> < coluna>)                ";
					else
						cout<<"Instrucao recebida...                                             ";
				}
			}
			else if(arg[0]=="go"&&config==true)	// Command to order an unit to perform a movement
			{
				istringstream iss2(arg[3]);		// Strategy to avoid the user to enter characters instead
				istringstream iss3(arg[4]);		// of numbers, which can cause the program to crash
				int cx,cy,i;
	
				iss2>>cx;
				iss3>>cy;
				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]=="."&&arg[2]==".")
					i=j.Go(go1,go2,cx*3,cy*3,linhas,colunas);	// Moves the object, with its name and population sent as arguments
				else
					i=j.Go(arg[1],arg[2],cx*3,cy*3,linhas,colunas);	// Moves the object, with its name and population sent as arguments

				go1=arg[1];
				go2=arg[2];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Impossivel mover a unidade...                                ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                           ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                        ";
				else if(i==4)
					cout<<"Coordenadas invalidas...                                     ";
				else if(i==5)
					cout<<"Comando invalido... (go <id> <delta_linha> <delta_coluna>)   ";
				else
					cout<<"Instrucao recebida...                                        ";
			}
			else if(arg[0]=="ataca"&&config==true)	// Gives the attack command
			{
				int i;

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case
				transform(arg[3].begin(),arg[3].end(),arg[3].begin(),::toupper);	// Converts the string to upper case
				transform(arg[4].begin(),arg[4].end(),arg[4].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]=="."&&arg[2]==".")
					i=j.Ataca(ataca1,ataca2,arg[3],arg[4]);	// Selects the object, with its name and population sent as arguments
				else
					i=j.Ataca(arg[1],arg[2],arg[3],arg[4]);	// Selects the object, with its name and population sent as arguments

				ataca1=arg[1];
				ataca2=arg[2];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Unidade invalida...                                        ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                         ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                      ";
				else if(i==4)
					cout<<"Comando invalido... (ataca <id> <idvitima>)                 ";
				else if(i==5)
					cout<<"A unidade nao pode atacar...                               ";
				else
					cout<<"Instrucao recebida...                                      ";
			}
			else if(arg[0]=="conserta"&&config==true)	// Gives the repairing command
			{
				int i;

				transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
				transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case
				transform(arg[3].begin(),arg[3].end(),arg[3].begin(),::toupper);	// Converts the string to upper case
				transform(arg[4].begin(),arg[4].end(),arg[4].begin(),::toupper);	// Converts the string to upper case

				if(arg[1]=="."&&arg[2]==".")
					i=j.Conserta(conserta1,conserta2,arg[3],arg[4]);	// Selects the object, with its name and population sent as arguments
				else
					i=j.Conserta(arg[1],arg[2],arg[3],arg[4]);	// Selects the object, with its name and population sent as arguments

				conserta1=arg[1];
				conserta2=arg[2];

				c.setTextColor(c.VERMELHO);
				c.gotoxy(3,75);

				if(i==0)	// If the object does not exists
					cout<<"Unidade invalida...                                        ";
				else if(i==2)
					cout<<"A populacao indicada nao existe...                         ";
				else if(i==3)
					cout<<"Ainda nao foram criadas populacoes...                      ";
				else if(i==4)
					cout<<"Comando invalido... (conserta <id> <ide>)                  ";
				else if(i==5)
					cout<<"O edificio nao precisa conserto...                         ";
				else if(i==6)
					cout<<"Nao existem recursos suficientes...                        ";
				else
					cout<<"\"Ready to work!\"                                         ";
			}
			else if(arg[0]=="mke")	// Orders the unit to make a building
			{
				if(arg[2]=="cas"||arg[2]=="quar"||arg[2]=="est"||arg[2]=="quin")	// Checks is the building name is valid
				{
					istringstream iss2(arg[3]);		// Strategy to avoid the user to enter characters instead
					istringstream iss3(arg[4]);		// of numbers, which can cause the program to crash
					int cx,cy,i;
					string popul="P01";
	
					iss2>>cx;
					iss3>>cy;

					if (cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
						cout<<"Coordenadas invalidas...                                      ";
					else
					{
						transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case

						if(arg[1]==".")
							i=j.Constroi(mke1,popul,arg[2],cx*3,cy*3);	// Gives the command to make a building to the game object
						else
							i=j.Constroi(arg[1],popul,arg[2],cx*3,cy*3);	// Gives the command to make a building to the game object

						if(arg[1]!=".")
							mke1=arg[1];

						j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
						
						if(i==2)
							cout<<"Unidade invalida...                                           ";
						else if(i==3)
							cout<<"Ja existe um edificio desse tipo...                           ";
						else if(i==4)
							cout<<"O sector esta ocupado...                                      ";
						else if(i==5)
							cout<<"Comando invalido... (mke <id> <oque> <linha> <coluna>)        ";
						else if(i==6)
							cout<<"Nao existem recursos suficientes...                           ";
						else
							cout<<"\"Ready to work!\"                                            ";
					}
				}
				else
					cout<<"Nome de edificio invalido...                                ";
			}
			else
				cout<<"Comando invalido...                                           ";	// Invalid entry
		}
		else if(num==6)
		{
			if(arg[0]=="mke"&&config==true)	// Orders the unit to make a building
			{
				if(arg[3]=="cas"||arg[3]=="quar"||arg[3]=="est"||arg[3]=="quin")	// Checks is the building name is valid
				{
					istringstream iss2(arg[4]);		// Strategy to avoid the user to enter characters instead
					istringstream iss3(arg[5]);		// of numbers, which can cause the program to crash
					int cx,cy,i;
	
					iss2>>cx;
					iss3>>cy;

					if (cx<0||cx>=(linhas/3)||cy<0||cy>=(colunas/3))	// Checks if the coordinates are valid
						cout<<"Coordenadas invalidas...                                     ";
					else
					{
						transform(arg[1].begin(),arg[1].end(),arg[1].begin(),::toupper);	// Converts the string to upper case
						transform(arg[2].begin(),arg[2].end(),arg[2].begin(),::toupper);	// Converts the string to upper case

						if(arg[1]=="."&&arg[2]==".")
							i=j.Constroi(mke1,mke2,arg[3],cx*3,cy*3);	// Gives the command to make a building to the game object
						else
							i=j.Constroi(arg[1],arg[2],arg[3],cx*3,cy*3);	// Gives the command to make a building to the game object

						mke1=arg[1];
						mke2=arg[2];

						j.DesenhaMapa(c,charx,chary);	// Draws the visible area of the map
						
						if(i==2)
							cout<<"Unidade invalida...                                           ";
						else if(i==3)
							cout<<"Ja existe um edificio desse tipo...                           ";
						else if(i==4)
							cout<<"O sector esta ocupado...                                      ";
						else if(i==5)
							cout<<"Comando invalido... (mke <id> <oque> <linha> <coluna>)        ";
						else if(i==6)
							cout<<"Nao existem recursos suficientes...                           ";
						else
							cout<<"\"Ready to work!\"                                            ";
					}
				}
				else
					cout<<"Nome de edificio invalido...                                ";
			}
		}
		else
			cout<<"Comando invalido...                                            ";	// Invalid entry

		if(j.p[0]->edif->size()==0&&j.p[0]->unid->size()==0&&j.p.size()>1)	// Defeat
		{
			printGameOver(c);
			fim=true;
		}

		int flagvic=0;

		if(j.p[0]->edif->size()!=0&&j.p[0]->unid->size()!=0&&j.p.size()>1)	// Victory
		{
			for(unsigned int i=1;i<j.p.size();i++)
				if(j.p[i]->edif->size()!=0||j.p[i]->unid->size()!=0)
					flagvic=1;
			
			if(flagvic==0)
			{
				printVictory(c);
				fim=true;
			}
		}

	}
	while(fim==false);

	return 0;
}

void Load(string n,Jogo& jogo)		// Reads an initial state from a file
{
	string com;
	ifstream file(n);

	while(file.peek()!=EOF)
	{
		getline(file,com);		// Reads the input

		istringstream iss(com);
		string arg[5];
		int num=0;

		for(int i=0;i<5;i++)   // Reads a maximum of 5 arguments
		{
			getline(iss,arg[i],' ');
			if(arg[i]!="")++num;
		}

		if(num==2)
			if(arg[0]=="pop")	// Command for a population creation
				int t=jogo.CriaPop(arg[1]);	// Asks for a population creation inside the game object

		if(num==3)
			if(arg[0]=="deambula")		// Command to order an unit to perform a random patrol
				int i=jogo.Deambula(arg[1],arg[2],jogo.GetTerritorio().GetLinhas(),jogo.GetTerritorio().GetColunas());

		if(num==4)
		{
			if(arg[0]=="setf")	// If command is entered in order to place a resources site
			{
				if(arg[1]=="min"||arg[1]=="ped"||arg[1]=="flo")	// Checks is the resource name is valid
				{
					istringstream iss2(arg[2]);
					istringstream iss3(arg[3]);
					int cx,cy;
	
					iss2>>cx;
					iss3>>cy;

					int i=jogo.AddRecurso(arg[1],cx*3,cy*3);	// Adds a resource to the game object
				}
			}	
			else if(arg[0]=="mina")
				int i=jogo.Recolhe(arg[1],arg[2],arg[3]);	// Gives an unit the command to harvest resources
		}

		if(num==5)
		{
			if(arg[0]=="sete")	// If command is entered in order to place a building
			{
					istringstream iss2(arg[3]);
					istringstream iss3(arg[4]);
					int cx,cy;
	
					iss2>>cx;
					iss3>>cy;

					int flagv=0;	// Flag for population name validation
					int pop=0;

					for(unsigned int i=0;i<jogo.p.size();i++)	// Checks if the population already exists
						if(jogo.p[i]->GetNome()==arg[1])
						{
							flagv=1;
							pop=i;	// Saves the index of the population
						}

					if(flagv==1)	// The population exists
						int i=jogo.p[pop]->AddEdificio(arg[2],cx*3,cy*3,jogo.GetTerritorio().b,pop,jogo.GetTerritorio().GetLinhas(),jogo.GetTerritorio().GetColunas());	// Adds a building to the game object
			}
			else if(arg[0]=="setu")	// If command is entered in order to place an unit
			{
				istringstream iss2(arg[3]);		// Strategy to avoid the user to enter characters instead
				istringstream iss3(arg[4]);		// of numbers, which can cause the program to crash
				int cx,cy;
	
				iss2>>cx;
				iss3>>cy;

				int flagv=0;	// Flag for population name validation
				int pop=0;

				for(unsigned int i=0;i<jogo.p.size();i++)	// Checks if the population already exists
					if(jogo.p[i]->GetNome()==arg[1])
					{
						flagv=1;
						pop=i;	// Saves the index of the population
					}

				if(flagv==1)	// The population exists
					int i=jogo.p[pop]->AddUnidade(arg[2],cx*3,cy*3,jogo.GetTerritorio().b,pop,jogo.GetTerritorio().GetLinhas(),jogo.GetTerritorio().GetColunas());	// Adds an unit to the game object				
			}
			else if(arg[0]=="ataca")
				int i=jogo.Ataca(arg[1],arg[2],arg[3],arg[4]);	// Selects the object, with its name and population sent as arguments
		}
	}

	file.close();
}

void Inicio(Consola &c)
{
	c.clrscr();
	c.gotoxy(0,3);
	c.setTextColor(c.BRANCO);
	c.setBackgroundColor(c.PRETO);
	
	cout<<"\t ___   _  __    _  ___   _______  __   __  _______  _______ "<<endl;
	cout<<"\t|   | | ||  |  | ||   | |       ||  | |  ||       ||       |"<<endl;
	cout<<"\t|   |_| ||   |_| ||   | |    ___||  |_|  ||_     _||  _____|"<<endl;
	cout<<"\t|      _||       ||   | |   | __ |       |  |   |  | |_____ "<<endl;
	cout<<"\t|     |_ |  _    ||   | |   ||  ||       |  |   |  |_____  |"<<endl;
	cout<<"\t|    _  || | |   ||   | |   |_| ||   _   |  |   |   _____| |"<<endl;
	cout<<"\t|___| |_||_|  |__||___| |_______||__| |__|  |___|  |_______|"<<endl<<endl<<endl<<endl<<endl;
	cout<<"\t _______  _______ "<<endl;
	cout<<"\t|       ||       |"<<endl;
	cout<<"\t|   _   ||    ___|"<<endl;
	cout<<"\t|  | |  ||   |___ "<<endl;
	cout<<"\t|  |_|  ||    ___|"<<endl;
	cout<<"\t|       ||   |    "<<endl;
	cout<<"\t|_______||___|    "<<endl<<endl<<endl<<endl<<endl;
	cout<<"\t _______  _______  _______ "<<endl;
	cout<<"\t|       ||       ||       |"<<endl;
	cout<<"\t|    _  ||   _   ||   _   |"<<endl;
	cout<<"\t|   |_| ||  | |  ||  | |  |"<<endl;
	cout<<"\t|    ___||  |_|  ||  |_|  |"<<endl;
	cout<<"\t|   |    |       ||       |"<<endl;
	cout<<"\t|___|    |_______||_______|"<<endl;

	c.gotoxy(3,40);

	cout<<"\t             _____                                                 "<<endl;
	cout<<"\t             \\   /                                                  "<<endl;
	cout<<"\t             |   |                                                  "<<endl;
	cout<<"\t __          |   |_____________________________________________     "<<endl;
	cout<<"\t|  |_________|   |                                              \\   "<<endl;
	cout<<"\t|  |         |   |________________________________________________\\ "<<endl;
	cout<<"\t|  |_________|   |                                                / "<<endl;
	cout<<"\t|__|         |   |_____________________________________________ /   "<<endl;
	cout<<"\t             |   |                                                  "<<endl;
	cout<<"\t             |   |                                                  "<<endl;
	cout<<"\t             /___\\                                                  "<<endl;

	c.gotoxy(3,58);
	c.setTextColor(c.VERMELHO);
	cout<<"\t\tLISTA DE COMANDOS:\n"<<endl<<endl;
	c.setTextColor(c.BRANCO);
	c.setTextColor(c.BRANCO);
	cout<<"\t\t"<<(char) 16<<" mkgame <lin> <col> (min: 15 x 27)"<<endl<<endl; 
	cout<<"\t\t"<<(char) 16<<" load <ficheiro.txt>"<<endl<<endl;  
	cout<<"\t\t"<<(char) 16<<" sair   "<<endl;
}

void printGameOver(Consola& c)
{
	c.clrscr();
	c.gotoxy(0,32);
	c.setTextColor(c.VERMELHO);
	c.setBackgroundColor(c.PRETO);
	cout<<"                                                                             "<<endl;
	cout<<"                .oooooo.                                                     "<<endl;
	cout<<"               d8P'  `Y8b                                                    "<<endl;
	cout<<"              888            .oooo.   ooo. .oo.  .oo.    .ooooo.             "<<endl;
	cout<<"              888           `P  )88b  `888P\"Y88bP\"Y88b  d88' `88b          "<<endl;
	cout<<"              888     ooooo  .oP\"888   888   888   888  888ooo888           "<<endl;
	cout<<"              `88.    .88'  d8(  888   888   888   888  888    .o            "<<endl;
	cout<<"               `Y8bood8P'   `Y888\"\"8o o888o o888o o888o `Y8bod8P'            "<<endl;
	cout<<"                                                                             "<<endl;
	cout<<"                    .oooooo.                                                 "<<endl;
	cout<<"                   d8P'  `Y8b                                                "<<endl;
	cout<<"                  888      888 oooo    ooo  .ooooo.  oooo d8b                "<<endl;
	cout<<"                  888      888  `88.  .8'  d88' `88b `888\"\"8P              "<<endl;
	cout<<"                  888      888   `88..8'   888ooo888  888                    "<<endl;
	cout<<"                  `88b    d88'    `888'    888    .o  888                    "<<endl;
	cout<<"                   `Y8bood8P'      `8'     `Y8bod8P' d888b                   "<<endl;
	cout<<"                                                                             "<<endl<<endl;
	c.setTextColor(c.BRANCO);
	c.gotoxy(24,50);
	system("pause");
}

void printVictory(Consola& c)
{
	c.clrscr();
	c.gotoxy(0,30);
	c.setTextColor(c.AMARELO);
	c.setBackgroundColor(c.PRETO);
	cout<<"                                                                                "<<endl;
	cout<<"                                   $$$$$$$$$$$$                                 "<<endl;
	cout<<"                                 $$            $$                               "<<endl;
	cout<<"                  $$$$$        $$                $$                             "<<endl;
	cout<<"                 $     $     $$       $$    $$     $$                           "<<endl;
	cout<<"                  $     $    $$       $$    $$      $$                          "<<endl;
	cout<<"                   $    $   $$        $$    $$      $$                          "<<endl;
	cout<<"                    $   $   $                         $$                        "<<endl;
	cout<<"                 $$$$$$$$$$$$                         $$                        "<<endl;
	cout<<"                 $            $   $$            $$    $$                        "<<endl;
	cout<<"                $$            $   $$            $$    $$                        "<<endl;
	cout<<"               $$   $$$$$$$$$$$     $$        $$     $$                         "<<endl;
	cout<<"               $               $      $$$$$$$       $$                          "<<endl;
	cout<<"               $$              $                    $$                          "<<endl;
	cout<<"                $   $$$$$$$$$$$$                   $$                           "<<endl;
	cout<<"                $$           $  $$               $$                             "<<endl;
	cout<<"                 $$$$$$$$$$$$     $$            $$                              "<<endl;
	cout<<"                                    $$$$$$$$$$$                                 "<<endl;
	cout<<"                                                                                "<<endl;
	c.setTextColor(c.VERMELHO);
	cout<<"                                    VICTORY!!                                   "<<endl;

	c.setTextColor(c.BRANCO);
	c.gotoxy(25,51);
	system("pause");
}

void Scroll(Consola& con,Jogo& jogo)	// Scrolls the visible map using the arrow keys
{
	char c;

	do
	{
		c=con.getch();

		int colunas=jogo.GetColunas();	// Gets the total number of columns
		int linhas=jogo.GetLinhas();	// Gets the total number of lines

		if(c==con.ESQUERDA)	// If the map is scrolled to the left (x coordinates affected)
		{
			con.gotoxy(3,75);
			cout<<"A mover para a esquerda...           "<<endl;

			if(charx!=0)							// Avoids the map to be redrawn if it is already in the left limit
			{
				if(charx<=81)						// If the distance between the origin and x is less than 80
					charx=0;						// Puts the x coordinate to zero
				else
					charx=charx-81;					// Decrements the max value

				jogo.DesenhaMapa(con,charx,chary);	// Asks for the map to be redrawn
			}
			else
			{
				con.gotoxy(3,75);
				cout<<"Limite esquerdo atingido...                "<<endl;	// Warns when the limit is reached
			}
		}

		if(c==con.DIREITA)	// If the map is scrolled to the right (x coordinates affected)
		{
			con.gotoxy(3,75);
			cout<<"A mover para a direita...             "<<endl;
			
			if((charx+81)!=colunas)						// Avoids the map to be redrawn if it is already in the left limit
			{
				if(colunas>81)							// Means the real map is bigger than the visualized
					if((colunas-81)<81)					// If the diference between the total columns and the visualized ones are less than 80
						charx=colunas-81;				// Saves the jumping coordinate
					else if((colunas-(charx+81))>81)	// If the whole map is at least the double of the visualized, verifying the proximity of the right border
						charx=charx+81;					// Max increment if the right border is not in the vicinity
					else
						charx=colunas-81;				// If the right border is in the neighbourhood it adjusts the current coordinates

					jogo.DesenhaMapa(con,charx,chary);	// Asks for the map to be redrawn
			}
			else
			{
				con.gotoxy(3,75);
				cout<<"Limite direito atingido...             "<<endl;	// Warns when the limit is reached
			}
		}

		if(c==con.CIMA)	// If the map is scrolled up (y coordinates affected)
		{
			con.gotoxy(3,75);
			cout<<"A mover para cima...                  "<<endl;

			if(chary!=0)							// Avoids the map to be redrawn if it is already in the top limit
			{
				if(chary<=45)						// If the distance between the origin and y is less than 40
					chary=0;						// Puts the y coordinate to zero
				else
					chary=chary-45;					// Decrements the max value

				jogo.DesenhaMapa(con,charx,chary);	// Asks for the map to be redrawn
			}
			else
			{
				con.gotoxy(3,75);
				cout<<"Limite superior atingido...             "<<endl;	// Warns when the limit is reached
			}
		}

		if(c==con.BAIXO)	// If the map is scrolled down (y coordinates affected)
		{
			con.gotoxy(3,75);
			cout<<"A mover para baixo...                 "<<endl;

			if((chary+45)!=linhas)						// Avoids the map to be redrawn if it is already in the bottom limit
			{
				if(linhas>45)							// Means the real map is bigger than the visualized
					if((linhas-45)<45)					// If the diference between the total lines and the visualized ones are less than 40
						chary=linhas-45;				// Saves the jumping coordinate
					else if((linhas-(chary+45))>45)		// If the whole map is at least the double of the visualized, verifying the proximity of the bottom border
						chary=chary+45;					// Max increment if the bottom border is not in the vicinity
					else
						chary=linhas-45;				// If the bottom border is in the neighbourhood it adjusts the current coordinates

					jogo.DesenhaMapa(con,charx,chary);	// Asks for the map to be redrawn
			}
			else
			{
				con.gotoxy(3,75);
				cout<<"Limite inferior atingido...                "<<endl;	// Warns when the limit is reached
			}
		}
	}
	while(c!='c');

	con.gotoxy(3,75);
	cout<<"Modo Comandos                                  "<<endl;
}