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

#ifndef JOGO_H
#define JOGO_H

#include "Consola.h"
#include "Territorio.h"
#include "Populacao.h"
#include "Blocos.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

class Jogo
{
	int linhas,colunas;
	Territorio t;

public:

	std::vector<Populacao*>p;	// Vector of pointers for each population object
	std::vector<Fonte*>f;		// Vector of pointers for each resource site object

	Jogo(int l=45,int c=81):linhas(l),colunas(c),t(linhas,colunas){}	// Default constructor

	int GetLinhas()const{return linhas;}
	int GetColunas()const{return colunas;}
	void SetLinhas(int i){linhas=i;}
	void SetColunas(int i){colunas=i;}

	~Jogo(){}	// Destructor

	void DesenhaMapa(Consola& con,int x,int y);					// Draws the map
	void DesenhaInfo(Consola& con);								// Draws the info bar
	void Mostra(Consola& con,int pop);							// Writes the info of a population
	void CentraSel(Consola& con,int& x,int& y,int lin,int col);	// Centers an object in the map when selected

	void Next();					// Iterate

	void Deambular(Unidade*s);		// Patrol
	void Consertar(Unidade* s);		// Repair
	void Construir(Unidade* s);		// Build
	void Mover(Unidade* s);			// Move
	void Atacar(Unidade* s);		// Attack
	void Demolir(Unidade* s);		// Demolish
	void Recolher(Unidade* s);		// Harvest
	void Depositar(Unidade* s);		// Deposit
	void Sector(Consola& con,int lin,int col);	// Shows the info in the selected sector

	int Deambula(std::string elem,std::string pop,int lin,int col);								// Sets the patrol order to an unit
	int Treina(int populacao,std::string e);													// Sets the training order to a building
	int Conserta(std::string elem,std::string pop,std::string elemalvo,std::string popalvo);	// Sets the repair order to an unit
	int Constroi(std::string elem,std::string pop,std::string e,int l,int c);					// Sets the construct order to an unit
	int Ataca(std::string elem,std::string pop,std::string elemalvo,std::string popalvo);		// Sets the attack order to an unit
	int Recolhe(std::string elem,std::string pop,std::string elemalvo);							// Sets the harvest order to an unit
	int Goto(std::string elem,std::string pop,int lin,int col);									// Sets the movement coordinates to an unit
	int Go(std::string elem,std::string pop,int lin,int col,int mlin,int mcol);					// Sets the movement coordinates to an unit
	int Selecciona(Consola& con,std::string elem,std::string pop,int& x,int& y);				// Selects an element
	int Stop(std::string elem,std::string pop);													// Cancels the unit's duties
	int CriaPop(std::string n);						// Creates a population
	int AddRecurso(std::string r,int x,int y);		// Adds a resource site to the territory

	Territorio& GetTerritorio(){return t;}
};

#endif