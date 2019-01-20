#pragma once
#include "raylib.h"
#include "../Enums/Enums.h"

namespace Common
{
	class Collectible
	{
	private:
		Vector2 _position;
		Vector2 _velocity;

		const int _speed = 67;
		const int _rotation_speed = 20;
		const int _base_width = 15;

		int _screen_height;

		Enums::BulletType _bulletType;
		Color _color;
		float _angle;

	public:
		Collectible(float xPosition, float yPosition, Enums::BulletType bulletType);

		void show() const;
		void update();

		Vector2 getPosition() const;
		Enums::BulletType getBulletType() const;

		bool isOutOfScreen() const;
	};
}
