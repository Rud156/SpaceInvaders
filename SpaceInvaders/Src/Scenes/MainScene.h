#pragma once
#include "../Player/SpaceShip.h"
#include "../Enemies/Enemy.h"
#include "../Common/Explosion.h"
#include <vector>
#include "../Common/Collectible.h"

namespace Scenes
{
	class MainScene
	{
	private:
		Player::SpaceShip* _space_ship;

		std::vector<Enemies::Enemy*> _enemies;
		std::vector<Common::Explosion*> _explosions;
		std::vector<Common::Collectible*> _collectibles;

		int _screen_width;
		int _screen_height;

		static MainScene* _instance;
		MainScene();

	public:
		static MainScene* Instance();
		~MainScene();

		void show();
		void update();

		void updateStaticObjects();
		void updateDynamicObjects();

		void addExplosion(float xPosition, float yPosition, float radius);
		void addCollectible(float xPosition, float yPosition, Enums::CollectibleType collectibleType);
		void destroyEnemy(int enemyIndex);
	};
}
