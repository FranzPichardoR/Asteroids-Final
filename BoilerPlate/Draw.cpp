#include "Draw.h"
#include <SDL2/SDL_opengl.h>

draw::draw()
{ }

void draw::DrawT(unsigned int mode, vector<Vector2> Point)
{

	glBegin(mode);
	for (auto point : Point)
	{
		glVertex2f(point.GetX(), point.GetY());
	}
	glEnd();

}

void draw::DrawSquare(unsigned int mode, Vector2 Mn, Vector2 Mx, Vector2 Pos)
{
	glLoadIdentity();

	glTranslatef(Pos.GetX(), Pos.GetY(), 0.0f);

	glBegin(mode);

	glVertex2i(Mn.GetX(), Mn.GetY());
	glVertex2i(Mn.GetX(), Mx.GetY());
	glVertex2i(Mx.GetX(), Mx.GetY());
	glVertex2i(Mx.GetX(), Mn.GetY());

	glEnd();
}

Vector2 draw::PosAL() const
{
	Vector2 PosAleatoria;
	float x = static_cast<float> (-400 + (400 + 400) * (rand() / static_cast<float> (RAND_MAX)));
	float y = static_cast<float> (-400 + (400 + 400) * (rand() / static_cast<float> (RAND_MAX)));
	PosAleatoria = Vector2(x, y);
	return PosAleatoria;
}

bool draw::Colliding(draw rhs)
{
	float x = PosAl.GetX() - rhs.PosAl.GetX();
	float y = PosAl.GetY() - rhs.PosAl.GetY();

	float Distancia = x * x + y * y;

	float radio = radioAl + rhs.radioAl;
	return radio * radio >= Distancia;

}

bool draw::CollidingSquare(draw rhs)
{
	setMin(radioAl);
	setMax(radioAl);
	rhs.setMin(rhs.radioAl);
	rhs.setMax(rhs.radioAl);

	return (Minimo.GetX() <= rhs.Maximo.GetX() &&
		(Maximo.GetX() >= rhs.Minimo.GetX())) &&
		(Minimo.GetY() <= rhs.Maximo.GetY() &&
		(Maximo.GetY() >= rhs.Minimo.GetY()));
}

void draw::setMin(const float Radio)
{
	float x = PosAl.GetX() - Radio;
	float y = PosAl.GetY() - Radio;

	Minimo = Vector2(x, y);
}

void draw::setMax(const float Radio)
{
	float x = PosAl.GetX() + Radio;
	float y = PosAl.GetY() + Radio;

	Maximo = Vector2(x, y);
}

Vector2 draw::GenerarMin(Vector2 Posicion, float Radio)
{
	float x1 = PosAl.GetX() - Radio;
	float y1 = PosAl.GetY() - Radio;

	return Vector2(x1, y1);
}

Vector2 draw::GenerarMax(Vector2 Posision, float Radio)
{
	float x = PosAl.GetX() + Radio;
	float y = PosAl.GetY() + Radio;

	return Vector2(x, y);
}
