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

#include "Territorio.h"

using namespace std;

Territorio::Territorio(int lin=27,int col=27):linhas(lin),colunas(col)
{
	b=new Fog*[linhas];

	for(int i=0;i<linhas;++i)
		b[i]=new Fog[colunas];
}