#pragma once

#ifndef _DRAW_
#define _DRAW_

#include <vector>
#include "Vector2.h"
#include <iostream>

using namespace std;

class draw
{
public: draw();
		void DrawT(unsigned int mode, vector<Vector2> point);
		void DrawSquare(unsigned int mode, const Vector2 Mn, const Vector2 Mx, const Vector2 Pos);
		Vector2 PosAL() const;
		bool Colliding(draw rhs);
		bool CollidingSquare(draw rhs);
		virtual void setPosAl(Vector2 pos) { PosAl = pos; }
		virtual void setRadioAl(float ra) { radioAl = ra; }
		void setMin(const float Radio);
		void setMax(const float Radio);
		Vector2 GenerarMin(const Vector2 Posicion, float Radio);
		Vector2 GenerarMax(const Vector2 Posicion, float Radio);

private:   Vector2 PosAl;
		   Vector2 Minimo;
		   Vector2 Maximo;
		   float radioAl;

};


#endif // !_DRAW_
