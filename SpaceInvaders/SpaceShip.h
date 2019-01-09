#pragma once

#include "raylib.h"
#include "Enums.h"
#include "Bullet.h"

#include <vector>

namespace Player {
	class SpaceShip
	{
	private:
		int _window_width;
		int _window_height;

		const int _base_width = 70;
		const int _base_height = this->_base_width / 5;
		const int _shooter_width = this->_base_width / 10;

		const int _ship_points_count = 12;
		Vector2 _ship_points[12];

		std::vector<Common::Bullet*> _bullets;
		const int _min_frame_wait_count = 7;
		int _current_frame_wait_count = this->_min_frame_wait_count;

		Vector2 _position;
		Vector2 _velocity;

		const int _speed = 15;
		float _health = 100;

		const Color _full_health_color = DARKGREEN;
		const Color _half_health_color = YELLOW;
		const Color _zero_health_color = RED;
		const Color _space_ship_color = SKYBLUE;

		bool _god_mode;
		Enums::BulletType _bullet_type;

	public:

		SpaceShip(int windowWidth, int windowHeight);

		void show();
		void update();

		void moveShip(Enums::Direction direction);
		void setBulletType(Enums::BulletType bulletType);
		std::vector<Common::Bullet*> getBullets(); // TODO: Change to return bullet
		void shootBullets();

		void decreaseHealth(float amount);
		void activateGodMode();

		bool isDestroyed();
		void resetSpaceShip();

		bool didSpaceShipCollide(float points[2]);
	};
}