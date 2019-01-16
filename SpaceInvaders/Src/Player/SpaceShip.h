#pragma once

#include "raylib.h"
#include "../Enums/Enums.h"
#include "../Common/Bullet.h"

#include <vector>

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
		float _health = 100;

		const Color _full_health_color = DARKGREEN;
		const Color _half_health_color = YELLOW;
		const Color _zero_health_color = RED;
		const Color _space_ship_color = SKYBLUE;

		bool _god_mode;
		Enums::BulletType _bullet_type;

		void moveShip(Enums::Direction direction);
		void setBulletType(Enums::BulletType bulletType);
		std::vector<Common::Bullet*> getBullets() const;
		void shootBullets();

		void activateGodMode();

	public:

		SpaceShip();

		void show();
		void update();

		void decreaseHealth(float amount);
		bool isDestroyed();
		void resetSpaceShip();

		bool didSpaceShipCollide(const Vector2 point) const;
		Vector2 getSpaceShipPosition() const;
	};
}
