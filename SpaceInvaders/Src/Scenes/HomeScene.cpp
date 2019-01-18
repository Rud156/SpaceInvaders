#include "HomeScene.h"
#include "raylib.h"

namespace Scenes
{
	HomeScene* HomeScene::_instance = nullptr;

	HomeScene::HomeScene()
	{
		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();
	}

	HomeScene* HomeScene::Instance()
	{
		if (_instance == nullptr)
			_instance = new HomeScene();

		return _instance;
	}

	bool HomeScene::drawAndCheckForGameStart()
	{
		const auto screenMiddle = Instance()->_screen_width / 2;

		DrawText(Instance()->_header.c_str(), screenMiddle, 30, 30, RED);
		DrawText(Instance()->_controls.c_str(), screenMiddle, 60, 20, MAGENTA);

		DrawText(Instance()->_createdBy.c_str(), screenMiddle,
		         Instance()->_screen_height - 30, 30, BLUE);

		const auto mousePosition = GetMousePosition();
		const Rectangle buttonBounds = {static_cast<float>(screenMiddle), 120.0f, 200.0f, 50.0f};

		DrawRectangleLinesEx(buttonBounds, 3, RED);
		DrawText("Play", buttonBounds.x, buttonBounds.y, 25, RED);
		if (CheckCollisionPointRec(mousePosition, buttonBounds))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				return true;
		}

		return false;
	}
}
