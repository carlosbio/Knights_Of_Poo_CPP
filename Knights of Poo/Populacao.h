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

#ifndef POPULACAO_H
#define POPULACAO_H

#include "Blocos.h"
#include "Consola.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define EDIFS 4
#define UNIDS 5

class Populacao
{
	std::string nome;	// Populacao name

public:

	std::vector<Edificio*> edif[EDIFS];		// Array of pointers to Edificio objects (buildings)
	std::vector<Unidade*> unid[UNIDS];		// Array of pointers to Unidade objects (units)

	Populacao(std::string n="default"):nome(n){}	// Populacao constructor

	void SetNome(std::string n){nome=n;}		// Sets the population name
	std::string GetNome()const{return nome;}	// Gets the population name

	int AddEdificio(std::string e,int x,int y,Fog** b,int po,int lin,int col);		// Adds a building to the Population
	int AddUnidade(std::string u,int x,int y,Fog** b,int po,int lin,int col);		// Adds an unit to the Population

	~Populacao(){}	// Populacao destructor
};

#endif