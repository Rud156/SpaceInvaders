#pragma once
#include "raylib.h"

namespace Utils {
	class VectorHelpers
	{
	public:
		static float MagSq(Vector2 vec);
		static float Mag(Vector2 vec);

		static Vector2 Mult(Vector2 vec, float factor);
		static Vector2 Add(Vector2 vec1, Vector2 vec2);

		static Vector2 Normalize(Vector2 vec);
		static Vector2 SetMag(Vector2 vec, float magnitude);
	};
}