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

	void Collectible::show()
	{
		const auto x = this->_position.x;
		const auto y = this->_position.y;

		this->_collectible_points[0] = {x, y};
		this->_collectible_points[1] = {x + this->_base_width, y};
		this->_collectible_points[2] = {x + this->_base_width, y + this->_base_width};
		this->_collectible_points[3] = {x, y + this->_base_width};

		const Rectangle rectangle = {x, y, this->_base_width, this->_base_width};
		DrawRectanglePro(rectangle, {0, 0}, this->_angle, this->_color);
	}

	void Collectible::update()
	{
		this->_position = Utils::VectorHelpers::Add(this->_position, this->_velocity);
		this->_angle = this->_angle + 2.0f * GetFrameTime();
		this->_angle = this->_angle > 360 ? 0 : this->_angle;
	}

	bool Collectible::isOutOfScreen() const
	{
		return this->_position.y > this->_screen_height + this->_base_width;
	}

	bool Collectible::didCollectibleCollide(const float points[2]) const
	{
		// ray-casting algorithm based on
		// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html

		const auto x = points[0];
		const auto y = points[1];

		auto inside = false;
		for (auto i = 0, j = this->_collectible_points_count - 1; i < this->_collectible_points_count; j = i++)
		{
			const auto xi = this->_collectible_points[i].x;
			const auto yi = this->_collectible_points[i].y;
			const auto xj = this->_collectible_points[j].x;
			const auto yj = this->_collectible_points[j].y;

			const auto intersect = ((yi > y) != (yj > y)) &&
				(x < (xj - xi) * (y - yi) / (yj - yi) + xi);
			if (intersect) inside = !inside;
		}

		return inside;
	}
}
