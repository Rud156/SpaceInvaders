#pragma once
#include "../Player/SpaceShip.h"


namespace Scenes {
	class MainScene
	{
	private:
		Player::SpaceShip *_space_ship;

	public:
		MainScene(int windowWidth, int windowHeight);
		~MainScene();
		void draw();
	};
}