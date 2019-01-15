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

		const int _speed = 2;
		const int _base_width = 15;

		const int _collectible_points_count = 4;
		Vector2 _collectible_points[4];

		int _screen_height;

		Enums::CollectibleType _collectibleType;
		Color _color;
		float _angle;

	public:
		Collectible(float xPosition, float yPosition, Enums::CollectibleType collectibleType);
		
		void show();
		void update();

		bool isOutOfScreen() const;
		bool didCollectibleCollide(const float points[2]) const;
	};
}
