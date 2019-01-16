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

		static MainScene *_instance;
		MainScene();

	public:
		static MainScene *Instance();
		~MainScene();

		void draw() const;
	};
}
