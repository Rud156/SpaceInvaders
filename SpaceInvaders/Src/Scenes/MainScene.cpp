#include "MainScene.h"

namespace Scenes
{
	MainScene::MainScene()
	{
		// TODO: Make Main Scene a Singleton so that explosions can be added
		// Also will be required to remove destroyed enemies and stray bullets

		this->_screen_width = GetScreenWidth();
		this->_screen_height = GetScreenHeight();

		this->_space_ship = new Player::SpaceShip();
		this->_test_enemy = new Enemies::Enemy(this->_screen_width / 2, this->_screen_height / 2, 30);
	}

	MainScene::~MainScene()
	{
		delete this->_space_ship;
		delete this->_test_enemy;
	}

	void MainScene::draw() const
	{
		// Space Ship Display and Control
		this->_space_ship->show();
		this->_space_ship->update();

		// TODO: Testing
		this->_test_enemy->show();
		this->_test_enemy->update();
		this->_test_enemy->checkAndShootIfNearPlayer(this->_space_ship->getSpaceShipPosition());
	}
}
