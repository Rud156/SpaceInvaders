#include "VectorHelpers.h"
#include <cmath>
#include <random>

namespace Utils
{
	const float VectorHelpers::_two_pi = 6.28318530717958647693f;

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

	Vector2 VectorHelpers::Sub(Vector2 vec1, Vector2 vec2)
	{
		vec1.x -= vec2.x;
		vec1.y -= vec2.y;

		return vec1;
	}

	Vector2 VectorHelpers::Div(Vector2 vec, float factor)
	{
		vec.x /= factor;
		vec.y *= factor;

		return vec;
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

	Vector2 VectorHelpers::Limit(Vector2 vec, float max)
	{
		const auto magSq = VectorHelpers::MagSq(vec);
		if (magSq > max * max)
			return VectorHelpers::Div(vec, sqrt(magSq));

		return vec;
	}

	Vector2 VectorHelpers::Random2D()
	{
		std::random_device rnd;
		std::mt19937 gen(rnd());
		const std::uniform_real_distribution<float> dis(0, 1);

		const float randomValue = dis(gen);
		return VectorHelpers::FromAngle(randomValue * VectorHelpers::_two_pi);
	}

	Vector2 VectorHelpers::FromAngle(float angle, float length)
	{
		return {length * cos(angle), length * sin(angle)};
	}
}
