#pragma once
#include "raylib.h"
#include "../Common/Explosion.h"

namespace Scenes
{
	class HomeScene final
	{
	private:
		const char* _header = "Space Invaders";
		const char* _controls = "Use Arrow Keys to Move and Space to shoot";
		const char* _createdBy = "Made by Rud156";
		const char* _play = "Play";

		Color _button_color = RED;

		int _screen_width;
		int _screen_height;

		static HomeScene* _instance;
		HomeScene();

	public:
		static HomeScene* Instance();
		static void setupScene();

		static bool drawAndCheckForGameStart();
	};
}
