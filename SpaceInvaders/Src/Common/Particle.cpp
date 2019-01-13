#include "Particle.h"
#include "../Utils/VectorHelpers.h"
#include "../Utils/ExtensionFunctions.h"

namespace Common
{
	Particle::Particle(float x, float y, const Color color, const float radius)
	{
		this->_position = {x, y};
		this->_velocity = Utils::VectorHelpers::Random2D();
		this->_velocity = Utils::VectorHelpers::Mult(this->_velocity, GetRandomValue(0, 70));
		this->_acceleration = {0, 0};

		this->_alpha = 1;
		this->_color = color;
		this->_radius = radius;
	}

	void Particle::show()
	{
		const auto fadeColor = Fade(this->_color, this->_alpha);
		const auto mappedRadius = Utils::ExtensionFunctions::Map(this->_alpha, 0, 1,
		                                                         0, this->_radius);

		DrawCircle(this->_position.x, this->_position.y, mappedRadius, fadeColor);

		this->_alpha -= 0.05f * GetFrameTime();
	}

	void Particle::update()
	{
		this->_velocity = Utils::VectorHelpers::Mult(this->_velocity, 0.5f);
		this->_velocity = Utils::VectorHelpers::Add(this->_velocity, this->_acceleration);

		this->_position = Utils::VectorHelpers::Add(this->_position, this->_velocity);
		this->_acceleration = Utils::VectorHelpers::Mult(this->_acceleration, 0);
	}

	void Particle::applyForce(const Vector2 force)
	{
		this->_acceleration = Utils::VectorHelpers::Add(this->_acceleration, force);
	}

	bool Particle::isVisible() const
	{
		return this->_alpha > 0;
	}
}
