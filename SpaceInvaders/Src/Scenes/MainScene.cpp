#include "MainScene.h"
#include "../Common/LevelEnemyGenerator.h"

namespace Scenes
{
	MainScene* MainScene::_instance = nullptr;

	MainScene::MainScene()
	{
		Instance()->_scene_started = false;
	}

	MainScene* MainScene::Instance()
	{
		if (_instance == nullptr)
			_instance = new MainScene();

		return _instance;
	}

	MainScene::~MainScene()
	{
		delete Instance()->_space_ship;

		for (auto& _enemy : Instance()->_enemies)
			delete _enemy;

		for (auto& _explosion : Instance()->_explosions)
			delete _explosion;

		for (auto& _collectible : Instance()->_collectibles)
			delete _collectible;

		Instance()->_enemies.clear();
		Instance()->_collectibles.clear();
		Instance()->_explosions.clear();
	}

	void MainScene::createOrResetScene(const int levelNumber)
	{
		Instance()->_scene_started = true;

		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();

		Instance()->_space_ship = new Player::SpaceShip();
		Instance()->_enemies = Common::LevelEnemyGenerator::GetEnemyForLevel(levelNumber);
	}

	void MainScene::update()
	{
		updateStaticObjects();
		updateDynamicObjects();
	}

	void MainScene::updateStaticObjects()
	{
		for (std::size_t i = 0; i < Instance()->_explosions.size(); i++)
		{
			Instance()->_explosions[i]->show();
			Instance()->_explosions[i]->update();

			if (Instance()->_explosions[i]->explosionComplete())
			{
				delete Instance()->_explosions[i];
				Instance()->_explosions.erase(Instance()->_explosions.begin() + i);
				i -= 1;
			}
		}

		for (std::size_t i = 0; i < Instance()->_collectibles.size(); i++)
		{
			Instance()->_collectibles[i]->show();
			Instance()->_collectibles[i]->update();

			if (Instance()->_collectibles[i]->isOutOfScreen())
			{
				delete Instance()->_collectibles[i];
				Instance()->_collectibles.erase(Instance()->_collectibles.begin() + i);
				i -= 1;
			}
		}
	}

	void MainScene::updateDynamicObjects()
	{
		if (Instance()->_space_ship != nullptr)
		{
			Instance()->_space_ship->show();
			Instance()->_space_ship->update();
		}

		for (std::size_t i = 0; i < Instance()->_enemies.size(); i++)
		{
			Instance()->_enemies[i]->show();
			Instance()->_enemies[i]->update();

			if (Instance()->_space_ship != nullptr)
				Instance()->_enemies[i]->checkAndShootIfNearPlayer(Instance()->_space_ship->getSpaceShipPosition());
		}
	}

	void MainScene::addCollectible(const float xPosition, const float yPosition,
	                               const Enums::CollectibleType collectibleType)
	{
		Instance()->_collectibles.push_back(new Common::Collectible(xPosition, yPosition, collectibleType));
	}

	void MainScene::destroyEnemy(int enemyIndex)
	{
		delete Instance()->_enemies[enemyIndex];
		Instance()->_enemies.erase(Instance()->_enemies.begin() + enemyIndex);
	}

	void MainScene::addExplosion(float xPosition, float yPosition, float radius)
	{
		this->_explosions.push_back(new Common::Explosion(xPosition, yPosition, radius));
	}
}
