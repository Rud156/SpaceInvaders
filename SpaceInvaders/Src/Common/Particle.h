#pragma once

#include "raylib.h"

namespace Common
{
	class Particle
	{
	private:
		Vector2 _position;
		Vector2 _velocity;
		Vector2 _acceleration;

		float _alpha;
		Color _color;
		float _radius;

	public:
		Particle(float x, float y, Color color, float radius);

		void show() const;
		void update();

		void applyForce(Vector2 force);
		bool isVisible() const;
	};
}
