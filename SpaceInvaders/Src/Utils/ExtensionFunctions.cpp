#include "ExtensionFunctions.h"
#include "raylib.h"

namespace Utils
{
	float ExtensionFunctions::Map(const float from, const float fromMin, const float fromMax, const float toMin,
	                              const float toMax)
	{
		const auto fromAbs = from - fromMin;
		const auto fromMaxAbs = fromMax - fromMin;

		const auto normal = fromAbs / fromMaxAbs;

		const auto toMaxAbs = toMax - toMin;
		const auto toAbs = toMaxAbs * normal;

		const auto to = toAbs + toMin;

		return to;
	}

	float ExtensionFunctions::Lerp(const float start, const float stop, const float amount)
	{
		return amount * (stop - start) + start;
	}

	Enums::BulletType ExtensionFunctions::getRandomBulletType()
	{
		const auto randomValue = GetRandomValue(0, 1000);
		const auto normalizedRandomValue = randomValue % 3;

		switch (normalizedRandomValue)
		{
		case 0:
			return Enums::BulletType::SingleBullet;

		case 1:
			return Enums::BulletType::DoubleBullet;

		case 2:
			return Enums::BulletType::SprayBullet;

		default:
			return Enums::BulletType::SingleBullet;
		}
	}
}
