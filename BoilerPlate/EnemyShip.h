#pragma once

#ifndef _ENEMYSHIP_
#define _ENEMYSHIP_

#include <iostream>
#include <vector>
#include "Vector2.h"
#include "Draw.h"
#include "Bala.h"
#include "ship.h"

using namespace std;

class EnemyShip : public draw
{
public: EnemyShip();
		~EnemyShip();
		void Draw();
		void Update(float deltatime, Vector2 Position);
		void Trasladar(Vector2 newPos);
		void limite();
		void Disparar(Vector2 Position);
		void EliminarBala(Bala* bala);
		void setPoint();
		vector<Bala*> Balas;

private: vector<Vector2> initShip;
		 vector<Vector2> initShip2;
		 Vector2 PositionEnemy;
		 vector<Vector2> Circulo;
		 float Radio;
		 float IncreX;
		 int Time;
		 int Time2;
		 float Angulo;
		 bool PermitirDisparar;
};




#endif // !_ENEMYSHIP_
