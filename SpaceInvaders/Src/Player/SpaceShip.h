#pragma once

#include "raylib.h"
#include "../Enemies/Enemy.h"
#include "../Enums/Enums.h"
#include "../Common/Bullet.h"
#include <vector>

namespace Enemies
{
	class Enemy;
}

namespace Player
{
	class SpaceShip
	{
	private:
		int _window_width;
		int _window_height;

		const float _base_width = 70;
		const float _base_height = this->_base_width / 5;
		const float _shooter_width = this->_base_width / 10;

		const int _ship_points_count = 12;
		Vector2 _ship_points[12];

		std::vector<Common::Bullet*> _bullets;
		const float _min_shoot_wait_time = 0.1f;
		float _current_shoot_wait_time = this->_min_shoot_wait_time;

		Vector2 _position;
		Vector2 _velocity;

		const int _speed = 500;
		const int _max_health = 200;
		float _health = _max_health;

		Sound _shoot_sound;

		const Color _full_health_color = DARKGREEN;
		const Color _half_health_color = YELLOW;
		const Color _zero_health_color = RED;
		const Color _space_ship_color = SKYBLUE;

		bool _god_mode;
		const char* _god_mode_text = "God Mode On!!!";
		Enums::BulletType _bullet_type;

		void moveShip(Enums::Direction direction);
		std::vector<Common::Bullet*> getBullets() const;
		void shootBullets();

		void activateGodMode();

	public:

		SpaceShip();
		~SpaceShip();

		void show();
		void update();

		bool decreaseHealthAndCheckDeath(float amount);
		void resetSpaceShip();

		void setBulletType(Enums::BulletType bulletType);

		void checkEnemyCollisionWithBullet(Enemies::Enemy* enemy, int enemyIndex);
		bool didSpaceShipCollide(const Vector2 point) const;
		Vector2 getSpaceShipPosition() const;
	};
}
