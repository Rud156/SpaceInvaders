#pragma once

#include "../Enums/Enums.h"

namespace Utils
{
	class ExtensionFunctions
	{
	public:
		static float Map(float from, float fromMin, float fromMax, float toMin, float toMax);
		static float Lerp(float start, float stop, float amount);

		static const char* FormatFloatToStringInt(float number);

		static Enums::BulletType getRandomBulletType();
	};
}
