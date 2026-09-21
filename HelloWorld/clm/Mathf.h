#ifndef CLM_MATH_F_H
#define CLM_MATH_F_H
#define CLM_MATH_F_I_H

#include "MathConst.h"

#include <cmath>

namespace clfe
{

	static constexpr MathConst<float> Constf;

	static inline float sinf(float radians)
	{
		return std::sinf(radians);
	}

	static inline float cosf(float radians)
	{
		return std::cosf(radians);
	}
	
	static inline float tanf(float radians)
	{
		return std::tanf(radians);
	}

	static inline float asinf(float value)
	{
		return std::asinf(value);
	}

	static inline float acosf(float value)
	{
		return std::acosf(value);
	}

	static inline float atanf(float value)
	{
		return std::atanf(value);
	}

	static inline float atan2f(float y, float x)
	{
		return std::atan2f(y, x);
	}

	//

	static inline float constexpr absf(float value)
	{
		return value < 0 ? -value : value;
	}

	static inline float ceilf(float value)
	{
		return std::ceilf(value);
	}

	static inline float floorf(float value)
	{
		return std::floor(value);
	}

	//

	static inline float powf(float value, float exponent)
	{
		return std::powf(value, exponent);
	}

	static inline float logf(float value, float base)
	{
		// Why doesn't cmath have this function?
		return std::logf(value) / std::logf(base);
	}

	static inline float log10f(float value)
	{
		return std::log10f(value);
	}

	static inline float log2f(float value)
	{
		return std::log2f(value);
	}

	static inline float lnf(float value)
	{
		return std::logf(value);
	}

	static inline float expf(float exponent)
	{
		return std::expf(exponent);
	}

	//

	static inline float constexpr sqrf(float value)
	{
		return value * value;
	}

	static inline float sqrtf(float value)
	{
		return std::sqrtf(value);
	}

	static inline float invSqrtf(float value)
	{
		return 1.0f / std::sqrtf(value);
	}

	static inline float rootf(float value, float n)
	{
		return std::powf(value, 1.0f / n);
	}

}

#endif