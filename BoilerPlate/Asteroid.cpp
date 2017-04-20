#include "Asteroid.h"
#include <SDL2/SDL_opengl.h>
#include <cmath>
#define PI 3.141592653f

const float Drag = 1.0f;
const float Fuerza = 1.25f;
const Vector2 null = Vector2(0, 0);
const float Min = 25.0f;
const float Max = 45.0f;

Asteroid::Asteroid(Vector2 pos, int size)
	: RadioAst(40.0f)
	, Angulo(0)
{
	setMasa();
	PositionAst = pos;
	AnguloRadian = (Angulo + 90.0f) * (PI / 180);

	if (size == 0)
		Size = size;
	if (size == 1)
		Size = size;
	if (size == 2)
		Size = size;

	GenerarCirculo();
	setRadioAl(RadioAst);
	setPoint();
}

Asteroid::Asteroid()
	: RadioAst(40.0f)
	, Angulo(0)
{
	setMasa();
	Size = 0;
	GenerarCirculo();
	PositionAst = PosAL();
	AnguloRadian = (Angulo + 90.0f) * (PI / 180);
	setRadioAl(RadioAst);
	setPoint();
}

Asteroid::~Asteroid()
{}

void Asteroid::DrawAst()
{
	glLoadIdentity();

	limite();

	glTranslatef(PositionAst.GetX(), PositionAst.GetY(), 0.0f);

	glRotated(Angulo, 0.0f, 0.0f, 1.0f);

	DrawT(GL_LINE_LOOP, Point);
}

void Asteroid::Mover(float deltaTime)
{
	Vector2 newPos;
	if (Masa > 0)
	{
		float Impulso = Fuerza / Masa;
		float x = Impulso * cosf(AnguloRadian);
		float y = Impulso * sinf(AnguloRadian);
		newPos += Vector2(x, y);
	}
	newPos += PositionAst;

	Angulo += 1.0f;

	Trasladar(newPos);

}

void Asteroid::Dividir(int cantidad, int size, Vector2 position)
{
	if (position == null)
	{
		for (int i = 0; i < cantidad; i++)
		{
			Asteroid* nEnemy = new Asteroid();
			nEnemy->DrawAst();
		}
		return;
	}

	else
	{
		for (int i = 0; i < cantidad; i++)
		{
			Asteroid* nEnemy = new Asteroid(position, size);
			nEnemy->DrawAst();
		}
	}
}

void Asteroid::limite()
{
	if (PositionAst.GetX() > 570)
	{
		Vector2 newPos = Vector2(PositionAst.GetX() * -1, PositionAst.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionAst.GetX() < -570)
	{
		Vector2 newPos = Vector2(PositionAst.GetX() * -1, PositionAst.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionAst.GetY() > 320)
	{
		Vector2 newPos = Vector2(PositionAst.GetX() * -1, PositionAst.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionAst.GetY() < -320)
	{
		Vector2 newPos = Vector2(PositionAst.GetX() * -1, PositionAst.GetY() * -1);
		Trasladar(newPos);
	}
}

void Asteroid::Trasladar(Vector2 newPos)
{
	PositionAst = static_cast<Vector2> (newPos);
	setPosAl(PositionAst);
}

void Asteroid::GenerarCirculo()
{
	int min = static_cast<int> (Min / (Size + 1));
	int max = static_cast<int> (Max / (Size + 1));

	if (Size == 0) RadioAst = RadioAst;
	if (Size == 1) RadioAst = RadioAst - 20;
	if (Size == 2) RadioAst = RadioAst - 30;
	setRadioAl(RadioAst);

	for (int point = 0; point < 16; ++point)
	{
		const float valor = static_cast<float> (2.0f * PI * (point / 16.0f));
		const float Aleatorio = static_cast<float> (min + (max - min) * (rand() / static_cast<float> (RAND_MAX)));
		Point.push_back(Vector2(sinf(valor) * Aleatorio, cosf(valor) * Aleatorio));
	}
}

void Asteroid::setMasa()
{
	Masa = Fuerza / 3.0f;
}

int Asteroid::getSize()
{
	return Size;
}

void Asteroid::setPoint()
{
	for (int point = 0; point < 16; ++point)
	{
		float valor = static_cast<float> (2.0f * PI * (point / 16.0f));
		float x = RadioAst * cosf(valor);
		float y = RadioAst * sinf(valor);
		Circulo.push_back(Vector2(x, y));
	}
}