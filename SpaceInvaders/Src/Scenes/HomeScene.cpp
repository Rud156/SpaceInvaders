#include "HomeScene.h"

namespace Scenes
{
	HomeScene* HomeScene::_instance = nullptr;

	HomeScene::HomeScene()
	{
		// Constructor must be empty and not call any reference
		// Or a recursive stackoverflow exception will occur
	}

	HomeScene* HomeScene::Instance()
	{
		if (_instance == nullptr)
			_instance = new HomeScene();

		return _instance;
	}

	void HomeScene::setupScene()
	{
		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();

		Instance()->_test_explosion = new Common::Explosion(
			Instance()->_screen_width / 2.0f, Instance()->_screen_height / 2.0f,
			5
		);
	}

	bool HomeScene::drawAndCheckForGameStart()
	{
		if (Instance()->_test_explosion->explosionComplete())
		{
			delete Instance()->_test_explosion;

			Instance()->_test_explosion = new Common::Explosion(
				Instance()->_screen_width / 2.0f, Instance()->_screen_height / 2.0f,
				5
			);
		}
		Instance()->_test_explosion->show();
		Instance()->_test_explosion->update();

		const auto screenMiddle = Instance()->_screen_width / 2;

		const auto headerWidth = MeasureText(Instance()->_header, 30);
		DrawText(Instance()->_header, screenMiddle - headerWidth / 2, 40, 30, ORANGE);

		const auto controlsWidth = MeasureText(Instance()->_controls, 20);
		DrawText(Instance()->_controls, screenMiddle - controlsWidth / 2, 100, 20, MAGENTA);

		const auto createdByWidth = MeasureText(Instance()->_createdBy, 30);
		DrawText(Instance()->_createdBy, screenMiddle - createdByWidth / 2,
		         Instance()->_screen_height - 40, 30, BLUE);

		const auto mousePosition = GetMousePosition();
		const auto screenHeightMiddle = Instance()->_screen_height / 2;
		const auto buttonWidth = 200.0f;
		const auto buttonHeight = 50.0f;
		const Rectangle buttonBounds = {
			static_cast<float>(screenMiddle) - buttonWidth / 2, screenHeightMiddle,
			buttonWidth, buttonHeight
		};

		DrawRectangleLinesEx(buttonBounds, 3, Instance()->_button_color);

		const auto playWidth = MeasureText(Instance()->_play, 25);
		DrawText(Instance()->_play, buttonBounds.x + buttonWidth / 2 - playWidth / 2,
		         buttonBounds.y + buttonHeight / 2 - 25 / 2.0f,
		         25, Instance()->_button_color);
		if (CheckCollisionPointRec(mousePosition, buttonBounds))
		{
			Instance()->_button_color = SKYBLUE;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				return true;
		}
		else
			Instance()->_button_color = RED;

		return false;
	}
}
