// SpaceInvaders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"

#include "Src/Scenes/MainScene.h"
#include "Src/Scenes/HomeScene.h"

int main()
{
	const auto screenWidth = 800;
	const auto screenHeight = 450;
	auto sceneType = Enums::Scene::Home;
	auto gameStarted = false;
	
	InitWindow(screenWidth, screenHeight, "Space Invaders");
	
	Scenes::HomeScene::Instance(); // Create Instance of HomeScene
	Scenes::MainScene::Instance(); // Create Instance of MainScene
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
	
		switch (sceneType)
		{
		case Enums::Main:
			Scenes::MainScene::update();
			break;
	
		case Enums::Home:
			gameStarted = Scenes::HomeScene::drawAndCheckForGameStart();
			if (gameStarted)
				sceneType = Enums::Scene::Main;
			break;
	
		case Enums::GameOver:
			break;
	
		default: break;
		}
	
		DrawFPS(10, 10);
		EndDrawing();
	}
	
	CloseWindow();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
