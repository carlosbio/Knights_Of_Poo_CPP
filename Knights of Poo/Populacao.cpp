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

#include "Populacao.h"

using namespace std;

int Populacao::AddEdificio(string e,int x,int y,Fog** b,int po,int lin,int col)	// Adds a building to the population
{
	static int quin;	// Static farms counter

	if(b[x][y].sector.size()!=0)	// The sector is occupied, so it's not allowed to place a new building in it
		return 3;

	if(e=="cas")	// If it is a castle
	{
		if(edif[0].size()==0)	// If the vector is empty
		{
			edif[0].push_back(new Castelo(x,y));	// Adds a new castle to the vector

			edif[0][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(edif[0][0]);	// Adds the castle to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-12;i<15;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-12;j<15;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
			return 2;	// Does not allow the construction of more than one castle
	}
	else if(e=="quar")	// If it is an academy
	{
		if(edif[1].size()==0)	// If the vector is empty
		{
			edif[1].push_back(new Quartel(x,y));	// Adds a new castle to the vector

			edif[1][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(edif[1][0]);	// Adds the academy to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-12;i<15;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-12;j<15;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
			return 2;	// Does not allow the construction of more than one academy
	}
	else if(e=="est")	// If it is a stable
	{
		if(edif[2].size()==0)	// If the vector is empty
		{
			edif[2].push_back(new Estabulo(x,y));	// Adds a new stable to the vector

			edif[2][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(edif[2][0]);	// Adds the stable to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-12;i<15;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-12;j<15;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
			return 2;	// Does not allow the construction of more than one stable
	}
	else if(e=="quin")	// If it is a farm
	{
		if(edif[3].size()==0)	// If the vector is empty
		{
			quin=1;

			edif[3].push_back(new Quinta(x,y));	// Adds a new farm to the vector

			edif[3][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(edif[3][0]);	// Adds the farm to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-12;i<15;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-12;j<15;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
		{
			quin++;	// Increments the farm counter

			edif[3].push_back(new Quinta(x,y,quin));	// Adds one farm to the vector

			edif[3][quin-1]->SetPop(po);				// Adds the population info

			b[x][y].sector.push_back(edif[3][quin-1]);	// Adds the farm to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-12;i<15;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-12;j<15;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
	}
	else
		return 0;

	return 1;	// Success
}

int Populacao::AddUnidade(string u,int x,int y,Fog** b,int po,int lin,int col)		// Adds an unit to the population
{
	static int sold,camp,campcav;

	if(u=="sold")	// If it is a Soldier
	{
		if(unid[0].size()==0)	// If the vector is empty
		{
			sold=1;	// Initializes the soldiers counter

			unid[0].push_back(new Soldado(x,y));	// Adds one soldier to the vector

			unid[0][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(unid[0][0]);	// Adds the soldier to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
		{
			sold++;	// Increments the soldier counter

			unid[0].push_back(new Soldado(x,y,sold));	// Adds one soldier to the vector

			unid[0][sold-1]->SetPop(po);				// Adds the population info

			b[x][y].sector.push_back(unid[0][sold-1]);	// Adds the soldier to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
	}
	else if(u=="camp")	// If it is a Peasant
	{
		if(unid[1].size()==0)	// If the vector is empty
		{
			camp=1;	// Initializes the peasants counter

			unid[1].push_back(new Campones(x,y));	// Adds one peasant to the vector

			unid[1][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(unid[1][0]);	// Adds the peasant to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
		{
			camp++;	// Increments the peasant counter

			unid[1].push_back(new Campones(x,y,camp));	// Adds one peasant to the vector

			unid[1][camp-1]->SetPop(po);				// Adds the population info

			b[x][y].sector.push_back(unid[1][camp-1]);	// Adds the peasant to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
	}
	else if(u=="cav")	// If it is a Knight
	{
		if(unid[2].size()==0)	// If the vector is empty
		{
			unid[2].push_back(new Cavaleiro(x,y));	// Adds one knight to the vector

			unid[2][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(unid[2][0]);	// Adds the knight to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
			return 2;	// Does not allow the construction of more than one knight
	}
	else if(u=="cv")	// If it is a Riding Peasant
	{
		if(unid[3].size()==0)	// If the vector is empty
		{
			campcav=1;	// Initializes the riding peasants counter

			unid[3].push_back(new CampCav(x,y));	// Adds one riding peasant to the vector

			unid[3][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(unid[3][0]);	// Adds the riding peasant to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
		{
			campcav++;	// Increments the riding peasant counter

			unid[3].push_back(new CampCav(x,y,campcav));	// Adds one riding peasant to the vector

			unid[3][campcav-1]->SetPop(po);				// Adds the population info

			b[x][y].sector.push_back(unid[3][campcav-1]);	// Adds the riding peasant to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
	}
	else if(u=="orc")	// If it is an Orc
	{
		if(unid[4].size()==0)	// If the vector is empty
		{
			unid[4].push_back(new Orc(x,y));	// Adds one orc to the vector

			unid[4][0]->SetPop(po);					// Adds the population info

			b[x][y].sector.push_back(unid[4][0]);	// Adds the orc to the position vector

			if(po==0)	// If it is the first population (player)
			{
				for(int i=-6;i<9;i++)	// Deactivates the "fog of war" flag in the coordinates where the castle will be placed
					for(int j=-6;j<9;j++)
						if(x+i>=0&&y+j>=0&&x+i<lin&&y+j<col)	// Validates the map limits
						{
							if(i>=0&&i<3&&j>=0&&j<3)
								b[x+i][y+j].SetP(0);
							else if(b[x+i][y+j].GetP()==1)		// If the sector is flagged as fog of war
								b[x+i][y+j].SetP(2);			// Flags as clear sector
							else if(b[x+i][y+j].GetP()==3)		// If the sector is flagged as enemy unit or resource
								b[x+i][y+j].SetP(0);			// Flags as occupied sector
						}
			}
			else
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						b[x+i][y+j].SetP(3);	// Sets the ground flag to 3 (enemy unit)
			}
		}
		else
			return 2;	// Does not allow the construction of more than one orc
	}
	else
		return 0;

	return 1;	// Success
}