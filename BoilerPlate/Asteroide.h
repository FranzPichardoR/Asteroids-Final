#pragma once

#ifndef _ASTEROIDE_
#define _ASTEROIDE_

#include <iostream>
#include "Vector2.h"
#include <vector>
#include <time.h>
#include "Draw.h"
#include <random>

using namespace std;

class Asteroide : public draw
{
public: Asteroide(Vector2 pos, int size);
		Asteroide();
		~Asteroide();
		void DrawAst();
		void Mover(float deltaTime);
		void Trasladar(Vector2 newPos);
		void limite();
		void GenerarCirculo();
		void Dividir(int Cantidad, int size, Vector2 position);
		void setMasa();
		int getSize();
		void setPoint();

private: float Angulo;
		 vector<Vector2> Point;
		 vector<Vector2> Circulo;
		 float RadioAst;
		 float Masa;
		 float AnguloRadian;
		 int Size;
		 Vector2 PositionAst;
		 Vector2 Mn;
		 Vector2 Mx;
};




#endif // !_ASTEROIDE_
