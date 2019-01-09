#include "pch.h"
#include "Bullet.h"
#include "VectorHelpers.h"

namespace Common {
	Bullet::Bullet(float xPosition, float yPosition, int size, bool goUp, 
		Color colorValue = WHITE, float rotation = -1)
	{
		this->_go_up = goUp;
		this->_speed = this->_go_up ? -10 : 10;

		this->_base_width = size;
		this->_base_height = size * 2;

		this->color = colorValue;
		this->rotation = rotation;

		this->position = { xPosition, yPosition };
		if (this->rotation == -1)
			this->velocity = { 0, 45 };
		else {
			auto rotation = 45 - this->rotation;
			this->velocity = { -45 + rotation,45 };
		}
		this->velocity = Utils::VectorHelpers::SetMag(this->velocity, this->_speed);
	}
	void Bullet::show()
	{

	}

	void Bullet::update()
	{
	}
}