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

#ifndef BLOCOS_H
#define BLOCOS_H

#include "Consola.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Main class

class Bloco
{
protected:

	int x,y;	// Coordinates of the object

public:

	Bloco(int i=0,int j=0):x(i),y(j){}	// Base class construtor

	virtual int GetX()const{return x;}
	virtual int GetY()const{return y;}

	virtual void SetX(int i){x=i;}
	virtual void SetY(int i){y=i;}

	virtual ~Bloco(){}					// Base class virtual destructor

	virtual std::string Coords()const	// Returns info
	{
		std::ostringstream oss;
		oss<<x<<","<<y;
		return oss.str();
	}
};

// Bloco heirs

class Fog:public Bloco	// "Fog of War" - Invisible ground
{
protected:

	int p;
	
public:

	std::vector<Bloco*>sector;	// A vector of pointers in each Fog object

	Fog(int i=0,int j=0,int f=1):Bloco(i,j),p(f){}	// Bloco derived class Fog construtor

	int GetX()const{return x;}
	int GetY()const{return y;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}

	int GetP()const{return p;}
	void SetP(int i){p=i;}

	virtual ~Fog(){}	// Bloco derived class Fog virtual destructor

	std::string Coords()const	// Returns info
	{
		std::ostringstream oss;
		oss<<"Coordenadas do sector: "<<Bloco::x<<","<<Bloco::y;
		return oss.str();
	}
};

class Fonte:public Bloco
{
protected:

	int n,quant;
	char id;

public:

	Fonte(int i=0,int j=0,int num=0,int q=0,char c='F'):Bloco(i,j),n(num),quant(q),id(c){}	// Resource site constructor

	virtual int GetX()const{return x;}
	virtual int GetY()const{return y;}
	virtual int GetQuant(){return quant;}
	virtual int GetN(){return n;}
	virtual char GetId(){return id;}

	virtual void SetX(int i){x=i;}
	virtual void SetY(int i){y=i;}
	virtual void SetQuant(int i){quant=i;}
	virtual void SetN(int i){n=i;}
	virtual void SetId(char i){id=i;}

	virtual ~Fonte(){}
};

class Edificio:public Bloco
{
protected:

	int n,vida,pop;	// Id number, health and population
	char id;		// Id char (to use together with the id number)

public:

	Edificio(int i=0,int j=0,int num=1,int v=99,int po=0,char c='E'):Bloco(i,j),n(num),vida(v),pop(po),id(c){}	// Bloco derived class Edificio construtor

	virtual int GetVida(){return vida;}
	virtual int GetN(){return n;}
	virtual int GetPop(){return pop;}
	virtual char GetId(){return id;}

	virtual void SetVida(int i){vida=i;}
	virtual void SetN(int i){n=i;}
	virtual void SetPop(int i){pop=i;}
	virtual void SetId(char i){id=i;}

	virtual void SetOuro(int i){}
	virtual void SetPedra(int i){}
	virtual void SetMadeira(int i){}

	virtual int GetOuro()=0;
	virtual int GetPedra()=0;
	virtual int GetMadeira()=0;

	virtual ~Edificio(){}	// Bloco derived class Edificio virtual destructor
};

class Unidade:public Bloco
{
protected:

	int n,vida,pop,actual;		// Id number, health, population and actual state
	char id,tipocarga;			// Id char (to use together with the id number) and type of cargo
	int destlin,destcol,carga;	// Destination coordinates and cargo capacity
	Unidade* alvo;
	Edificio* destino;
	Fonte* recurso;

public:

	std::vector<int>tarefas;

	Unidade(int i=0,int j=0,int num=0,int v=0,int po=0,int ac=0,char c='U',char tc='T',int dl=0,int dc=0,int ca=0):Bloco(i,j),n(num),vida(v),pop(po),actual(ac),id(c),tipocarga(tc),destlin(dl),destcol(dc),carga(ca){}	// Bloco derived class Unidade construtor

	virtual int GetVida(){return vida;}
	virtual int GetN(){return n;}
	virtual int GetPop(){return pop;}
	virtual int GetDestlin(){return destlin;}
	virtual int GetDestcol(){return destcol;}
	virtual int GetActual(){return actual;}
	virtual int GetCarga(){return carga;}
	virtual char GetTipocarga(){return tipocarga;}
	virtual char GetId(){return id;}
	virtual int GetX()const{return x;}
	virtual int GetY()const{return y;}
	virtual Unidade* GetAlvo(){return alvo;}
	virtual Edificio* GetDestino(){return destino;}
	virtual Fonte* GetRecurso(){return recurso;}

