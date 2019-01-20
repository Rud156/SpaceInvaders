#pragma once
#include "../Enemies/Enemy.h"
#include "../Player/SpaceShip.h"
#include "../Common/Explosion.h"
#include "../Common/Collectible.h"
#include <vector>

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

		const char* _first_play = "Game Starts In...";
		const char* _subsequent_play = "Next Wave In...";

		const int _max_countdown = 3;
		float _current_countdown = _max_countdown;

		static MainScene* _instance;
		MainScene();

		static bool countdownToGameAndStart();

		static void updateStaticObjects();

		static void updateEnemies();
		static void updatePlayer();

		static void createExtraEnemiesBasedOnSize(float xPosition, float yPosition, float enemyBaseWidth);
		static void checkPlayerCollectibleCollision();

	public:
		static MainScene* Instance();
		~MainScene();

		static void setupOrResetScene(int levelNumber);
		static bool update();

		void addExplosion(float xPosition, float yPosition, float radius);
		static void addCollectible(float xPosition, float yPosition, Enums::BulletType bulletType);

		static void destroyEnemy(int enemyIndex);
		static void destroyPlayer();
	};
}
