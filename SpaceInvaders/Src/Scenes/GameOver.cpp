#include "GameOver.h"

namespace Scenes
{
	GameOver* GameOver::_instance = nullptr;

	GameOver::GameOver()
	{
		// Constructor must be empty and not call any reference
		// Or a recursive stackoverflow exception will occur
	}

	GameOver::~GameOver()
	{
		clearScene();
		_instance = nullptr;
	}

	GameOver* GameOver::Instance()
	{
		if (_instance == nullptr)
			_instance = new GameOver();

		return _instance;
	}

	void GameOver::setupScene()
	{
		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();
	}

	void GameOver::drawScene()
	{
		const auto screenWidthMiddle = Instance()->_screen_width / 2;
		const auto screenHeightMiddle = Instance()->_screen_height / 2;

		if (Instance()->_game_won)
		{
			const auto gameWonTextWidth = MeasureText(Instance()->_game_won_text, 30);
			DrawText(Instance()->_game_won_text, screenWidthMiddle - gameWonTextWidth / 2,
			         screenHeightMiddle - 100, 30, GREEN);
		}
		else
		{
			const auto gameLostTextWidth = MeasureText(Instance()->_game_lost_text, 30);
			DrawText(Instance()->_game_lost_text, screenWidthMiddle - gameLostTextWidth / 2,
			         screenHeightMiddle - 100, 30, RED);
		}

		Instance()->_mouse_position = GetMousePosition();
		const auto buttonWidth = 200.0f;
		const auto buttonHeight = 50.0f;
		const Rectangle buttonBounds = {
			static_cast<float>(screenWidthMiddle) - buttonWidth / 2, screenHeightMiddle + 100,
			buttonWidth, buttonHeight
		};

		DrawRectangleLinesEx(buttonBounds, 3, Instance()->_button_color);

		const auto replayWidth = MeasureText(Instance()->_replay_text, 25);
		DrawText(Instance()->_replay_text, buttonBounds.x + buttonWidth / 2 - replayWidth / 2.0f,
		         buttonBounds.y + buttonHeight / 2 - 25 / 2.0f,
		         25, Instance()->_button_color);

		Instance()->_button_bounds = buttonBounds;
	}

	bool GameOver::updateScene()
	{
		if (Instance()->_game_won)
		{
			updateStaticObjects();

			if (Instance()->_current_time <= 0)
			{
				Instance()->_current_time = Instance()->_time_between_explosions;
				createExplosionAtRandomPlace();
			}

			Instance()->_current_time -= GetFrameTime();
		}

		if (CheckCollisionPointRec(Instance()->_mouse_position, Instance()->_button_bounds))
		{
			Instance()->_button_color = MAGENTA;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				return true;
		}
		else
			Instance()->_button_color = ORANGE;

		return false;
	}

	void GameOver::clearScene()
	{
		for (auto& _explosion : Instance()->_explosions)
			delete _explosion;

		Instance()->_explosions.clear();

		Instance()->_current_time = Instance()->_time_between_explosions;
	}

	void GameOver::updateStaticObjects()
	{
		for (std::size_t i = 0; i < Instance()->_explosions.size(); i++)
		{
			Instance()->_explosions[i]->show();
			Instance()->_explosions[i]->update();

			if (Instance()->_explosions[i]->explosionComplete())
			{
				delete Instance()->_explosions[i];
				Instance()->_explosions.erase(Instance()->_explosions.begin() + i);
				i -= 1;
			}
		}
	}

	void GameOver::createExplosionAtRandomPlace()
	{
		const auto randomX = GetRandomValue(0, Instance()->_screen_width);
		const auto randomY = GetRandomValue(0, Instance()->_screen_height);
		const auto randomRadius = GetRandomValue(7, 14);

		Instance()->_explosions.push_back(new Common::Explosion(randomX, randomY, randomRadius));
	}

	void GameOver::setGameState(const bool won)
	{
		Instance()->_game_won = won;
	}
}
