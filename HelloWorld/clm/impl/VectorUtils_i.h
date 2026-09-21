#ifndef CLM_VECTOR_UTILS_I_H
#define CLM_VECTOR_UTILS_I_H

#include "VectorMatrixCommon_i.h"
#include "Vector_i.h"

namespace clfe
{

	// Default utilities

	template <msize_t Size, msize_t Size0, typename T> // Could try replacing Size and Size0 with one template parameter
	inline Vector<Size, T> resizeVec(const Vector<Size0, T>& vec) requires (Size == Size0)
	{
		return Vector<Size, T>(vec);
	}

	template <msize_t Size, msize_t Size0, typename T>
	Vector<Size, T> resizeVec(const Vector<Size0, T>& vec) requires (Size != Size0)
	{
		Vector<Size, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, (i < Size0) ? vec.get(i) : static_cast<T>(0));
		}
		return result;
	}

	template <typename To, msize_t Size, typename From>
		requires Compatible<From, To>
	Vector<Size, To> castVec(const Vector<Size, From>& vec)
	{
		To arr[Size];
		for (msize_t i = 0; i < Size; i++)
		{
			arr[i] = static_cast<To>(vec.get(i));
		}
		return Vector<Size, To>(arr);
	}

	// Special operations

	// vec dot
	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T>&& Arithmetic<U>
	auto vdot(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2) -> decltype(static_cast<T>(0) + static_cast<U>(0))
	{
		auto result = static_cast<decltype(static_cast<T>(0) + static_cast<U>(0))>(0);
		for (msize_t i = 0; i < Size; i++)
		{
			result += vec1.get(i) * vec2.get(i);
		}
		return result;
	}

	// vec cross
	template <msize_t Size, typename T, typename U>
		requires (Size == 3) && Arithmetic<T>&& Arithmetic<U>
	auto vcross(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		return Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>(
			vec1.get(1) * vec2.get(2) - vec1.get(2) * vec2.get(1),
			vec1.get(2) * vec2.get(0) - vec1.get(0) * vec2.get(2),
			vec1.get(0) * vec2.get(1) - vec1.get(1) * vec2.get(0)
		);
	}

}

#endif