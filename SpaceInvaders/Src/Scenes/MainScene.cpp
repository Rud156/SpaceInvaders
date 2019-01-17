#include "MainScene.h"

namespace Scenes
{
	MainScene* MainScene::_instance = nullptr;

	MainScene::MainScene()
	{
		// TODO: Make Main Scene a Singleton so that explosions can be added
		// Also will be required to remove destroyed enemies and stray bullets

		this->_screen_width = GetScreenWidth();
		this->_screen_height = GetScreenHeight();

		this->_space_ship = new Player::SpaceShip();
		this->_test_enemy = new Enemies::Enemy(this->_screen_width / 2.0f, this->_screen_height / 2.0f, 30);
	}

	MainScene* MainScene::Instance()
	{
		if (MainScene::_instance == nullptr)
			MainScene::_instance = new MainScene();

		return MainScene::_instance;
	}

	MainScene::~MainScene()
	{
		delete this->_space_ship;
		delete this->_test_enemy;
	}

	void MainScene::draw()
	{
		// Space Ship Display and Control
		this->_space_ship->show();
		this->_space_ship->update();

		if (this->_test_enemy != nullptr)
		{
			// TODO: Testing
			this->_test_enemy->show();
			this->_test_enemy->update();
			this->_test_enemy->checkAndShootIfNearPlayer(this->_space_ship->getSpaceShipPosition());

			this->_space_ship->checkEnemyCollisionWithBullet(this->_test_enemy);
		}

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

	void MainScene::addExplosion(float xPosition, float yPosition, float radius)
	{
		this->_explosions.push_back(new Common::Explosion(xPosition, yPosition, radius));
	}
}
