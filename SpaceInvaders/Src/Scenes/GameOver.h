#pragma once
#include "raylib.h"

namespace Scenes
{
	class GameOver
	{
	private:
		int _screen_width;
		int _screen_height;

		const char* _game_won_text = "You Won The Game !!!";
		const char* _game_lost_text = "You Lost The Game...";
		const char* _replay_text = "Replay";

		Color _button_color;

		bool _gameWon;

		static GameOver* _instance;
		GameOver();

	public:
		static GameOver* Instance();
		static void setupScene();

		static bool drawScene();

		static void setGameState(bool won);
	};
}
