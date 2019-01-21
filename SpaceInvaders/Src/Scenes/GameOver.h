#pragma once
#include "raylib.h"
#include "../Common/Explosion.h"
#include <vector>

namespace Scenes
{
	class GameOver final
	{
	private:
		int _screen_width;
		int _screen_height;

		const char* _game_won_text = "You Won The Game !!!";
		const char* _game_lost_text = "You Lost The Game...";
		const char* _replay_text = "Replay";

		std::vector<Common::Explosion*> _explosions;
		const float _time_between_explosions = 0.3f;
		float _current_time = _time_between_explosions;

		Vector2 _mouse_position;
		Rectangle _button_bounds;
		Color _button_color;

		bool _game_won = true;

		static GameOver* _instance;
		GameOver();

		static void updateStaticObjects();
		static void createExplosionAtRandomPlace();

	public:
		~GameOver();

		static GameOver* Instance();
		static void setupScene();

		static void drawScene();
		static bool updateScene();
		static void clearScene();

		static void setGameState(bool won);
	};
}
