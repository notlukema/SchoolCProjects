#ifndef CLM_MATH_H
#define CLM_MATH_H
#define CLM_MATH_I_H

#include "Mathf.h"
#include "Mathd.h"

namespace clfe
{

	static inline float sin(float radians)
	{
		return sinf(radians);
	}

	static inline double sin(double radians)
	{
		return sind(radians);
	}

	static inline float cos(float radians)
	{
		return cosf(radians);
	}

	static inline double cos(double radians)
	{
		return cosd(radians);
	}

	static inline float tan(float radians)
	{
		return tanf(radians);
	}

	static inline double tan(double radians)
	{
		return tand(radians);
	}

	static inline float asin(float value)
	{
		return asinf(value);
	}

	static inline double asin(double value)
	{
		return asind(value);
	}

	static inline float acos(float value)
	{
		return acosf(value);
	}

	static inline double acos(double value)
	{
		return acosd(value);
	}

	static inline float atan(float value)
	{
		return atanf(value);
	}

	static inline double atan(double value)
	{
		return atand(value);
	}

	static inline float atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	static inline double atan2(double y, double x)
	{
		return atan2d(y, x);
	}

	//

	static inline float constexpr abs(float value)
	{
		return absf(value);
	}

	static inline double constexpr abs(double value)
	{
		return absd(value);
	}

	static inline float ceil(float value)
	{
		return ceilf(value);
	}

	static inline double ceil(double value)
	{
		return ceild(value);
	}

	static inline float floor(float value)
	{
		return floorf(value);
	}

	static inline double floor(double value)
	{
		return floord(value);
	}

	//

	static inline float pow(float value, float exponent)
	{
		return powf(value, exponent);
	}

	static inline double pow(double value, double exponent)
	{
		return powd(value, exponent);
	}

	static inline float log(float value, float base)
	{
		return logf(value, base);
	}

	static inline double log(double value, double base)
	{
		return logd(value, base);
	}

	static inline float log10(float value)
	{
		return log10f(value);
	}

	static inline double log10(double value)
	{
		return log10d(value);
	}

	static inline float log2(float value)
	{
		return log2f(value);
	}

	static inline double log2(double value)
	{
		return log2d(value);
	}

	static inline float ln(float value)
	{
		return lnf(value);
	}

	static inline double ln(double value)
	{
		return lnd(value);
	}

	static inline float exp(float exponent)
	{
		return expf(exponent);
	}

	static inline double exp(double exponent)
	{
		return expd(exponent);
	}

	//

	static inline float constexpr sqr(float value)
	{
		return sqrf(value);
	}

	static inline double constexpr sqr(double value)
	{
		return sqrd(value);
	}

	static inline float sqrt(float value)
	{
		return sqrtf(value);
	}

	static inline double sqrt(double value)
	{
		return sqrtd(value);
	}

	static inline float invSqrt(float value)
	{
		return invSqrtf(value);
	}

	static inline double invSqrt(double value)
	{
		return invSqrtd(value);
	}

	static inline float root(float value, float n)
	{
		return rootf(value, n);
	}

	static inline double root(double value, double n)
	{
		return rootd(value, n);
	}

}

#endif