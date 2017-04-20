#include "App.hpp"
#include <iostream>
#include <algorithm>

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

namespace Engine
{
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
		, CantVidas(3)
		, Entro(false)
		, Time(0)
		, RespawnTime(0)
		, Score(0)
		, CantAsteroides(1)
	{
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
	}

	App::~App()
	{
		CleanupSDL();
	}

	void App::Execute()
	{
		if (m_state != GameState::INIT_SUCCESSFUL)
		{
			std::cerr << "Game INIT was not successful." << std::endl;
			return;
		}

		m_state = GameState::RUNNING;

		SDL_Event event;
		while (m_state == GameState::RUNNING)
		{
			// Input polling
			//
			while (SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}

			//
			Update();
			Render();
		}
	}

	bool App::Init()
	{
		// Init the external dependencies
		//
		bool success = SDLInit() && GlewInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		// Setup the viewport
		//
		SetupViewport();

		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;

		Load config;
		Ship = config.load();
		ShipVidas = config.load();
		Index = 0;
		enemy = EnemyShip();

		for (int i = 0; i < CantAsteroides; i++)
		{
			Asteroide* newAst = new Asteroide();
			Ast.push_back(newAst);
		}

		return true;
	}

	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{		
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_W:
			Ship[Index].MoveUp();
			break;
		case SDL_SCANCODE_S:
			Ship[Index].MoveDown();
			break;
		case SDL_SCANCODE_A:
			Ship[Index].MoveLeft();
			break;
		case SDL_SCANCODE_D:
			Ship[Index].MoveRight();
			break;
		case SDL_SCANCODE_SPACE:
			Ship[Index].Disparar();
			break;
		case SDL_SCANCODE_P:
			Index++;
			if (Index > (Ship.size() - 1))
			{
				Index = 0;
			}

			break;
		default:			
			SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
			break;
		}
	}

	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			OnExit();
			break;
		default:
			//DO NOTHING
			break;
		}
	}

	void App::Update()
	{
		double startTime = m_timer->GetElapsedTimeInSeconds();

		//Update of the ship
		Ship[Index].Update(DESIRED_FRAME_RATE);

		//Update of the enemy ship
		enemy.Update(DESIRED_FRAME_RATE, Ship[Index].Position);

		//Update of the asteroids
		for (int i = 0; i < Ast.size(); i++)
		{
			Ast.at(i)->Mover(DESIRED_FRAME_RATE);
		}
		
		//Check if you have live or not
		CheckLive();

		//Check for asteroids yes or no
		CheckAst();

		//Check all collisions
		if(EnterColliding != true)
			CheckColliding();
		else
		{
			RespawnTime++;

			if (RespawnTime == 100)
			{
				EnterColliding = false;
				RespawnTime = 0;
			}
		}

		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		while (endTime < nextTimeFrame)
		{
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		double elapsedTime = endTime - startTime;        

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		m_nUpdates++;
	}

	void App::Render()
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw the ships
		Ship[Index].Draw();

		//Draw the lives of the ships
		ShipVidas[Index].Vidas(CantVidas,Index);

		//Draw the enemy ships
		enemy.Draw();

		//Draw the asteroids
		for (int i = 0; i < Ast.size(); i++)
		{
			Ast.at(i)->DrawAst();
		}
		
		SDL_GL_SwapWindow(m_mainWindow);
	}

	bool App::SDLInit()
	{
		// Initialize SDL's Video subsystem
		//
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Failed to init SDL" << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Uint32 flags =  SDL_WINDOW_OPENGL     | 
						SDL_WINDOW_SHOWN      | 
						SDL_WINDOW_RESIZABLE;

		m_mainWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			flags
		);

		if (!m_mainWindow)
		{
			std::cerr << "Failed to create window!" << std::endl;
			SDL_Quit();
			return false;
		}

		m_context = SDL_GL_CreateContext(m_mainWindow);
		SDL_GL_MakeCurrent(m_mainWindow, m_context);

		// Make double buffer interval synced with vertical scanline refresh
		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		// Defining ortho values
		//
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		// Set viewport to match window
		//
		glViewport(0, 0, m_width, m_height);

		// Set Mode to GL_PROJECTION
		//
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set projection MATRIX to ORTHO
		//
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		// Setting Mode to GL_MODELVIEW
		//
		glMatrixMode(GL_MODELVIEW);
	}

	bool App::GlewInit()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		return true;
	}

	void App::CleanupSDL()
	{
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;

		SetupViewport();
	}

	void App::OnExit()
	{
		// Exit main for loop
		//
		m_state = GameState::QUIT;

		// Cleanup SDL pointers
		//
		CleanupSDL();
	}

	void App::CheckAst()
	{
		if (Ast.size() == 0)
		{
			CantAsteroides += 3;
			for (int i = 0; i < CantAsteroides; i++)
			{
				Asteroide* newAst = new Asteroide();
				Ast.push_back(newAst);
			}
		}
	}

	void App::CheckLive()
	{
		if (CantVidas == 0)
		{
			cout << "GAME OVER!!!" << endl;
			cout << "Su Score final es: " << Score << endl;
			std::system("Pause");
			exit(EXIT_FAILURE);
		}
	}

	void App::CheckColliding()
	{
		bool bulletHit = false;

		for (auto copy : Ast)
		{
			Asteroide* pAst = dynamic_cast<Asteroide*> (copy);
			if (pAst)
			{
				if (Ship[Index].Colliding(*copy))
				{
					EnterColliding = true;
					CantVidas--;
					int size = pAst->getSize();

					Ast.erase(remove(Ast.begin(), Ast.end(), copy), Ast.end());
					delete copy;

					if (size == 0)
					{
						for (int i = 0; i < 2; i++)
						{
							Vector2 PosAleatoria;
							float x = static_cast<float> (-400 + (400 + 400) * (rand() / static_cast<float> (RAND_MAX)));
							float y = static_cast<float> (-400 + (400 + 400) * (rand() / static_cast<float> (RAND_MAX)));
							PosAleatoria = Vector2(x, y);

							Asteroide* nEnemy = new Asteroide(PosAleatoria, 1);
							Ast.push_back(nEnemy);
						}
					}
					if (size == 1)
					{
						for (int i = 0; i < 2; i++)
						{
							Vector2 PosAleatoria;
							float x = static_cast<float> (-300 + (300 + 300) * (rand() / static_cast<float> (RAND_MAX)));
							float y = static_cast<float> (-300 + (300 + 300) * (rand() / static_cast<float> (RAND_MAX)));
							PosAleatoria = Vector2(x, y);

							Asteroide* nEnemy = new Asteroide(PosAleatoria, 2);
							Ast.push_back(nEnemy);
						}
					}

					Ship[Index].Reiniciar();

					break;
				}

				for (int i = 0; i < Ship[Index].Balas.size(); i++)
				{
					if (Ship[Index].Balas[i]->Colliding(*pAst))
					{
						int size = pAst->getSize();

						Ast.erase(remove(Ast.begin(), Ast.end(), copy), Ast.end());
						delete copy;

						Ship[Index].EliminarBala(Ship[Index].Balas[i]);

						if (size == 0)

						{
							Score += 100;
							for (int i = 0; i < 2; i++)
							{
								Vector2 PosAleatoria;
								float x = static_cast<float> (-400 + (400 + 400) * (rand() / static_cast<float> (RAND_MAX)));
								float y = static_cast<float> (-400 + (400 + 400) * (rand() / static_cast<float> (RAND_MAX)));
								PosAleatoria = Vector2(x, y);

								Asteroide* nEnemy = new Asteroide(PosAleatoria, 1);
								Ast.push_back(nEnemy);
							}
						}
						if (size == 1)
						{
							Score += 200;
							for (int i = 0; i < 2; i++)
							{
								Vector2 PosAleatoria;
								float x = static_cast<float> (-300 + (300 + 300) * (rand() / static_cast<float> (RAND_MAX)));
								float y = static_cast<float> (-300 + (300 + 300) * (rand() / static_cast<float> (RAND_MAX)));
								PosAleatoria = Vector2(x, y);

								Asteroide* nEnemy = new Asteroide(PosAleatoria, 2);
								Ast.push_back(nEnemy);
							}
						}
						if (size == 2)
							Score += 300;

						bulletHit = true;
					}
				}
				if (bulletHit == true)
					break;

				for (int x = 0; x < enemy.Balas.size(); x++)
				{
					if (enemy.Balas[x]->Colliding(Ship[Index]))
					{
						EnterColliding = true;
						CantVidas--;
						Ship[Index].Reiniciar();
						enemy.EliminarBala(enemy.Balas[x]);
						break;
					}
				}

				for (int x = 0; x < Ship[Index].Balas.size(); x++)
				{
					if (Ship[Index].Balas[x]->Colliding(enemy))
					{
						Score += 500;
						enemy.~EnemyShip();
						Ship[Index].EliminarBala(Ship[Index].Balas[x]);
						Entro = true;
					}
				}

				if (Entro == true)
				{
					if (Time == 1000)
					{
						enemy = EnemyShip();
					}
					Time++;
				}
			}

		}
	}
}
