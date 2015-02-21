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

#ifndef CONSOLA_H
#define CONSOLA_H

#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <iostream> 

class Consola
{
	HANDLE hconsola;
	HANDLE hStdin;
	HWND hwnd;

public:

	// para usar nas cores
	const static int PRETO          =  0;
	const static int AZUL           =  1;
	const static int VERDE          =  2;
	const static int CYAN           =  3;
	const static int VERMELHO       =  4;
	const static int ROXO           =  5;
	const static int AMARELO        =  6;
	const static int BRANCO         =  7;
	const static int CINZENTO       =  8;
	const static int AZUL_CLARO     =  9;
	const static int VERDE_CLARO    = 10;
	const static int CYAN_CLARO     = 11;
	const static int VERMELHO_CLARO = 12;
	const static int COR_DE_ROSA    = 13;
	const static int AMARELO_CLARO  = 14;
	const static int BRANCO_CLARO   = 15;

	// para usar em getch
	const static char ESQUERDA = 1;
	const static char DIREITA  = 2;
	const static char CIMA     = 3;
	const static char BAIXO    = 4;
	const static char ENTER    = 13;
	const static char ESCAPE   = 27;

	// para usar pra tabelas				// para ser usado como as restantes const static
	const static int CLEAN = 0;
	const static int TOP = 1;
	const static int MID = 2;
	const static int BOT = 3;
	const static int YDIV = 4;
	const static int XDIV = 5;

	Consola();
	void gotoxy(int x, int y);
	void clrscr();
	void setTextColor(WORD color);
	void setBackgroundColor(WORD color);
	void setScreenSize(int nLinhas, int nCols);
	void setTextSize(int x, int y);
	void setTextSizeXP(int x, int y);
	char getch (void);
	void drawLine(int x1,int y1,int x2,int y2,int cor);
	void drawCircle(int X,int Y,int R,int Pen,int Fill);
	void drawTab(int type, int length);						//novo metodo - serve para desenhar tabelas
	void drawSeparator(int x,int y,int height);				//novo metodo - serve para desenhar separadores
	void setCursor(bool b);									//novo metodo - serve para configurar cursor
};

#endif