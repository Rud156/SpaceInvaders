#pragma once
#include "../Player/SpaceShip.h"
#include "../Enemies/Enemy.h"
#include "../Common/Explosion.h"
#include <vector>
#include "../Common/Collectible.h"

namespace Scenes
{
	class MainScene final
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

		static void updateStaticObjects();
		static void updateDynamicObjects();

	public:
		static MainScene* Instance();
		~MainScene();

		static void createOrResetScene();
		static void update();

		void addExplosion(float xPosition, float yPosition, float radius);
		static void addCollectible(float xPosition, float yPosition, Enums::CollectibleType collectibleType);
		static void destroyEnemy(int enemyIndex);
	};
}
