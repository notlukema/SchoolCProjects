#ifndef CLM_MATRIX_2X2_I_H
#define CLM_MATRIX_2X2_I_H

#include "VectorMatrixCommon_i.h"
#include "Matrix_i.h"

namespace clfe
{

	template <typename T>
	class Matrix<2, 2, T>
	{
	protected: // Matrix reimplementation
		using ct = Vector<2, T>;
		ct array[2];

		inline void swap(msize_t r1, msize_t c1, msize_t r2, msize_t c2)
		{
			T temp = get(r1, c1);
			setAt(r1, c1, get(r2, c2));
			setAt(r2, c2, temp);
		}

	public:
		Matrix(T scalar = static_cast<T>(1)) : array{
			ct(scalar, 0),
			ct(0, scalar)
		} {}

		Matrix(T m00, T m01,
			T m10, T m11) : array{
			ct(m00, m01),
			ct(m10, m11)
		} {}

		Matrix(const T* arr[]) : array{
			ct(arr[0], arr[1]),
			ct(arr[2], arr[3])
		} {}

		Matrix(const Vector<2, T>* arr) : array{
			arr[0],
			arr[1]
		} {}

		inline msize_t rows() const
		{
			return 2;
		}

		inline msize_t cols() const
		{
			return 2;
		}

		inline ct& operator[](msize_t i)
		{
			return array[i];
		}

		inline ct getRow(msize_t i) const
		{
			return array[i];
		}

		inline void setRow(msize_t r, const ct& vec)
		{
			array[r] = vec;
		}

		inline const ct* const get() const
		{
			return static_cast<const ct* const>(array);
		}

		inline T get(msize_t r, msize_t c) const
		{
			return array[r].get(c);
		}

		inline void setAt(msize_t r, msize_t c, T value)
		{
			array[r].setAt(c, value);
		}

	public:
		void transpose()
		{
			swap(0, 1, 1, 0);
		}

		Matrix<2, 2, T> transposed() const
		{
			return Matrix<2, 2, T>(
				get(0, 0), get(1, 0),
				get(0, 1), get(1, 1)
			);
		}

		template <typename U = T>
		U determinant() const requires Arithmetic2<T, U>
		{
			return static_cast<U>(get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0));
		}

	public: // Matrix2x2 specific
		inline T m00() const
		{
			return get(0, 0);
		}

		inline T m01() const
		{
			return get(0, 1);
		}

		inline T m10() const
		{
			return get(1, 0);
		}

		inline T m11() const
		{
			return get(1, 1);
		}

	};

}

#endif