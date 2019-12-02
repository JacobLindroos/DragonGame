#include "GameManager.h"

#pragma region Con- & Destructor

GameManager::GameManager()
{
	//creates a new player and background on the heap
	background = new Background(560.f, 0.f, 800, 3200, "Res/origin.png");
	player = new Player(928.f, 950.f, "Res/Dragon.png", Player::Normal, Player::None);
}

GameManager::~GameManager()
{
	//calls the function quit, which clears and cleans up the memory before quiting
	Quit();
}

#pragma endregion


#pragma region Start, Update and Quit

void GameManager::Start()
{
	//calls the function engine initialize which initialize necessary starting functions
	EngineInitialize();
	//setting up our UI manager
	SetUIManager(game.GetUIManager());
}


//funtion that updates our game
void GameManager::Update()
{
	//while loop that runs until the engineIsOpen function returns false
	while (EngineIsOpen()) {

		//spawns the background and player
		game.SpawnGameObject(background);
		game.SpawnGameObject(player);

		//while loop that runs until the engineIsOpen function returns false
		while (EngineIsOpen())
		{
			//gets the time at frame start
			time.StartFrame();
			//clearing before rendering
			EngineClear();
			//goes through all update functions connected to all game objects in the game
			game.Update(time.DeltaTime());
			//spawns enemies into the game w. a spawndelay of 0.5 seconds
			spawn.SpawnEnemies(&game, time.DeltaTime(), 0.5f);
			//render all game objects 
			game.Render();
			//checking for key input
			EngineUpdate();
			//gets the time at frame end
			time.EndFrame();

			//Wait to achieve target framerate 
			if (time.DeltaTime() < frameDelay)
			{
				SDL_Delay(frameDelay - time.DeltaTime());
			}
		}
	}
}


//quit function that calls for enginedestroy funtion..
//..which destroys the window and rendering. Also quiting SDL and TTF
void GameManager::Quit()
{
	EngineDestroy();
}

#pragma endregion
