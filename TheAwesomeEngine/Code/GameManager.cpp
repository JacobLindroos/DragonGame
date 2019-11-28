#include "GameManager.h"

GameManager::GameManager()
{
	background = new Background(560.f, 0.f, 800, 3200, "Res/Clouds4.png");
	player = new Player(928.f, 950.f, "Res/Ma_Man.png",Player::Normal,Player::None);
}


GameManager::~GameManager()
{
}


void GameManager::Start()
{
	EngineInitialize();
	SetUIManager(game.GetUIManager());
}


void GameManager::Update()
{
	while (EngineIsOpen()) {

		game.SpawnGameObject(background);
		game.SpawnGameObject(player);

		while (EngineIsOpen())
		{
			time.StartFrame();
			EngineClear();
			game.Update(time.DeltaTime());

			spawn.SpawnEnemies(&game, time.DeltaTime(), 0.75f);

			game.Render();

			EngineUpdate();
			time.EndFrame();

			// Wait to achieve target framerate 
			if (time.DeltaTime() < frameDelay)
			{
				SDL_Delay(frameDelay - time.DeltaTime());
			}
		}
	}
}


void GameManager::Quit()
{
	EngineDestroy();
}