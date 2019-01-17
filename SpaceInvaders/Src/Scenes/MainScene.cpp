#include "MainScene.h"

namespace Scenes
{
	MainScene* MainScene::_instance = nullptr;

	MainScene::MainScene()
	{
		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();

		Instance()->_space_ship = new Player::SpaceShip();
	}

	MainScene* MainScene::Instance()
	{
		if (MainScene::_instance == nullptr)
			MainScene::_instance = new MainScene();

		return MainScene::_instance;
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

	void MainScene::show()
	{
		// Space Ship Display and Control
		this->_space_ship->show();
		this->_space_ship->update();

		// Explosions and Effects
		for (size_t i = 0; i < this->_explosions.size(); i++)
		{
			this->_explosions[i]->show();
			this->_explosions[i]->update();

			if (this->_explosions[i]->explosionComplete())
			{
				delete this->_explosions[i];
				this->_explosions.erase(this->_explosions.begin() + i);
				i = -1;
			}
		}
	}

	void MainScene::update()
	{
		Instance()->updateStaticObjects();
		Instance()->updateDynamicObjects();
	}

	void MainScene::updateStaticObjects()
	{
		for (size_t i = 0; i < Instance()->_explosions.size(); i++)
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

		for (size_t i = 0; i < Instance()->_collectibles.size(); i++)
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
	}

	void MainScene::addCollectible(float xPosition, float yPosition, Enums::CollectibleType collectibleType)
	{
	}

	void MainScene::destroyEnemy(int enemyIndex)
	{
	}

	void MainScene::addExplosion(float xPosition, float yPosition, float radius)
	{
		this->_explosions.push_back(new Common::Explosion(xPosition, yPosition, radius));
	}
}
