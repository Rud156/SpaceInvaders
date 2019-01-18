#pragma once

#include <string>

namespace Scenes
{
	class HomeScene
	{
	private:
		const std::string _header = "Space Invaders";
		const std::string _controls = "Use Arrow Keys to Move and Space to shoot";
		const std::string _createdBy = "Made by Rud156";

		int _screen_width;
		int _screen_height;

		static HomeScene* _instance;
		HomeScene();

	public:
		static HomeScene* Instance();

		static bool drawAndCheckForGameStart();
	};
}
