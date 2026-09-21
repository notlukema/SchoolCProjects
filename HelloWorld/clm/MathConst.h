#ifndef CLM_MATH_CONST_H
#define CLM_MATH_CONST_H
#define CLM_MATH_CONST_I_H

namespace clfe
{

	template <typename T>
	struct MathConst
	{

		static constexpr T Pi = static_cast<T>(3.14159265358979323846);
		//static constexpr T TwoPi = static_cast<T>(6.28318530717958647692);
		//static constexpr T HalfPi = static_cast<T>(1.57079632679489661923);
		static constexpr T E = static_cast<T>(2.71828182845904523536);
		//static constexpr T GoldenRatio = static_cast<T>(1.618033988749895);
		//static constexpr T Sqrt2 = static_cast<T>(1.41421356237309504880);
		//static constexpr T Sqrt3 = static_cast<T>(1.73205080756887729353);
		//static constexpr T InvSqrt2 = static_cast<T>(0.70710678118654752440);
		//static constexpr T InvSqrt3 = static_cast<T>(0.57735026918962576450);
		//static constexpr T Ln2 = static_cast<T>(0.69314718055994530942);
		//static constexpr T Ln10 = static_cast<T>(2.30258509299404568402);
		//static constexpr T InvLn2 = static_cast<T>(1.44269504088896340736);
		//static constexpr T InvLn10 = static_cast<T>(0.43429448190325182765);

		static constexpr int factorialp(int num)
		{
			if (num > 1) {
				return num * factorial(num - 1);
			}
			return 1;
		}

		static constexpr T factorial(int num)
		{
			return static_cast<T>(factorialp(num));
		}

		static constexpr T invFactorial(int num)
		{
			return 1 / factorial(num);
		}

	};

}

#endif