	virtual void SetX(int i){x=i;}
	virtual void SetY(int i){y=i;}
	virtual void SetVida(int i){vida=i;}
	virtual void SetN(int i){n=i;}
	virtual void SetPop(int i){pop=i;}
	virtual void SetDestlin(int i){destlin=i;}
	virtual void SetDestcol(int i){destcol=i;}
	virtual void SetCarga(int i){carga=i;}
	virtual void SetTipocarga(char i){tipocarga=i;}
	virtual void SetActual(int i){actual=i;}
	virtual void SetId(char i){id=i;}
	virtual void SetAlvo(Unidade* i){alvo=i;}
	virtual void SetDestino(Edificio* i){destino=i;}
	virtual void SetRecurso(Fonte* i){recurso=i;}

	virtual int GetVel()=0;
	virtual int GetAtaque()=0;
	virtual int GetDef()=0;

	virtual ~Unidade(){}	// Bloco derived class Unidade virtual destructor
};

// Edificio heirs

class Castelo:public Edificio
{
	int ouro,pedra,madeira;

public:

	Castelo(int i=0,int j=0,int num=1,int v=99,int po=0,char c='C',int o=20,int p=20,int m=20):Edificio(i,j,num,v,po,c),ouro(o),pedra(p),madeira(m){}	// Edificio derived class Castelo construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	char GetId(){return id;}
	int GetOuro(){return ouro;}
	int GetPedra(){return pedra;}
	int GetMadeira(){return madeira;}

	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetOuro(int i){ouro=i;}
	void SetPedra(int i){pedra=i;}
	void SetMadeira(int i){madeira=i;}

	~Castelo(){}	// Castelo destructor
};

class Quartel:public Edificio	// Academy
{
	int ouro,pedra,madeira;

public:

	Quartel(int i=0,int j=0,int num=1,int v=99,int po=0,char c='A',int o=0,int p=0,int m=0):Edificio(i,j,num,v,po,c),ouro(o),pedra(p),madeira(m){}	// Academy construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	char GetId(){return id;}
	int GetOuro(){return ouro;}
	int GetPedra(){return pedra;}
	int GetMadeira(){return madeira;}

	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetOuro(int i){ouro=i;}
	void SetPedra(int i){pedra=i;}
	void SetMadeira(int i){madeira=i;}

	~Quartel(){}
};

class Estabulo:public Edificio	// Stable
{
	int ouro,pedra,madeira;

public:

	Estabulo(int i=0,int j=0,int num=1,int v=99,int po=0,char c='E',int o=0,int p=0,int m=0):Edificio(i,j,num,v,po,c),ouro(o),pedra(p),madeira(m){}	// Academy construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	char GetId(){return id;}
	int GetOuro(){return ouro;}
	int GetPedra(){return pedra;}
	int GetMadeira(){return madeira;}

	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetOuro(int i){ouro=i;}
	void SetPedra(int i){pedra=i;}
	void SetMadeira(int i){madeira=i;}

	~Estabulo(){}
};

class Quinta:public Edificio	// Farm
{
	int ouro,pedra,madeira;
		
public:

	Quinta(int i=0,int j=0,int num=1,int v=99,int po=0,char c='Q',int o=0,int p=0,int m=0):Edificio(i,j,num,v,po,c),ouro(o),pedra(p),madeira(m){}	// Academy construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	char GetId(){return id;}
	int GetOuro(){return ouro;}
	int GetPedra(){return pedra;}
	int GetMadeira(){return madeira;}

	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetOuro(int i){ouro=i;}
	void SetPedra(int i){pedra=i;}
	void SetMadeira(int i){madeira=i;}

	~Quinta(){}
};

// Unidade heirs

class Campones:public Unidade	// Peasant
{
	int vel,ataque,def;

public:

