#include "MainScene.h"
#include "../Common/LevelEnemyGenerator.h"
#include "../Utils/ExtensionFunctions.h"
#include "GameOver.h"

namespace Scenes
{
	MainScene* MainScene::_instance = nullptr;

	MainScene::MainScene()
	{
		// Constructor must be empty and not call any reference
		// Or a recursive stackoverflow exception will occur
	}

	bool MainScene::countdownToGameAndStart()
	{
		const auto displayTime = Utils::ExtensionFunctions::
			FormatFloatToStringInt(Instance()->_current_countdown);

		const char* displayText;
		if (Instance()->_current_level <= 1)
			displayText = Instance()->_first_play;
		else
			displayText = Instance()->_subsequent_play;

		const auto screenWidthMiddle = Instance()->_screen_width / 2;
		const auto screenHeightMiddle = Instance()->_screen_height / 2;

		const auto displayTextWidth = MeasureText(displayText, 25);
		DrawText(displayText, screenWidthMiddle - displayTextWidth / 2,
		         screenHeightMiddle - 50, 25, RED);

		const auto displayTimeWidth = MeasureText(displayTime, 30);
		DrawText(displayTime, screenWidthMiddle - displayTimeWidth / 2,
		         screenHeightMiddle + 50, 30, BLUE);

		Instance()->_current_countdown -= GetFrameTime();

		return Instance()->_current_countdown <= 0;
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

	void MainScene::setupOrResetScene(const int levelNumber)
	{
		Instance()->_current_countdown = Instance()->_max_countdown;

		Instance()->_scene_started = true;
		Instance()->_current_level = levelNumber;

		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();

		Instance()->_space_ship = new Player::SpaceShip();
		Instance()->_enemies = Common::LevelEnemyGenerator::GetEnemyForLevel(levelNumber);
	}

	bool MainScene::update()
	{
		if (!Instance()->_scene_started)
			return true;

		if (Instance()->_enemies.empty())
		{
			Instance()->_current_level += 1;

			if (Instance()->_current_level > Instance()->_max_level)
			{
				GameOver::setGameState(true);
				return true;
			}

			Instance()->_enemies = Common::LevelEnemyGenerator::
				GetEnemyForLevel(Instance()->_current_level);
		}

		updateStaticObjects();
		updateDynamicObjects();

		return false;
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
			{
				Instance()->_enemies[i]->checkAndShootIfNearPlayer
					(Instance()->_space_ship->getSpaceShipPosition());

				Instance()->_enemies[i]->checkPlayerCollisionWithBullet(Instance()->_space_ship);
				Instance()->_space_ship->checkEnemyCollisionWithBullet(Instance()->_enemies[i], i);

				checkPlayerCollectibleCollision();
			}
		}
	}

	void MainScene::checkPlayerCollectibleCollision()
	{
		for (std::size_t i = 0; i < Instance()->_collectibles.size(); i++)
		{
			const auto collectiblePosition = Instance()->_collectibles[i]->getPosition();
			if (Instance()->_space_ship->didSpaceShipCollide(collectiblePosition))
			{
				const auto collectibleBulletType = Instance()->_collectibles[i]->getBulletType();
				Instance()->_space_ship->setBulletType(collectibleBulletType);

				delete Instance()->_collectibles[i];
				Instance()->_collectibles.erase(Instance()->_collectibles.begin() + i);
				i -= 1;
			}
		}
	}

	void MainScene::addCollectible(const float xPosition, const float yPosition,
	                               const Enums::BulletType bulletType)
	{
		Instance()->_collectibles.push_back(new Common::Collectible(xPosition, yPosition, bulletType));
	}

	void MainScene::createExtraEnemiesBasedOnSize(const float xPosition, const float yPosition,
	                                              const float enemyBaseWidth)
	{
		if (enemyBaseWidth > 100)
		{
			for (auto i = 0; i < 2; i++)
			{
				Instance()->_enemies.push_back(
					new Enemies::Enemy(xPosition, yPosition, enemyBaseWidth / 2)
				);
			}
		}
	}

	void MainScene::destroyEnemy(int enemyIndex)
	{
		const auto enemyPosition = Instance()->_enemies[enemyIndex]->getEnemyPosition();
		const auto enemyBaseWidth = Instance()->_enemies[enemyIndex]->getEnemyBaseWidth();

		Instance()->addExplosion(enemyPosition.x, enemyPosition.y, enemyBaseWidth * 7 / 45);
		Instance()->createExtraEnemiesBasedOnSize(enemyPosition.x, enemyPosition.y, enemyBaseWidth);

		const auto randomValue = GetRandomValue(0, 1000);
		if (randomValue % 2 == 0)
			Instance()->addCollectible(enemyPosition.x, enemyPosition.y,
			                           Utils::ExtensionFunctions::getRandomBulletType());

		delete Instance()->_enemies[enemyIndex];
		Instance()->_enemies.erase(Instance()->_enemies.begin() + enemyIndex);
	}

	void MainScene::destroyPlayer()
	{
		delete Instance()->_space_ship;
		Instance()->_scene_started = false;

		GameOver::setGameState(false);
	}

	void MainScene::addExplosion(const float xPosition, const float yPosition, const float radius)
	{
		this->_explosions.push_back(new Common::Explosion(xPosition, yPosition, radius));
	}
}
