#pragma once

#ifndef _BALA_
#define _BALA_

#include <iostream>
#include "Draw.h"
#include "Vector2.h"

using namespace std;

class Bala : public draw
{
public:	Bala(Vector2, Vector2, float);
		void Render();
		void Update(float);
		void limite();
		void rotate(float num)	 { Angulo = num; };
		void Trasladar(Vector2 position);
		int	 m_lifeTime;

private: Vector2 PositionBala;
		 float Angulo;
		 float AnguloRadianes;
		 float Masa;
		 float Radio;
};
#endif // !_BALA_
