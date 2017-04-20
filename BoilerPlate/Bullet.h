#pragma once

#ifndef _BULLET_
#define _BULLET_

#include <iostream>
#include "Draw.h"
#include "Vector2.h"

using namespace std;

class Bullet : public draw
{
public:	Bullet(Vector2, Vector2, float);
		void Render();
		void Update(float);
		void limite();
		void rotate(float num) { Angulo = num; };
		void Trasladar(Vector2 position);
		int	 m_lifeTime;

private: Vector2 PositionBala;
		 float Angulo;
		 float AnguloRadianes;
		 float Masa;
		 float Radio;
};
#endif // !_BULLET_