	Campones(int i=0,int j=0,int num=1,int v=20,int po=0,int ac=0,char c='P',char tc='T',int dl=0,int dc=0,int ca=3,int ve=1,int a=0,int d=0):Unidade(i,j,num,v,po,ac,c,tc,dl,dc,ca),vel(ve),ataque(a),def(d){}	// Unidade derived class Soldado construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	int GetDestlin(){return destlin;}
	int GetDestcol(){return destcol;}
	char GetId(){return id;}
	int GetVel(){return vel;}
	int GetDef(){return def;}
	int GetActual(){return actual;}
	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetAtaque(){return ataque;}
	int GetCarga(){return carga;}
	char GetTipocarga(){return tipocarga;}
	Unidade* GetAlvo(){return alvo;}
	Edificio* GetDestino(){return destino;}
	Fonte* GetRecurso(){return recurso;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetDestlin(int i){destlin=i;}
	void SetDestcol(int i){destcol=i;}
	void SetVel(int i){vel=i;}
	void SetDef(int i){def=i;}
	void SetActual(int i){actual=i;}
	void SetAtaque(int i){ataque=i;}
	void SetCarga(int i){carga=i;}
	void SetTipocarga(char i){tipocarga=i;}
	void SetAlvo(Unidade* i){alvo=i;}
	void SetDestino(Edificio* i){destino=i;}
	void SetRecurso(Fonte* i){recurso=i;}

	~Campones(){}	// Campones destructor
};

class Soldado:public Unidade	// Soldier
{
	int vel,ataque,def;

public:

	Soldado(int i=0,int j=0,int num=1,int v=40,int po=0,int ac=0,char c='S',char tc='T',int dl=0,int dc=0,int ca=0,int ve=2,int a=5,int d=20):Unidade(i,j,num,v,po,ac,c,tc,dl,dc,ca),vel(ve),ataque(a),def(d){}	// Soldado construtor

	//Soldado& operator=(const Soldado& c){Unidade::operator=(c);vel=c.vel;ataque=c.ataque;def=c.def;return *this;}	// Assignment operator

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	int GetDestlin(){return destlin;}
	int GetDestcol(){return destcol;}
	char GetId(){return id;}
	int GetVel(){return vel;}
	int GetAtaque(){return ataque;}
	int GetDef(){return def;}
	int GetActual(){return actual;}
	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetCarga(){return carga;}
	char GetTipocarga(){return tipocarga;}
	Unidade* GetAlvo(){return alvo;}
	Edificio* GetDestino(){return destino;}
	Fonte* GetRecurso(){return recurso;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetDestlin(int i){destlin=i;}
	void SetDestcol(int i){destcol=i;}
	void SetVel(int i){vel=i;}
	void SetAtaque(int i){ataque=i;}
	void SetDef(int i){def=i;}
	void SetActual(int i){actual=i;}
	void SetCarga(int i){carga=i;}
	void SetTipocarga(char i){tipocarga=i;}
	void SetAlvo(Unidade* i){alvo=i;}
	void SetDestino(Edificio* i){destino=i;}
	void SetRecurso(Fonte* i){recurso=i;}

	~Soldado(){}	// Soldado destructor
};

class Cavaleiro:public Unidade	// Knight
{
	int vel,ataque,def;

public:

	Cavaleiro(int i=0,int j=0,int num=1,int v=60,int po=0,int ac=0,char c='K',char tc='T',int dl=0,int dc=0,int ca=0,int ve=2,int a=8,int d=40):Unidade(i,j,num,v,po,ac,c,tc,dl,dc,ca),vel(ve),ataque(a),def(d){}	// Knight construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	int GetDestlin(){return destlin;}
	int GetDestcol(){return destcol;}
	char GetId(){return id;}
	int GetVel(){return vel;}
	int GetDef(){return def;}
	int GetActual(){return actual;}
	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetAtaque(){return ataque;}
	int GetCarga(){return carga;}
	char GetTipocarga(){return tipocarga;}
	Unidade* GetAlvo(){return alvo;}
	Edificio* GetDestino(){return destino;}
	Fonte* GetRecurso(){return recurso;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetDestlin(int i){destlin=i;}
	void SetDestcol(int i){destcol=i;}
	void SetVel(int i){vel=i;}
	void SetDef(int i){def=i;}
	void SetActual(int i){actual=i;}
	void SetAtaque(int i){ataque=i;}
	void SetCarga(int i){carga=i;}
	void SetTipocarga(char i){tipocarga=i;}
	void SetAlvo(Unidade* i){alvo=i;}
	void SetDestino(Edificio* i){destino=i;}
	void SetRecurso(Fonte* i){recurso=i;}

	~Cavaleiro(){}	// Knight destructor
};

class CampCav:public Unidade	// Riding Peasant
{
	int vel,ataque,def;

public:

