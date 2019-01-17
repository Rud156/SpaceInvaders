#pragma once
#include "../Player/SpaceShip.h"
#include "../Enemies/Enemy.h"
#include "../Common/Explosion.h"
#include <vector>

namespace Scenes
{
	class MainScene
	{
	private:
		Player::SpaceShip* _space_ship;
		Enemies::Enemy* _test_enemy;

		std::vector<Common::Explosion*> _explosions;

		int _screen_width;
		int _screen_height;

		static MainScene *_instance;
		MainScene();

	public:
		static MainScene *Instance();
		~MainScene();

		void draw();
		void addExplosion(float xPosition, float yPosition, float radius);
	};
}
