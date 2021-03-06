#pragma once

#include "raylib.h"
#include "Particle.h"
#include <vector>

namespace Common
{
	class Explosion
	{
	private:
		Vector2 _position;
		Vector2 _gravity;
		float _radius;

		Color _color;
		std::vector<Particle*> _particles;

		void explode();

	public:
		Explosion(float xPosition, float yPosition, float radius);

		void show();
		void update();

		bool explosionComplete() const;
	};
}
