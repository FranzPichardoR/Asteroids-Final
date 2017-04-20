#include "AlienShip.h"
#include <SDL2/SDL_opengl.h>
#include "Draw.h"
#include <cmath>
#include <algorithm>

#define PI 3.141592653

const float Max_Speed = 10.0f;
const float Fuerza = 1.25f;

AlienShip::AlienShip()
	: PositionEnemy(Vector2(400, 0))
	, IncreX(-565.0f)
	, Radio(15.0f)
	, Time(0)
	, Time2(0)
	, Angulo(0)
	, PermitirDisparar(true)
{
	initShip2.push_back(Vector2(-7, 0));
	initShip2.push_back(Vector2(-7, 11));
	initShip2.push_back(Vector2(-5, 13));
	initShip2.push_back(Vector2(-3, 14));
	initShip2.push_back(Vector2(0, 15));
	initShip2.push_back(Vector2(3, 14));
	initShip2.push_back(Vector2(5, 12));
	initShip2.push_back(Vector2(6, 11));
	initShip2.push_back(Vector2(6, 0));
	initShip2.push_back(Vector2(0, -2));
	initShip2.push_back(Vector2(-7, 0));

	initShip.push_back(Vector2(0, -8));
	initShip.push_back(Vector2(8, -7));
	initShip.push_back(Vector2(10, -6));
	initShip.push_back(Vector2(15, -1));
	initShip.push_back(Vector2(16, 0));
	initShip.push_back(Vector2(13, 4));
	initShip.push_back(Vector2(9, 7));
	initShip.push_back(Vector2(6, 8));
	initShip.push_back(Vector2(0, 8));
	initShip.push_back(Vector2(-6, 8));
	initShip.push_back(Vector2(-9, 7));
	initShip.push_back(Vector2(-12, 5));
	initShip.push_back(Vector2(-13, 4));
	initShip.push_back(Vector2(-15, 2));
	initShip.push_back(Vector2(-16, 0));
	initShip.push_back(Vector2(-13, -4));
	initShip.push_back(Vector2(-8, -7));
	initShip.push_back(Vector2(-6, -8));
	initShip.push_back(Vector2(0, -8));

	setPoint();
	setRadioAl(Radio);
}

AlienShip::~AlienShip()
{
	for (int x = 0; x < Balas.size(); x++)
	{
		EliminarBala(Balas[x]);
	}
	PermitirDisparar = false;
}

void AlienShip::Draw()
{
	glLoadIdentity();

	limite();

	glTranslatef(PositionEnemy.GetX(), PositionEnemy.GetY(), 0.0f);

	glRotatef(Angulo, 0.0f, 0.0f, 1.0f);

	DrawT(GL_LINE_LOOP, initShip);
	DrawT(GL_LINE_LOOP, initShip2);

	for (int i = 0; i < Balas.size(); i++)
		Balas[i]->Render();
}

void AlienShip::Update(float deltatime, Vector2 Position)
{
	float y = IncreX * (PI / 180);

	if (Time == 350)
	{
		if (Time2 == 0 && PermitirDisparar == true)
			Disparar(Position);

		if (Time2 == 50)
		{
			Time = 0;
			Time2 = 0;
		}
		else
			Time2++;
	}
	else
	{
		Time++;
		PositionEnemy = Vector2(IncreX, 300 * sinf(y));
		IncreX += 0.500f;
		if (300 * sinf(y) >= 0)
		{
			Angulo -= 0.11f;
		}
		else if (300 * sinf(y) < 0)
		{
			Angulo += 0.11f;
		}
		setPosAl(PositionEnemy);
	}

	for (int i = 0; i < Balas.size(); i++)
	{
		Balas[i]->Update(deltatime);
		if (Balas[i]->m_lifeTime >= 150)
		{
			EliminarBala(Balas[i]);
			break;
		}
	}
}

void AlienShip::limite()
{
	if (PositionEnemy.GetX() > 570)
	{
		Vector2 newPos = Vector2(PositionEnemy.GetX() * -1, PositionEnemy.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionEnemy.GetX() < -570)
	{
		Vector2 newPos = Vector2(PositionEnemy.GetX() * -1, PositionEnemy.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionEnemy.GetY() > 320)
	{
		Vector2 newPos = Vector2(PositionEnemy.GetX() * -1, PositionEnemy.GetY() * -1);
		Trasladar(newPos);
	}
	else if (PositionEnemy.GetY() < -320)
	{
		Vector2 newPos = Vector2(PositionEnemy.GetX() * -1, PositionEnemy.GetY() * -1);
		Trasladar(newPos);
	}
}

void AlienShip::Trasladar(Vector2 newPos)
{
	PositionEnemy = static_cast<Vector2> (newPos);
	IncreX = -570;
	setPosAl(PositionEnemy);
}

void AlienShip::Disparar(Vector2 Position)
{
	float valor = (PositionEnemy.GetY() - Position.GetY()) / (PositionEnemy.GetX() - Position.GetX());
	float anguloA = atan(valor) * (180 / PI);

	if (PositionEnemy.GetX() < 0 || PositionEnemy.GetX() < 0 && Position.GetX() >= 0 || PositionEnemy.GetX() >= 0 && Position.GetX() >= 0)
		anguloA = anguloA + 270.0f;
	else if (PositionEnemy.GetX() >= 0 || PositionEnemy.GetX() >= 0 && Position.GetX() < 0 || PositionEnemy.GetX() < 0 && Position.GetX() < 0)
		anguloA = anguloA + 90.0f;

	Bullet* nBullet = new Bullet(PositionEnemy, Vector2(30, 30), anguloA);
	Balas.push_back(nBullet);
}

void AlienShip::EliminarBala(Bullet* bala)
{
	Balas.erase(remove(Balas.begin(), Balas.end(), bala), Balas.end());
	delete bala;
}


void AlienShip::setPoint()
{
	for (int point = 0; point < 16; ++point)
	{
		float valor = static_cast<float> (2.0f * PI * (point / 16.0f));
		float x = Radio * cosf(valor);
		float y = Radio * sinf(valor);
		Circulo.push_back(Vector2(x, y));
	}
}