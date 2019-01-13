#pragma once
#include "raylib.h"

namespace Utils
{
	class VectorHelpers
	{
	private:
		const static float _two_pi;

	public:
		static float MagSq(Vector2 vec);
		static float Mag(Vector2 vec);

		static Vector2 Add(Vector2 vec1, Vector2 vec2);
		static Vector2 Sub(Vector2 vec1, Vector2 vec2);
		static Vector2 Mult(Vector2 vec, float factor);
		static Vector2 Div(Vector2 vec, float factor);

		static Vector2 Normalize(Vector2 vec);
		static Vector2 SetMag(Vector2 vec, float magnitude);
		static Vector2 Limit(Vector2 vec, float max);

		static Vector2 Random2D();
		static Vector2 FromAngle(float angle, float length = 1);
	};
}
