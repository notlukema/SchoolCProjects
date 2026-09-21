#ifndef CLM_VECTORMATRIX_COMMON_I_H
#define CLM_VECTORMATRIX_COMMON_I_H

#include <type_traits>
#include <cstdint>
#include <concepts>

namespace clfe
{

	using msize_t = uint16_t;

	// Guarentees that all types are the same as T
	template <typename T, typename... Args>
	concept AllSame = (std::same_as<T, Args> && ...);

	// Guarentees that all types can be converted to T
	template <typename T, typename... Args>
	concept AllCompatible = (std::convertible_to<Args, T> && ...);

	// Guarentees that U can be converted to T
	template <typename T, typename U>
	concept Compatible = std::convertible_to<U, T>;

	// Guarentees that T is an arithmetic type
	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	// Guarentees that T and U are arithmetic types and that T can be converted to U
	template <typename T, typename U>
	concept Arithmetic2 = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::convertible_to<T, U>;

	// Guarentees that T and U are arithmetic types and that the result of T + U can be converted to T
	template <typename T, typename U>
	concept Arithmetic3 = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::convertible_to<decltype(static_cast<T>(0) + static_cast<U>(0)), T>;

	constexpr msize_t smax(msize_t a, msize_t b)
	{
		return (a > b) ? a : b;
	}

	constexpr msize_t smin(msize_t a, msize_t b)
	{
		return (a < b) ? a : b;
	}

}

#endif