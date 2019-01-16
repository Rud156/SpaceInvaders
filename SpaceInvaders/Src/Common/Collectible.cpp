#include "Collectible.h"
#include "../Utils/VectorHelpers.h"
#include "../Utils/ColorHelpers.h"

namespace Common
{
	Collectible::Collectible(float xPosition, float yPosition, Enums::CollectibleType collectibleType)
	{
		this->_screen_height = GetScreenHeight();

		this->_position = {xPosition, yPosition};
		this->_velocity = {0, float(_screen_height)};
		this->_velocity = Utils::VectorHelpers::SetMag(this->_velocity, this->_speed);

		this->_angle = 0;

		this->_collectibleType = collectibleType;
		this->_color = Utils::ColorHelpers::CollectibleTypeToColor(collectibleType);
	}

	void Collectible::show() const
	{
		const auto x = this->_position.x;
		const auto y = this->_position.y;

		const Rectangle rectangle = {x, y, this->_base_width, this->_base_width};
		DrawRectanglePro(rectangle, {0, 0}, this->_angle, this->_color);
	}

	void Collectible::update()
	{
		this->_position = Utils::VectorHelpers::Add(this->_position,
		                                            Utils::VectorHelpers::Mult(this->_velocity, GetFrameTime()));

		this->_angle = this->_angle + 2.0f * GetFrameTime();
		this->_angle = this->_angle > 360 ? 0 : this->_angle;
	}

	bool Collectible::isOutOfScreen() const
	{
		return this->_position.y > this->_screen_height + this->_base_width;
	}

	bool Collectible::didCollectibleCollide(const Vector2 point) const
	{
		const auto x = this->_position.x;
		const auto y = this->_position.y;

		const Rectangle rectangle = {x, y, this->_base_width, this->_base_width};
		return CheckCollisionPointRec(point, rectangle);
	}
}
