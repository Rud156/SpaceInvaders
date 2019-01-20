#pragma once

#include "../Enums/Enums.h"
#include <string>

namespace Utils
{
	class ExtensionFunctions
	{
	public:
		static float Map(float from, float fromMin, float fromMax, float toMin, float toMax);
		static float Lerp(float start, float stop, float amount);

		static std::string FormatFloatToStringInt(float number);

		static Enums::BulletType getRandomBulletType();
	};
}
