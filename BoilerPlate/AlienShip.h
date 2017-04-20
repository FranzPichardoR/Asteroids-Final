#pragma once

#ifndef _ALIENSHIP_
#define _ALIENSHIP_

#include <iostream>
#include <vector>
#include "Vector2.h"
#include "Draw.h"
#include "Bullet.h"
#include "ship.h"

using namespace std;

class AlienShip : public draw
{
public: AlienShip();
		~AlienShip();
		void Draw();
		void Update(float deltatime, Vector2 Position);
		void Trasladar(Vector2 newPos);
		void limite();
		void Disparar(Vector2 Position);
		void EliminarBala(Bullet* bala);
		void setPoint();
		vector<Bullet*> Balas;

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




#endif // !_ALIENSHIP_
