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
		const int _base_width = 15;

		int _screen_height;

		Enums::CollectibleType _collectibleType;
		Color _color;
		float _angle;

	public:
		Collectible(float xPosition, float yPosition, Enums::CollectibleType collectibleType);

		void show() const;
		void update();

		bool isOutOfScreen() const;
		bool didCollectibleCollide(Vector2 point) const;
	};
}
