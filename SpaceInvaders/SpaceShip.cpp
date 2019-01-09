#include "pch.h"
#include "SpaceShip.h"
#include "ExtensionFunctions.h"
#include "VectorHelpers.h"

namespace Player {
	SpaceShip::SpaceShip(int windowWidth, int windowHeight)
	{
		this->_window_width = windowWidth;
		this->_window_height = windowHeight;

		this->position = { (float)windowWidth / 2, (float)windowHeight - this->_base_height - 7 };
		this->velocity = { 0, 0 };

		this->_god_mode = false;
		this->_bullet_type = Enums::BulletType::SingleBullet;
	}

	void SpaceShip::show()
	{
		auto bodyColor = Utils::ExtensionFunctions::LerpColor(
			this->_zero_health_color,
			this->_space_ship_color,
			this->health / 100.0
		);

		auto x = this->position.x;
		auto y = this->position.y;

		this->_ship_points[11] = { x - this->_shooter_width / 2, y - this->_base_height * 2 };
		this->_ship_points[10] = { x + this->_shooter_width / 2, y - this->_base_height * 2 };
		this->_ship_points[9] = { x + this->_shooter_width / 2, y - this->_base_height * 1.5f };
		this->_ship_points[8] = { x + this->_base_width / 4, y - this->_base_height * 1.5f };
		this->_ship_points[7] = { x + this->_base_width / 4, y - this->_base_height / 2 };
		this->_ship_points[6] = { x + this->_base_width / 2, y - this->_base_height / 2 };
		this->_ship_points[5] = { x + this->_base_width / 2, y + this->_base_height / 2 };
		this->_ship_points[4] = { x - this->_base_width / 2, y + this->_base_height / 2 };
		this->_ship_points[3] = { x - this->_base_width / 2, y - this->_base_height / 2 };
		this->_ship_points[2] = { x - this->_base_width / 4, y - this->_base_height / 2 };
		this->_ship_points[1] = { x - this->_base_width / 4, y - this->_base_height * 1.5f };
		this->_ship_points[0] = { x - this->_shooter_width / 2, y - this->_base_height * 1.5f };

		DrawPolyExLines(this->_ship_points, this->_ship_points_count, bodyColor);

		Color currentColor;
		if (this->health < 50)
			currentColor = Utils::ExtensionFunctions::LerpColor(
				this->_zero_health_color,
				this->_half_health_color,
				this->health / 50
			);
		else
			currentColor = Utils::ExtensionFunctions::LerpColor(
				this->_half_health_color,
				this->_full_health_color,
				(this->health - 50) / 50
			);

		DrawRectangle(0, this->_window_height - 7,
			this->_window_width * this->health / 100, 10, currentColor);
	}

	void SpaceShip::update()
	{
		if (!IsKeyDown(KEY_SPACE) || this->_current_frame_wait_count < 0)
			this->_current_frame_wait_count = this->_min_frame_wait_count;

		if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT))
		{
			// Do Nothing When Both Keys Are Pressed
		}
		else if (IsKeyDown(KEY_LEFT))
			this->moveShip(Enums::Direction::Left);
		else if (IsKeyDown(KEY_RIGHT))
			this->moveShip(Enums::Direction::Right);
		else if (IsKeyDown(KEY_SPACE))
			this->shootBullets();

		// TODO: Add Bullets
	}

	void SpaceShip::moveShip(Enums::Direction direction)
	{
		if (this->position.x < this->_base_width / 2)
			this->position.x = this->_base_width / 2 + 1;

		if (this->position.x > this->_window_width - this->_base_width / 2)
			this->position.x = this->_window_width - this->_base_width / 2 - 1;

		this->velocity = { (float)this->_window_width, 0 };
		if (direction == Enums::Direction::Left)
			this->velocity = Utils::VectorHelpers::SetMag(this->velocity, -this->speed);
		else
			this->velocity = Utils::VectorHelpers::SetMag(this->velocity, this->speed);

		this->position = Utils::VectorHelpers::Add(this->position, this->velocity);
	}

	void SpaceShip::setBulletType(Enums::BulletType bulletType)
	{
		this->_bullet_type = bulletType;
	}

	void SpaceShip::getBullet()
	{
	}

	void SpaceShip::shootBullets()
	{
	}

	void SpaceShip::decreaseHealth(float amount)
	{
		if (!this->_god_mode)
			this->health -= amount;
	}

	void SpaceShip::activateGodMode()
	{
		this->_god_mode = true;
	}

	bool SpaceShip::isDestroyed()
	{
		if (this->health <= 0) {
			this->health = 0;
			return true;
		}
		else {
			return false;
		}
	}

	void SpaceShip::resetSpaceShip()
	{
		// TODO: Reset Bullets Here
		this->_current_frame_wait_count = this->_min_frame_wait_count;
		this->health = 100;
		this->_god_mode = false;
		this->_bullet_type = Enums::BulletType::SingleBullet;
	}

	bool SpaceShip::didSpaceShipCollide(float points[2])
	{
		// ray-casting algorithm based on
		// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html

		auto x = points[0];
		auto y = points[1];

		auto inside = false;
		for (int i = 0, j = this->_ship_points_count - 1; i < this->_ship_points_count; j = i++) {
			auto xi = this->_ship_points[i].x,
				yi = this->_ship_points[i].y;
			auto xj = this->_ship_points[j].x,
				yj = this->_ship_points[j].y;

			auto intersect = ((yi > y) != (yj > y)) &&
				(x < (xj - xi) * (y - yi) / (yj - yi) + xi);
			if (intersect) inside = !inside;
		}

		return inside;
	}
}