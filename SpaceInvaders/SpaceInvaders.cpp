// SpaceInvaders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"

#include "Src/Scenes/MainScene.h"
#include "Src/Scenes/HomeScene.h"
#include "Src/Scenes/GameOver.h"

int main()
{
	const auto screenWidth = 800;
	const auto screenHeight = 450;
	auto sceneType = Enums::Scene::Home;

	InitWindow(screenWidth, screenHeight, "Space Invaders");
	InitAudioDevice();

	const auto backgroundMusic = LoadSound("resources/audio/background.wav");

	Scenes::HomeScene::Instance(); // Create Instance of HomeScene
	Scenes::MainScene::Instance(); // Create Instance of MainScene
	Scenes::GameOver::Instance(); // Create Instance of GameOverScene

	Scenes::HomeScene::setupScene();
	Scenes::GameOver::setupScene();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		if (!IsSoundPlaying(backgroundMusic))
			PlaySound(backgroundMusic);

		switch (sceneType)
		{
		case Enums::Scene::Home:
			{
				const auto gameStarted = Scenes::HomeScene::drawAndCheckForGameStart();
				if (gameStarted)
				{
					sceneType = Enums::Scene::Main;
					Scenes::MainScene::setupOrResetScene(1);
				}
			}
			break;

		case Enums::Scene::Main:
			{
				const auto gameOver = Scenes::MainScene::update();
				if (gameOver)
				{
					sceneType = Enums::Scene::GameOver;
					Scenes::GameOver::clearScene();
				}
			}
			break;

		case Enums::Scene::GameOver:
			{
				Scenes::GameOver::drawScene();
				const auto resetGame = Scenes::GameOver::updateScene();
				if (resetGame)
					sceneType = Enums::Scene::Home;
			}
			break;

		default: break;
		}

		EndDrawing();
	}

	UnloadSound(backgroundMusic);

	CloseAudioDevice();
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
