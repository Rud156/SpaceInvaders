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

		const int _max_speed = 5;
		const int _max_force = 5;

		const Color _color = GREEN;
		float _base_width;
		float _base_height;
		float _shooter_height;

		const int _ship_shape_points_count = 12;
		Vector2 _ship_shape_points[16];

		const int _magnitude_limit = 50;
		std::vector<Common::Bullet*> _bullets;
		const float _min_shoot_wait_time = 0.1f;
		float _current_shoot_wait_time;

		float _max_health;
		float _current_health;
		const Color _full_health_color = GREEN;
		const Color _half_health_color = YELLOW;
		const Color _zero_health_color = RED;

		std::mt19937 _gen;
		std::uniform_real_distribution<float> _dis;

	public:
		Enemy(float xPosition, float yPosition, float enemyBaseWidth);
		void show();
		void update();
		void checkArrival();

		void renderBullets();
		void checkAndShootIfNearPlayer(Vector2 playerPosition);

		bool checkAndTakeDamage();
		bool isEnemyHit(const float points[2]) const;
	};
}
