#pragma once

#include "raylib.h"

namespace Common
{
	class Bullet
	{
	private:
		bool _go_up;
		int _speed;
		float _base_width;
		float _base_height;

		int _screen_width;
		int _screen_height;

		Color _color;
		float _rotation;

		Vector2 _position;
		Vector2 _velocity;

	public:
		Bullet(float xPosition, float yPosition, float size, bool goUp,
		       Color colorValue = WHITE, float rotation = -1);

		void show() const;
		void update();
		Vector2 getPosition() const;
		bool isOutOfScreen() const;
	};
}
