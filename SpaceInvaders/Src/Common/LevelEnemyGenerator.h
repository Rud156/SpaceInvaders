#pragma once
#include <vector>
#include "../Enemies/Enemy.h"

namespace Common
{
	class LevelEnemyGenerator
	{
		static std::vector<Enemies::Enemy*> GetEnemyForLevel(int levelNumber);
	};
}
