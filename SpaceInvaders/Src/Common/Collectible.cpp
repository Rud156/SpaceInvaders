#include "Collectible.h"
#include "../Utils/VectorHelpers.h"
#include "../Utils/ColorHelpers.h"

namespace Common
{
	Collectible::Collectible(float xPosition, float yPosition, Enums::BulletType bulletType)
	{
		this->_screen_height = GetScreenHeight();

		this->_position = {xPosition, yPosition};
		this->_velocity = {0, static_cast<float>(_screen_height)};
		this->_velocity = Utils::VectorHelpers::SetMag(this->_velocity, this->_speed);

		this->_angle = 0;

		this->_bulletType = bulletType;
		this->_color = Utils::ColorHelpers::CollectibleTypeToColor(bulletType);
	}

	void Collectible::show() const
	{
		const auto x = this->_position.x;
		const auto y = this->_position.y;

		const Rectangle rectangle = {x, y, this->_base_width, this->_base_width};
		DrawRectanglePro(rectangle, {this->_base_width / 2.0f, this->_base_width / 2.0f},
		                 this->_angle, this->_color);
	}

	void Collectible::update()
	{
		this->_position = Utils::VectorHelpers::Add(this->_position,
		                                            Utils::VectorHelpers::Mult(this->_velocity, GetFrameTime()));

		this->_angle = this->_angle + this->_rotation_speed * GetFrameTime();
		this->_angle = this->_angle > 360 ? 0 : this->_angle;
	}

	bool Collectible::isOutOfScreen() const
	{
		return this->_position.y > this->_screen_height + this->_base_width;
	}

	Vector2 Collectible::getPosition() const
	{
		return this->_position;
	}

	Enums::BulletType Collectible::getBulletType() const
	{
		return this->_bulletType;
	}
}
