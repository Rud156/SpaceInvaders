#pragma once

#include "raylib.h"
#include "../Common/Bullet.h"
#include <vector>
#include <random>

namespace Enemies
{
	class Enemy
	{
	private:
		Vector2 _position;
		float _prev_x;

		int _screen_width;
		int _screen_height;

		Vector2 _position_to_reach;
		Vector2 _velocity;
		Vector2 _acceleration;

		const int _max_speed = 167;
		const int _max_force = 5;

		const Color _color = GREEN;
		float _base_width;
		float _base_height;
		float _shooter_height;

		const int _ship_shape_points_count = 17;
		Vector2 _ship_shape_points[17];

		const int _magnitude_limit = 50;
		std::vector<Common::Bullet*> _bullets;
		const float _min_shoot_wait_time = 0.3f;
		float _current_shoot_wait_time;

		float _max_health;
		float _current_health;
		const Color _full_health_color = GREEN;
		const Color _half_health_color = YELLOW;
		const Color _zero_health_color = RED;

		std::mt19937 _gen;
		std::uniform_real_distribution<float> _dis;

		void checkTargetPointReached();
		void renderBullets();

	public:
		Enemy(float xPosition, float yPosition, float enemyBaseWidth);
		~Enemy();
		
		void show();
		void update();

		void checkAndShootIfNearPlayer(Vector2 playerPosition);
		
		bool checkDeathAndTakeDamage();
		bool isEnemyHit(const Vector2 point) const;

		Vector2 getEnemyPosition() const;
	};
}