	CampCav(int i=0,int j=0,int num=1,int v=40,int po=0,int ac=0,char c='B',char tc='T',int dl=0,int dc=0,int ca=5,int ve=1,int a=0,int d=0):Unidade(i,j,num,v,po,ac,c,tc,dl,dc,ca),vel(ve),ataque(a),def(d){}	// Riding Peasant construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	int GetDestlin(){return destlin;}
	int GetDestcol(){return destcol;}
	char GetId(){return id;}
	int GetVel(){return vel;}
	int GetDef(){return def;}
	int GetActual(){return actual;}
	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetAtaque(){return ataque;}
	int GetCarga(){return carga;}
	char GetTipocarga(){return tipocarga;}
	Unidade* GetAlvo(){return alvo;}
	Edificio* GetDestino(){return destino;}
	Fonte* GetRecurso(){return recurso;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetDestlin(int i){destlin=i;}
	void SetDestcol(int i){destcol=i;}
	void SetVel(int i){vel=i;}
	void SetDef(int i){def=i;}
	void SetActual(int i){actual=i;}
	void SetAtaque(int i){ataque=i;}
	void SetCarga(int i){carga=i;}
	void SetTipocarga(char i){tipocarga=i;}
	void SetAlvo(Unidade* i){alvo=i;}
	void SetDestino(Edificio* i){destino=i;}
	void SetRecurso(Fonte* i){recurso=i;}

	~CampCav(){}	// Riding Peasant destructor
};

class Orc:public Unidade	// Orc
{
	int vel,ataque,def;

public:

	Orc(int i=0,int j=0,int num=1,int v=30,int po=0,int ac=0,char c='O',char tc='T',int dl=0,int dc=0,int ca=0,int ve=3,int a=10,int d=20):Unidade(i,j,num,v,po,ac,c,tc,dl,dc,ca),vel(ve),ataque(a),def(d){}	// Orc construtor

	int GetVida(){return vida;}
	int GetN(){return n;}
	int GetPop(){return pop;}
	int GetDestlin(){return destlin;}
	int GetDestcol(){return destcol;}
	char GetId(){return id;}
	int GetVel(){return vel;}
	int GetDef(){return def;}
	int GetActual(){return actual;}
	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetAtaque(){return ataque;}
	int GetCarga(){return carga;}
	char GetTipocarga(){return tipocarga;}
	Unidade* GetAlvo(){return alvo;}
	Edificio* GetDestino(){return destino;}
	Fonte* GetRecurso(){return recurso;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetVida(int i){vida=i;}
	void SetN(int i){n=i;}
	void SetPop(int i){pop=i;}
	void SetId(char i){id=i;}
	void SetDestlin(int i){destlin=i;}
	void SetDestcol(int i){destcol=i;}
	void SetVel(int i){vel=i;}
	void SetDef(int i){def=i;}
	void SetActual(int i){actual=i;}
	void SetAtaque(int i){ataque=i;}
	void SetCarga(int i){carga=i;}
	void SetTipocarga(char i){tipocarga=i;}
	void SetAlvo(Unidade* i){alvo=i;}
	void SetDestino(Edificio* i){destino=i;}
	void SetRecurso(Fonte* i){recurso=i;}

	~Orc(){}	// Orc destructor
};

// Fonte heirs

class Mina:public Fonte	// Mine
{

public:

	Mina(int i=0,int j=0,int num=1,int q=99,char c='M'):Fonte(i,j,num,q,c){}	// Mine site constructor

	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetQuant(){return quant;}
	int GetN(){return n;}
	char GetId(){return id;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetQuant(int i){quant=i;}
	void SetN(int i){n=i;}
	void SetId(char i){id=i;}

	~Mina(){}
};

class Pedreira:public Fonte	// Quarry
{

public:

	Pedreira(int i=0,int j=0,int num=1,int q=99,char c='R'):Fonte(i,j,num,q,c){}	// Quarry site constructor

	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetQuant(){return quant;}
	int GetN(){return n;}
	char GetId(){return id;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetQuant(int i){quant=i;}
	void SetN(int i){n=i;}
	void SetId(char i){id=i;}

	~Pedreira(){}
};

class Floresta:public Fonte	// Forest
{

public:

	Floresta(int i=0,int j=0,int num=1,int q=20,char c='F'):Fonte(i,j,num,q,c){}	// Forest site constructor

	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetQuant(){return quant;}
	int GetN(){return n;}
	char GetId(){return id;}

	void SetX(int i){x=i;}
	void SetY(int i){y=i;}
	void SetQuant(int i){quant=i;}
	void SetN(int i){n=i;}
	void SetId(char i){id=i;}

	~Floresta(){}
};

#endif