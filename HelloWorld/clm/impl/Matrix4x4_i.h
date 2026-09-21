#ifndef CLM_MATRIX_4X4_I_H
#define CLM_MATRIX_4X4_I_H

#include "VectorMatrixCommon_i.h"
#include "Matrix_i.h"

namespace clfe
{

	template <typename T>
	class Matrix<4, 4, T>
	{
	protected: // Matrix reimplementation
		using ct = Vector<4, T>;
		ct array[4];

		inline void swap(msize_t r1, msize_t c1, msize_t r2, msize_t c2)
		{
			T temp = get(r1, c1);
			setAt(r1, c1, get(r2, c2));
			setAt(r2, c2, temp);
		}

	public:
		Matrix(T scalar = static_cast<T>(1)) : array{
			ct(scalar, 0, 0, 0),
			ct(0, scalar, 0, 0),
			ct(0, 0, scalar, 0),
			ct(0, 0, 0, scalar)
		} {}

		Matrix(T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33) : array{
			ct(m00, m01, m02, m03),
			ct(m10, m11, m12, m13),
			ct(m20, m21, m22, m23),
			ct(m30, m31, m32, m33)
		} {}

		Matrix(const T* arr[]) : array{
			ct(arr[0], arr[1], arr[2], arr[3]),
			ct(arr[4], arr[5], arr[6], arr[7]),
			ct(arr[8], arr[9], arr[10], arr[11]),
			ct(arr[12], arr[13], arr[14], arr[15])
		} {}

		Matrix(const Vector<4, T>* arr) : array{
			arr[0],
			arr[1],
			arr[2],
			arr[3]
		} {}

		inline msize_t rows() const
		{
			return 4;
		}

		inline msize_t cols() const
		{
			return 4;
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
			swap(0, 3, 3, 0);
			swap(1, 2, 2, 1);
			swap(1, 3, 3, 1);
			swap(2, 3, 3, 2);
		}

		Matrix<4, 4, T> transposed() const
		{
			return Matrix<4, 4, T>(
				get(0, 0), get(1, 0), get(2, 0), get(3, 0),
				get(0, 1), get(1, 1), get(2, 1), get(3, 1),
				get(0, 2), get(1, 2), get(2, 2), get(3, 2),
				get(0, 3), get(1, 3), get(2, 3), get(3, 3)
			);
		}

	private:
		template <typename U = T>
		inline U detHelper2(msize_t c1, msize_t c2) const
		{
			return static_cast<U>(get(2, c1) * get(3, c2) - get(3, c1) * get(2, c2));
		}

		template <typename U = T>
		inline U detHelper(msize_t c1, msize_t c2, msize_t c3) const requires Arithmetic2<T, U>
		{
			return static_cast<U>(get(1, c1) * detHelper2(c2, c3) - get(1, c2) * detHelper2(c1, c3) + get(1, c3) * detHelper2(c1, c2));
		}

	public:
		template <typename U = T>
		U determinant() const requires Arithmetic2<T, U>
		{
			return static_cast<U>(get(0, 0) * detHelper(1, 2, 3) - get(0, 1) * detHelper(0, 2, 3) + get(0, 2) * detHelper(0, 1, 3) + get(0, 3) * detHelper(0, 1, 2));
		}

	public: // Matrix4x4 specific
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

		inline T m03() const
		{
			return get(0, 3);
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

		inline T m13() const
		{
			return get(1, 3);
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

		inline T m23() const
		{
			return get(2, 3);
		}

		inline T m30() const
		{
			return get(3, 0);
		}

		inline T m31() const	
		{
			return get(3, 1);
		}

		inline T m32() const
		{
			return get(3, 2);
		}

		inline T m33() const
		{
			return get(3, 3);
		}

	};

}

#endif