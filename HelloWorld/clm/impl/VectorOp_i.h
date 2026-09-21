#ifndef CLFE_VECTOR_OP_I_H
#define CLFE_VECTOR_OP_I_H

#include "VectorMatrixCommon_i.h"
#include "Vector_i.h"

namespace clfe
{

	//
	// Inter-vector operations
	//

	// Addition

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) + vec2.get(i));
		}
		return result;
	}

	template <msize_t Size1, msize_t Size2, typename T, typename U>
		requires (Size1 != Size2) && Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size1, T>& vec1, const Vector<Size2, U>& vec2) -> Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < smax(Size1, Size2); i++)
		{
			result.setAt(i,
				((i < Size1) ? vec1.get(i) : static_cast<T>(0)) +
				((i < Size2) ? vec2.get(i) : static_cast<U>(0))
			);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator+=(Vector<Size, T>& vec1, const Vector<Size, U>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) + vec2.get(i)));
		}
		return vec1;
	}

	// Subtraction

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) - vec2.get(i));
		}
		return result;
	}

	template <msize_t Size1, msize_t Size2, typename T, typename U>
		requires (Size1 != Size2) && Arithmetic<T> && Arithmetic<U>
	auto operator-(const Vector<Size1, T>& vec1, const Vector<Size2, U>& vec2) -> Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < smax(Size1, Size2); i++)
		{
			result.setAt(i,
				((i < Size1) ? vec1.get(i) : static_cast<T>(0)) -
				((i < Size2) ? vec2.get(i) : static_cast<U>(0))
			);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator-=(Vector<Size, T>& vec1, const Vector<Size, U>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) - vec2.get(i)));
		}
		return vec1;
	}

	// Multiplication

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator*(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) * vec2.get(i));
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator*=(Vector<Size, T>& vec1, const Vector<Size, U>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) * vec2.get(i)));
		}
		return vec1;
	}

	// Division

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator/(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) / vec2.get(i));
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator/=(Vector<Size, T>& vec1, const Vector<Size, U>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) / vec2.get(i)));
		}
		return vec1;
	}

	//
	// Scalar operations
	//

	// Addition

	/* Works with different types, but has code bloat and is quite ambiguous
	
	template <int Size, typename T, typename U, typename P>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size, T, P>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>();
		for (int i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) + scalar);
		}
		return result;
	}
	*/

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size, T>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) + scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator+=(Vector<Size, T>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) + scalar));
		}
		return vec;
	}

	// Subtraction

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Vector<Size, T>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) - scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator-=(Vector<Size, T>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) - scalar));
		}
		return vec;
	}

	// Multiplication

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator*(const Vector<Size, T>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) * scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator*=(Vector<Size, T>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) * scalar));
		}
		return vec;
	}

	// Division

	template <msize_t Size, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator/(const Vector<Size, T>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) / scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U>
		requires Arithmetic3<T, U>
	Vector<Size, T>& operator/=(Vector<Size, T>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) / scalar));
		}
		return vec;
	}

	//
	// Comparisons
	//

	template <msize_t Size, typename T, typename U>
	bool operator==(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			if (vec1.get(i) != vec2.get(i))
			{
				return false;
			}
		}
		return true;
	}

	template <msize_t Size, typename T, typename U>
	bool operator!=(const Vector<Size, T>& vec1, const Vector<Size, U>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			if (vec1.get(i) != vec2.get(i))
			{
				return true;
			}
		}
		return false;
	}

}

#endif