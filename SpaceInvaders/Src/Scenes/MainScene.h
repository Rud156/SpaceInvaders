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

		bool _scene_started;
		int _current_level;
		const int _max_level = 9;

		static MainScene* _instance;
		MainScene();

		static void updateStaticObjects();
		static void updateDynamicObjects();
		static void checkPlayerCollectibleCollision();

	public:
		static MainScene* Instance();
		~MainScene();

		static void setupOrResetScene(int levelNumber);
		static bool update();

		void addExplosion(float xPosition, float yPosition, float radius);
		static void addCollectible(float xPosition, float yPosition, Enums::BulletType bulletType);
		static void createExtraEnemiesBasedOnSize(float xPosition, float yPosition, float enemyBaseWidth);

		static void destroyEnemy(int enemyIndex);
		static void destroyPlayer();
	};
}
