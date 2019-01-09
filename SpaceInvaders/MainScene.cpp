#include "pch.h"
#include "MainScene.h"

Scenes::MainScene::MainScene(int windowWidth, int windowHeight)
{
	this->_space_ship = new Player::SpaceShip(windowWidth, windowHeight);
}

Scenes::MainScene::~MainScene()
{
	delete this->_space_ship;
}

void Scenes::MainScene::draw()
{
	// Space Ship Display and Control
	this->_space_ship->show();
	this->_space_ship->update();
}
