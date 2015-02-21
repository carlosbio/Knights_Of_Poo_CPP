// ------------------------------------------------------------------------------------------------------------	//
//																												//
// Descri��o e implementa��o de um programa em C++ que consiste num jogo de estrat�gia do tipo Warcraft			//
//																												//
// Unidade curricular de Programa��o Orientada a Objectos 2014/2015 do curso de Engenharia Inform�tica do ISEC	//
//																												//
// Trabalho realizado por Carlos da Silva (21220319)															//
//																												//
// Data: 07/12/2014																								//
//																												//
// ------------------------------------------------------------------------------------------------------------	//

#ifndef TERRITORIO_H
#define TERRITORIO_H

#include "Consola.h"
#include "Blocos.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Territorio
{
	int linhas,colunas;

public:

	Fog **b;	// Bidimensional array of objects of the class Fog

	Territorio(int lin,int col);

	int GetLinhas()const{return linhas;}
	int GetColunas()const{return colunas;}

	void SetLinhas(int i){linhas=i;}
	void SetColunas(int i){colunas=i;}

	Fog& GetBloco(){return **b;}
};

#endif