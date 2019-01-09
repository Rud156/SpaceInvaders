#include "pch.h"
#include "SpaceShip.h"
#include "ExtensionFunctions.h"

namespace Player {
	SpaceShip::SpaceShip(int windowWidth, int windowHeight)
	{
		this->_window_width = windowWidth;
		this->_window_height = windowHeight;

		this->position = { (float)windowWidth / 2, (float)windowHeight - this->_base_height - 10 };
		this->velocity = { 0, 0 };

		this->_god_mode = false;
		this->_bullet_color = 0;
	}

	void SpaceShip::show()
	{
		auto bodyColor = Utils::ExtensionFunctions::Instance()->LerpColor(
			this->_zero_health_color,
			this->_space_ship_color,
			this->health / 100
		);

		auto x = this->position.x;
		auto y = this->position.y;

		this->_shape_points[0] = { x - this->_shooter_width / 2, y - this->_base_height * 2 };
		this->_shape_points[1] = { x + this->_shooter_width / 2, y - this->_base_height * 2 };
		this->_shape_points[2] = { x + this->_shooter_width / 2, y - this->_base_height * 1.5 };
		this->_shape_points[3] = { x + this->_base_width / 4, y - this->_base_height * 1.5 };
		this->_shape_points[4] = { x + this->_base_width / 4, y - this->_base_height / 2 };
		this->_shape_points[5] = { x + this->_base_width / 2, y - this->_base_height / 2 };
		this->_shape_points[6] = { x + this->_base_width / 2, y + this->_base_height / 2 };
		this->_shape_points[7] = { x - this->_base_width / 2, y + this->_base_height / 2 };
		this->_shape_points[8] = { x - this->_base_width / 2, y - this->_base_height / 2 };
		this->_shape_points[9] = { x - this->_base_width / 4, x - y - this->_base_height / 2 };
		this->_shape_points[10] = { x - this->_base_width / 4, y - this->_base_height * 1.5 };
		this->_shape_points[11] = { x - this->_shooter_width / 2, y - this->_base_height * 1.5 };

		DrawPolyEx(this->_shape_points, 12, bodyColor);

		Color currentColor;
		if (this->health < 50)
			currentColor = Utils::ExtensionFunctions::Instance()->LerpColor(
				this->_zero_health_color,
				this->_half_health_color,
				this->health / 50
			);
		else
			currentColor = Utils::ExtensionFunctions::Instance()->LerpColor(
				this->_half_health_color,
				this->_full_health_color,
				(this->health - 50) / 50
			);

		DrawRectangle(this->_window_width / 2, this->_window_height - 7,
			this->_window_width * this->health / 100, 10);
	}

	void SpaceShip::update()
	{
		if (!IsKeyDown(KEY_SPACE) || this->_current_frame_wait_count < 0)
			this->_current_frame_wait_count = this->_min_frame_wait_count;

		// TODO: Add Bullets
	}

	void SpaceShip::moveShip()
	{
	}

	void SpaceShip::setBulletType()
	{
	}

	void SpaceShip::getBulletType()
	{
	}

	void SpaceShip::shootBullets()
	{
	}

	void SpaceShip::decreaseHealth()
	{
	}

	void SpaceShip::activateGodMode()
	{
	}

	bool SpaceShip::isDestroyed()
	{
		return false;
	}

	void SpaceShip::resetSpaceShip()
	{
	}

	bool SpaceShip::didSpaceShipCollide(float points[2])
	{
		// ray-casting algorithm based on
		// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html

		auto x = points[0];
		auto y = points[1];

		auto inside = false;
		for (int i = 0, j = 12 - 1; i < 12; j = i++) {
			auto xi = this->_shape_points[i].x,
				yi = this->_shape_points[i].y;
			auto xj = this->_shape_points[j].x,
				yj = this->_shape_points[j].y;

			auto intersect = ((yi > y) != (yj > y)) &&
				(x < (xj - xi) * (y - yi) / (yj - yi) + xi);
			if (intersect) inside = !inside;
		}

		return inside;
	}
}