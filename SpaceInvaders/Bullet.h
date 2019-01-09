#pragma once

#include "raylib.h"

namespace Common {
	class Bullet
	{
	private:
		bool _go_up;
		int _speed;
		float _base_width;
		float _base_height;

		Color color;
		float rotation;

		Vector2 position;
		Vector2 velocity;

	public:
		Bullet(float xPosition, float yPosition, int size, bool goUp, 
			Color colorValue = WHITE, float rotation = -1);
		void show();
		void update();
	};
}