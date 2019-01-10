#include "pch.h"
#include "Bullet.h"
#include "../Utils/VectorHelpers.h"

namespace Common {
	Bullet::Bullet(float xPosition, float yPosition, int size, bool goUp,
		Color colorValue, float rotation)
	{
		this->_go_up = goUp;
		this->_speed = this->_go_up ? -10 : 10;

		this->_screen_width = GetScreenWidth();
		this->_screen_height = GetScreenHeight();

		this->_base_width = size;
		this->_base_height = size * 2;

		this->_color = colorValue;
		this->_rotation = rotation;

		this->_position = { xPosition, yPosition };
		if (this->_rotation == -1)
			this->_velocity = { 0, 45 };
		else {
			auto rotation = 45 - this->_rotation;
			this->_velocity = { -45 + rotation, 45 };
		}
		this->_velocity = Utils::VectorHelpers::SetMag(this->_velocity, this->_speed);
	}
	void Bullet::show()
	{
		auto x = this->_position.x;
		auto y = this->_position.y;

		Rectangle rect = { x, y - this->_base_height, this->_base_width, this->_base_height };
		DrawRectanglePro(rect, { 0, 0 }, this->_rotation, this->_color);
	}

	void Bullet::update()
	{
		this->_position = Utils::VectorHelpers::Add(this->_position, this->_velocity);
	}

	bool Bullet::isOutOfScreen()
	{
		return this->_position.y < -this->_base_height || this->_position.x < -this->_base_height ||
			this->_position.x > this->_screen_width + this->_base_height ||
			this->_position.y > this->_screen_height + this->_base_height;
	}
}