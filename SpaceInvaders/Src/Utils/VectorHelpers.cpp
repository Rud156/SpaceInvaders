#include "VectorHelpers.h"
#include <cmath>
#include <random>

namespace Utils
{
	const float VectorHelpers::_two_pi = 6.28318530717958647693f;

	float VectorHelpers::MagSq(const Vector2 vec)
	{
		const auto x = vec.x;
		const auto y = vec.y;

		return x * x + y * y;
	}

	float VectorHelpers::Mag(Vector2 vec)
	{
		return std::sqrt(VectorHelpers::MagSq(vec));
	}

	Vector2 VectorHelpers::Mult(Vector2 vec, const float factor)
	{
		vec.x *= factor;
		vec.y *= factor;

		return vec;
	}

	Vector2 VectorHelpers::Add(Vector2 vec1, const Vector2 vec2)
	{
		vec1.x += vec2.x;
		vec1.y += vec2.y;

		return vec1;
	}

	Vector2 VectorHelpers::Sub(Vector2 vec1, const Vector2 vec2)
	{
		vec1.x -= vec2.x;
		vec1.y -= vec2.y;

		return vec1;
	}

	Vector2 VectorHelpers::Div(Vector2 vec, const float factor)
	{
		if (factor == 0)
			return vec;

		vec.x /= factor;
		vec.y /= factor;

		return vec;
	}

	Vector2 VectorHelpers::Normalize(const Vector2 vec)
	{
		const float length = VectorHelpers::Mag(vec);
		return VectorHelpers::Mult(vec, 1.0 / length);
	}

	Vector2 VectorHelpers::SetMag(const Vector2 vec, const float magnitude)
	{
		const auto normalizedVector = VectorHelpers::Normalize(vec);
		return VectorHelpers::Mult(normalizedVector, magnitude);
	}

	Vector2 VectorHelpers::Limit(const Vector2 vec, const float max)
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

		const auto randomValue = dis(gen);
		return VectorHelpers::FromAngle(randomValue * VectorHelpers::_two_pi);
	}

	Vector2 VectorHelpers::FromAngle(const float angle, const float length)
	{
		return {length * cos(angle), length * sin(angle)};
	}
}
