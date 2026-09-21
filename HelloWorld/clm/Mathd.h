#ifndef CLM_MATH_D_H
#define CLM_MATH_D_H
#define CLM_MATH_D_I_H

#include "MathConst.h"

#include <cmath>

namespace clfe
{

	static constexpr MathConst<double> Constd;

	static inline double sind(double radians)
	{
		return std::sin(radians);
	}

	static inline double cosd(double radians)
	{
		return std::cos(radians);
	}

	static inline double tand(double radians)
	{
		return std::tan(radians);
	}

	static inline double asind(double value)
	{
		return std::asin(value);
	}

	static inline double acosd(double value)
	{
		return std::acos(value);
	}

	static inline double atand(double value)
	{
		return std::atan(value);
	}

	static inline double atan2d(double y, double x)
	{
		return std::atan2(y, x);
	}

	//

	static inline double constexpr absd(double value)
	{
		return value < 0.0 ? -value : value;
	}

	static inline double ceild(double value)
	{
		return std::ceil(value);
	}

	static inline double floord(double value)
	{
		return std::floor(value);
	}

	//

	static inline double powd(double value, double exponent)
	{
		return std::pow(value, exponent);
	}

	static inline double logd(double value, double base)
	{
		// Why doesn't cmath have this function?
		return std::log(value) / std::log(base);
	}

	static inline double log10d(double value)
	{
		return std::log10(value);
	}

	static inline double log2d(double value)
	{
		return std::log2(value);
	}

	static inline double lnd(double value) 
{
		return std::log(value);
	}

	static inline double expd(double exponent)
	{
		return std::exp(exponent);
	}

	//

	static inline double constexpr sqrd(double value)
	{
		return value * value;
	}

	static inline double sqrtd(double value)
	{
		return std::sqrt(value);
	}

	static inline double invSqrtd(double value)
	{
		return 1.0 / std::sqrt(value);
	}

	static inline double rootd(double value, double n)
	{
		return std::pow(value, 1.0 / n);
	}

}

#endif