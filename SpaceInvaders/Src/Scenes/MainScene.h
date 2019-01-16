#pragma once
#include "../Player/SpaceShip.h"
#include "../Enemies/Enemy.h"


namespace Scenes
{
	class MainScene
	{
	private:
		Player::SpaceShip* _space_ship;
		Enemies::Enemy* _test_enemy;

		int _screen_width;
		int _screen_height;

	public:
		MainScene();
		~MainScene();

		void draw() const;
	};
}
