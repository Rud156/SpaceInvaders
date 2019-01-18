#include "LevelEnemyGenerator.h"
#include "../Enemies/Enemy.h"

#include <iostream>

namespace Common
{
	std::vector<Enemies::Enemy*> LevelEnemyGenerator::GetEnemyForLevel(const int levelNumber)
	{
		std::vector<Enemies::Enemy*> enemies;
		const auto screenWidth = GetScreenWidth();

		switch (levelNumber)
		{
		case 1:
			enemies.push_back(
				new Enemies::Enemy(
					GetRandomValue(0, screenWidth),
					-30,
					GetRandomValue(45, 75)
				)
			);
			break;

		case 2:
			for (auto i = 0; i < 2; i++)
			{
				enemies.push_back(
					new Enemies::Enemy(
						GetRandomValue(0, screenWidth),
						-30,
						GetRandomValue(45, 70)
					)
				);
			}
			break;

		case 3:
			for (auto i = 0; i < 15; i++)
			{
				enemies.push_back(
					new Enemies::Enemy(
						GetRandomValue(0, screenWidth),
						-30,
						GetRandomValue(45, 70)
					)
				);
			}
			break;

		case 4:
			enemies.push_back(
				new Enemies::Enemy(
					GetRandomValue(0, screenWidth),
					-30,
					GetRandomValue(150, 170)
				)
			);
			break;

		case 5:
			for (auto i = 0; i < 2; i++)
			{
				enemies.push_back(
					new Enemies::Enemy(
						GetRandomValue(0, screenWidth),
						-30,
						GetRandomValue(150, 170)
					)
				);
			}
			break;

		case 6:
			for (auto i = 0; i < 20; i++)
			{
				enemies.push_back(
					new Enemies::Enemy(
						GetRandomValue(0, screenWidth),
						-30,
						20
					)
				);
			}
			break;

		case 7:
			for (auto i = 0; i < 50; i++)
			{
				enemies.push_back(
					new Enemies::Enemy(
						GetRandomValue(0, screenWidth),
						-30,
						20
					)
				);
			}
			break;

		case 8:
			for (auto i = 0; i < 20; i++)
			{
				enemies.push_back(
					new Enemies::Enemy(
						GetRandomValue(0, screenWidth),
						-30,
						GetRandomValue(20, 170)
					)
				);
			}
			break;

		case 9:
			for (auto i = 0; i < 20; i++)
			{
				enemies.push_back(
					new Enemies::Enemy(
						GetRandomValue(0, screenWidth),
						-30,
						GetRandomValue(70, 120)
					)
				);
			}
			break;

		default:
			std::cout << "Invalid Case Selected" << std::endl;
			break;
		}
		return enemies;
	}
}
