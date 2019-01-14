#include "Explosion.h"
#include "../Utils/ColorHelpers.h"

namespace Common
{
	Explosion::Explosion(float positionX, float positionY, float radius)
	{
		this->_position = {positionX, positionY};
		this->_gravity = {0, 0.2f};
		this->_radius = radius;

		const auto randomColor = GetRandomValue(0, 359);
		this->_color = Utils::ColorHelpers::HSLAToRGBA(randomColor, 100, 100);

		this->explode();
	}

	void Explosion::show()
	{
		for (auto particle : this->_particles)
			particle->show();
	}

	void Explosion::update()
	{
		for (size_t i = 0; i < this->_particles.size(); i++)
		{
			this->_particles[i]->applyForce(this->_gravity);
			this->_particles[i]->update();

			if (!this->_particles[i]->isVisible())
			{
				this->_particles.erase(this->_particles.begin() + i);
				i -= 1;
			}
		}
	}

	void Explosion::explode()
	{
		for (auto i = 0; i < 200; i++)
		{
			const auto particle = new Particle(this->_position.x, this->_position.y,
			                                   this->_color, this->_radius);
			this->_particles.push_back(particle);
		}
	}

	bool Explosion::explosionComplete() const
	{
		return this->_particles.empty();
	}
}
