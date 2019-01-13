#include "Enemy.h"

namespace Enemies {
	Enemy::Enemy(float xPosition, float yPosition, float enemyBaseWidth)
	{
		this->_position = { xPosition, yPosition };
		this->_prev_x = this->_position.x;

		this->_screen_width = GetScreenWidth();
		this->_screen_height = GetScreenHeight();

		this->_position_to_reach = { float(GetRandomValue(0, this->_screen_width)),
			float(GetRandomValue(0, this->_screen_height / 2)) };
		this->_velocity = { 0, 0 };
		this->_acceleration = { 0, 0 };

		this->_base_width = enemyBaseWidth;

	}

	void Enemy::show()
	{
	}

	void Enemy::update()
	{
	}

	void Enemy::checkArrival()
	{
	}

	void Enemy::renderBullets()
	{
	}

	void Enemy::checkAndShootIfNearPlayer()
	{
	}

	bool Enemy::checkAndTakeDamage()
	{
		return false;
	}

	bool Enemy::isEnemyHit()
	{
		return false;
	}
}
