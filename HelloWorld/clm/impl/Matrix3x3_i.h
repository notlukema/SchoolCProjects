#ifndef CLM_MATRIX_3X3_I_H
#define CLM_MATRIX_3X3_I_H

#include "VectorMatrixCommon_i.h"
#include "Matrix_i.h"

namespace clfe
{

	template <typename T>
	class Matrix<3, 3, T>
	{
	protected: // Matrix reimplementation
		using ct = Vector<3, T>;
		ct array[3];

		inline void swap(msize_t r1, msize_t c1, msize_t r2, msize_t c2)
		{
			T temp = get(r1, c1);
			setAt(r1, c1, get(r2, c2));
			setAt(r2, c2, temp);
		}

	public:
		Matrix(T scalar = static_cast<T>(1)) : array{
			ct(scalar, 0, 0),
			ct(0, scalar, 0),
			ct(0, 0, scalar)
		} {}

		Matrix(T m00, T m01, T m02,
			T m10, T m11, T m12,
			T m20, T m21, T m22) : array{
			ct(m00, m01, m02),
			ct(m10, m11, m12),
			ct(m20, m21, m22)
		} {}

		Matrix(const T* arr[]) : array{
			ct(arr[0], arr[1], arr[2]),
			ct(arr[3], arr[4], arr[5]),
			ct(arr[6], arr[7], arr[8])
		} {}

		Matrix(const Vector<3, T>* arr) : array{
			arr[0],
			arr[1],
			arr[2]
		} {}

		inline msize_t rows() const
		{
			return 3;
		}

		inline msize_t cols() const
		{
			return 3;
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
			swap(0, 2, 2, 0);
			swap(1, 2, 2, 1);
		}

		Matrix<3, 3, T> transposed() const
		{
			return Matrix<3, 3, T>(
				get(0, 0), get(1, 0), get(2, 0),
				get(0, 1), get(1, 1), get(2, 1),
				get(0, 2), get(1, 2), get(2, 2)
			);
		}

	private:
		template <typename U = T>
		inline U detHelper(msize_t c1, msize_t c2) const
		{
			return static_cast<U>(get(1, c1) * get(2, c2) - get(1, c2) * get(2, c1));
		}

	public:
		template <typename U = T>
		U determinant() const requires Arithmetic2<T, U>
		{
			return static_cast<U>(get(0, 0) * detHelper(1, 2) - get(0, 1) * detHelper(0, 2) + get(0, 2) * detHelper(0, 1));
		}

	public: // Matrix3x3 specific
		inline T m00() const
		{
			return get(0, 0);
		}

		inline T m01() const
		{
			return get(0, 1);
		}

		inline T m02() const
		{
			return get(0, 2);
		}

		inline T m10() const
		{
			return get(1, 0);
		}

		inline T m11() const
		{
			return get(1, 1);
		}

		inline T m12() const
		{
			return get(1, 2);
		}

		inline T m20() const
		{
			return get(2, 0);
		}

		inline T m21() const
		{
			return get(2, 1);
		}

		inline T m22() const
		{
			return get(2, 2);
		}

	};

}

#endif