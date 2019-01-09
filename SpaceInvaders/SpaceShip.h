#pragma once

#include "raylib.h"

namespace Player {
	class SpaceShip
	{
	private:
		int _window_width;
		int _window_height;

		const int _base_width = 70;
		const int _base_height = this->_base_width / 5;
		const int _shooter_width = this->_base_width / 10;
		Vector2 _shape_points[12];


		const int _min_frame_wait_count = 7;
		int _current_frame_wait_count = this->_min_frame_wait_count;

		Vector2 position;
		Vector2 velocity;

		const int speed = 15;
		const int health = 100;

		const Color _full_health_color = DARKGREEN;
		const Color _half_health_color = YELLOW;
		const Color _zero_health_color = RED;
		const Color _space_ship_color = SKYBLUE;

		bool _god_mode;
		int _bullet_color;

	public:
		
		SpaceShip(int windowWidth, int windowHeight);
		
		void show();
		void update();
		
		void moveShip(Direction direction);
		void setBulletType();
		void getBulletType(); // TODO: Change to return bullet
		void shootBullets();

		void decreaseHealth();
		void activateGodMode();
		
		bool isDestroyed();
		void resetSpaceShip();

		bool didSpaceShipCollide(float points[2]);
	};
}