#include "VectorHelpers.h"
#include <cmath>

namespace Utils
{
	float VectorHelpers::MagSq(Vector2 vec)
	{
		float x = vec.x;
		float y = vec.y;

		return x * x + y * y;
	}

	float VectorHelpers::Mag(Vector2 vec)
	{
		return std::sqrt(VectorHelpers::MagSq(vec));
	}

	Vector2 VectorHelpers::Mult(Vector2 vec, float factor)
	{
		vec.x *= factor;
		vec.y *= factor;

		return vec;
	}

	Vector2 VectorHelpers::Add(Vector2 vec1, Vector2 vec2)
	{
		vec1.x += vec2.x;
		vec1.y += vec2.y;

		return vec1;
	}

	Vector2 VectorHelpers::Normalize(Vector2 vec)
	{
		const float length = VectorHelpers::Mag(vec);
		return VectorHelpers::Mult(vec, 1.0 / length);
	}

	Vector2 VectorHelpers::SetMag(Vector2 vec, float magnitude)
	{
		const Vector2 normalizedVector = VectorHelpers::Normalize(vec);
		return VectorHelpers::Mult(normalizedVector, magnitude);
	}
}
