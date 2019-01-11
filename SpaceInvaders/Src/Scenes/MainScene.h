#pragma once
#include "../Player/SpaceShip.h"


namespace Scenes
{
	class MainScene
	{
	private:
		Player::SpaceShip* _space_ship;

	public:
		MainScene();
		~MainScene();
		void draw() const;
	};
}
