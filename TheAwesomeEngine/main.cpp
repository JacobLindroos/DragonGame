#include "Code/GameManager.h"

GameManager gameManager;

int main(int argc, char* argv[]) {

	gameManager.Start();
	gameManager.Update();
	gameManager.Quit();

	return 0;
}
