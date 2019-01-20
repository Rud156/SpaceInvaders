#include "GameOver.h"

namespace Scenes
{
	GameOver* GameOver::_instance = nullptr;

	GameOver::GameOver()
	{
		// Constructor must be empty and not call any reference
		// Or a recursive stackoverflow exception will occur
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

	bool GameOver::drawScene()
	{
		const auto screenWidthMiddle = Instance()->_screen_width / 2;
		const auto screenHeightMiddle = Instance()->_screen_height / 2;

		if (Instance()->_gameWon)
		{
			const auto gameWonTextWidth = MeasureText(Instance()->_game_won_text, 30);
			DrawText(Instance()->_game_won_text, screenWidthMiddle - gameWonTextWidth / 2,
			         screenHeightMiddle - 50, 30, GREEN);
		}
		else
		{
			const auto gameLostTextWidth = MeasureText(Instance()->_game_lost_text, 30);
			DrawText(Instance()->_game_lost_text, screenWidthMiddle - gameLostTextWidth / 2,
			         screenHeightMiddle - 50, 0, RED);
		}

		const auto mousePosition = GetMousePosition();
		const auto buttonWidth = 200.0f;
		const auto buttonHeight = 50.0f;
		const Rectangle buttonBounds = {
			static_cast<float>(screenWidthMiddle) - buttonWidth / 2, screenHeightMiddle,
			buttonWidth, buttonHeight
		};

		DrawRectangleLinesEx(buttonBounds, 3, Instance()->_button_color);
		if (CheckCollisionPointRec(mousePosition, buttonBounds))
		{
			Instance()->_button_color = MAGENTA;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				return true;
		}
		else
			Instance()->_button_color = ORANGE;

		return false;
	}

	void GameOver::setGameState(const bool won)
	{
		Instance()->_gameWon = won;
	}
}
