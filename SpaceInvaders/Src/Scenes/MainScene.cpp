#include "pch.h"
#include "MainScene.h"

namespace Scenes
{
	MainScene::MainScene()
	{
		this->_space_ship = new Player::SpaceShip();
	}

	MainScene::~MainScene()
	{
		delete this->_space_ship;
	}

	void MainScene::draw() const
	{
		// Space Ship Display and Control
		this->_space_ship->show();
		this->_space_ship->update();
	}
}
