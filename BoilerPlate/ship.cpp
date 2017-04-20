#include "ship.h"
#include <SDL2/SDL_opengl.h>
#include <cmath>
#include <algorithm>

#define PI 3.141592653

const float AnguloAjuste = 90.0f;
const float Fuerza = 3.0f;
const float Drag = 0.979f;
const float Max_Speed = 10.0f;

ship::ship()
	: Velocity(0,0)
	, RadioShip(40.0f)
	, Position(Vector2(0,0))
{
	setRadioAl(RadioShip);
	setMasa();
	setPoint();
	UsoBala = 0;
}

ship::ship(const vector<Vector2> points)
{
	Point = points;
	Position = Vector2(0, 0);
	Angulo = 0;
	AnguloRadianes = (Angulo + AnguloAjuste) * (PI / 180);
	RadioShip = 40.0f;
	setRadioAl(RadioShip);
	setMasa();
	Time = 0;
	setPoint();
	UsoBala = 0;
}

void ship::Draw()
{
	glLoadIdentity();

	limite();

	glTranslatef(Position.GetX(),Position.GetY(), 0.0f);

	glRotatef(Angulo, 0.0f, 0.0f, 1.0f);

	if (!Inmune)
	{
		if (Time >= 100)
		{
			Inmune = true;
			Time = 0;
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		Time++;
	}

	DrawT(GL_LINE_LOOP, Point);
 	
	AnguloRadianes = (Angulo + AnguloAjuste) * (PI / 180);

	for (int i = 0; i < Balas.size(); i++)
		Balas[i]->Render();
}

void ship::Trasladar(Vector2 position)
{
	Position = position;
	setPosAl(Position);
}

void ship::MoveUp()
{
	if (Masa > 0)
	{
		Vector2 velocity = Vector2((Fuerza / Masa) * cosf(AnguloRadianes), (Fuerza / Masa) * sinf(AnguloRadianes));
		Velocity += velocity;
	}
}

void ship::MoveDown()
{
	if (Masa > 0)
	{
		Vector2 velocity = Vector2(-(Fuerza / Masa) * cosf(AnguloRadianes), -(Fuerza / Masa) * sinf(AnguloRadianes));
		Velocity += velocity;
	}
}

void ship::MoveRight()
{
	Angulo -= 10.0f;
	AnguloRadianes = (Angulo + AnguloAjuste) * (PI / 180);	
}

void ship::MoveLeft()
{
	Angulo += 10.0f;
	AnguloRadianes = (Angulo + AnguloAjuste) * (PI / 180);
}

void ship::limite()
{
	if (Position.GetX() > 600)
	{
		Vector2 newPos = Vector2(Position.GetX() * -1, Position.GetY() * -1);
		Trasladar(newPos);
	}
	else if (Position.GetX() < -600)
	{
		Vector2 newPos = Vector2(Position.GetX() * -1, Position.GetY() * -1);
		Trasladar(newPos);
	}
	else if (Position.GetY() > 350)
	{
		Vector2 newPos = Vector2(Position.GetX() * -1, Position.GetY() * -1);
		Trasladar(newPos);
	}
	else if (Position.GetY() < -350)
	{
		Vector2 newPos = Vector2(Position.GetX() * -1, Position.GetY() * -1);
		Trasladar(newPos);
	}
}

void ship::setMasa()
{
	for (auto count : Point)
	{
		Masa += 0.2f;
	}

	if (Masa < 2.0f)
		Masa = 1.5f;

	return;
}

void ship::setPoint()
{
	for (int point = 0; point < 16; ++point)
	{
		float valor = static_cast<float> (2.0f * PI * (point / 16.0f));
		float x = RadioShip * cosf(valor);
		float y = RadioShip * sinf(valor);
		Circulo.push_back(Vector2(x, y));
	}
}

Vector2 ship::getPosition()
{
	return Position;
}

void ship::Reiniciar()
{
	Position = Vector2(0.0f, 0.0f);
	Angulo = 0;
	AnguloRadianes = 0;
	Velocity = Vector2(0.0f, 0.0f);
	Inmune = false;

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	for (auto point : Point)
	{
		glVertex2f(point.GetX(), point.GetY());
	}
	glEnd();
}

void ship::Update(float deltatime)
{
	float speed = fabs(Velocity.getLengt());
	if (speed > Max_Speed)
	{
		Velocity = Vector2((Velocity.GetX() / speed) * Max_Speed, (Velocity.GetY() / speed) * Max_Speed);

		Speed = fabs(Velocity.getLengt());
	}

	Velocity = Vector2(Velocity.GetX() * Drag, Velocity.GetY() * Drag);

	Vector2 pos = Position + Velocity;
	Trasladar(pos);

	for (int i = 0; i < Balas.size(); i++)
	{
		Balas[i]->Update(deltatime);
		if (Balas[i]->m_lifeTime >= 240)
		{
			EliminarBala(Balas[i]);
			break;
		}
	}
}

void ship::Disparar()
{
	if (UsoBala == 20) return;
	else if (UsoBala < 20)
	{
		Bala* nBullet = new Bala(Position, Velocity, Angulo);
		Balas.push_back(nBullet);
		UsoBala++;
	}
}

void ship::EliminarBala(Bala* bala)
{
	Balas.erase(remove(Balas.begin(), Balas.end(), bala), Balas.end());
	delete bala;
	UsoBala--;
}

void ship::Vidas(int vidas, int index)
{
	if (index != 2)
	{
		int Suma = 380;
		for (int x = 0; x < vidas; x++)
		{
			glLoadIdentity();

			glBegin(GL_LINE_LOOP);
			for (auto point : Point)
			{
				glVertex2f(point.GetX() + Suma, point.GetY() + 275);
			}
			glEnd();
			Suma += 70;
		}
	}
	else
	{
		int Suma = 400;
		for (int x = 0; x < vidas; x++)
		{
			glLoadIdentity();

			glBegin(GL_LINE_LOOP);
			for (auto point : Point)
			{
				glVertex2f(point.GetX() + Suma, point.GetY() + 295);
			}
			glEnd();
			Suma += 50;
		}
	}
}