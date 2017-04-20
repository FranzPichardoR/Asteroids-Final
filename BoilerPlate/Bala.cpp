#include "Bala.h"
#include "SDL2\SDL_opengl.h"

const float AnguloAjuste = 90.0f;
const float PI = 3.1415926535897323846f;
const float Fuerza = 1.25f;

Bala::Bala(Vector2 pos, Vector2 v, float angle)
{
	Masa = 0.3f;
	Radio = 1.0f;
	setRadioAl(Radio);
	Angulo = angle;
	AnguloRadianes = (Angulo + AnguloAjuste) * (PI / 180);
	PositionBala = pos;
	setPosAl(PositionBala);
	m_lifeTime = 0;
};

void Bala::Render()
{
	m_lifeTime++;

	glLoadIdentity();

	limite();

	glTranslatef(PositionBala.GetX(), PositionBala.GetY(), 0.f);

	glLoadIdentity();
	
	glPointSize(2.0f);

	glEnable(GL_POINT_SMOOTH);

	glBegin(GL_POINTS);

	glVertex2f(PositionBala.GetX(),PositionBala.GetY());

	glEnd();
};

void Bala::Update(float fps)
{
	Vector2 current;
	if (Masa > 0)
	{
		float impulse = (Fuerza / Masa);
		float x = impulse * cosf(AnguloRadianes);
		float y = impulse * sinf(AnguloRadianes);

		current += Vector2(x, y);
	}

	current += PositionBala;
	Trasladar(current);
	return;
};

void Bala::limite()
{
	if (PositionBala.GetX() > 600)
	{
		Vector2 newPos = Vector2(PositionBala.GetX() * -1, PositionBala.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionBala.GetX() < -600)
	{
		Vector2 newPos = Vector2(PositionBala.GetX() * -1, PositionBala.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionBala.GetY() > 350)
	{
		Vector2 newPos = Vector2(PositionBala.GetX() * -1, PositionBala.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionBala.GetY() < -350)
	{
		Vector2 newPos = Vector2(PositionBala.GetX() * -1, PositionBala.GetY() * -1);
		Trasladar(newPos);
	}
}

void Bala::Trasladar(Vector2 position)
{
	PositionBala = position;
	setPosAl(PositionBala);
}