#ifndef CLM_MATRIX_I_H
#define CLM_MATRIX_I_H

#include "VectorMatrixCommon_i.h"
#include "Vector_i.h"

namespace clfe
{
	
	template <msize_t Cols, msize_t Rows, typename T>
	class Matrix
	{
	protected:
		Vector<Cols, T> array[Rows];

		inline void swap(msize_t c1, msize_t r1, msize_t c2, msize_t r2)
		{
			T temp = get(c1, r1);
			setAt(c1, r1, get(c2, r2));
			setAt(c2, r2, temp);
		}

	public:
		Matrix(T scalar = static_cast<T>(1)) requires (Cols == Rows) : array{} // Only works for square matrices
		{
			for (msize_t i = 0; i < Rows; i++)
			{
				array[i].setAt(i, scalar);
			}
		}

		Matrix() requires (Cols != Rows) : array{} {} // Always all 0 if not a square matrix

		/* Initializes like:
		* 1  2  3  4
		* 5  6  7  8
		* 9  10 11 12
		* 13 14 15 16
		*/
		template <typename... Args>
			requires (sizeof...(Args) == Cols * Rows) && AllCompatible<T, Args...>
		Matrix(Args... args)
		{
			T temp[] = { static_cast<T>(args)... };
			for (msize_t r = 0; r < Rows; r++)
			{
				for (msize_t c = 0; c < Cols; c++)
				{
					array[r].setAt(c, temp[r * Cols + c]);
				}
			}
		}

		Matrix(const T* arr[])
		{
			for (msize_t r = 0; r < Rows; r++)
			{
				for (msize_t c = 0; c < Cols; c++)
				{
					array[r].setAt(c, arr[r * Cols + c]);
				}
			}
		}

		Matrix(const Vector<Cols, T>* arr)
		{
			for (msize_t r = 0; r < Rows; r++)
			{
				array[r] = arr[r];
			}
		}

		inline msize_t rows() const
		{
			return Rows;
		}

		inline msize_t cols() const
		{
			return Cols;
		}

		inline Vector<Cols, T>& operator[](msize_t i)
		{
			return array[i];
		}

		inline Vector<Cols, T> getRow(msize_t i) const
		{
			return array[i];
		}

		inline void setRow(msize_t r, const Vector<Cols, T>& vec)
		{
			array[r] = vec;
		}

		inline const Vector<Cols, T>* const get() const
		{
			return static_cast<const Vector<Cols, T>* const>(array);
		}

		inline T get(msize_t r, msize_t c) const
		{
			return array[r].get(c);
		}

		inline void setAt(msize_t r, msize_t c, T value)
		{
			array[r].setAt(c, value);
		}

		void transpose() requires (Cols == Rows)
		{
			for (msize_t r = 1; r < Rows; r++)
			{
				for (msize_t c = 0; c < r; c++) {
					swap(r, c, c, r);
				}
			}
		}

		Matrix<Rows, Cols, T> transposed() const
		{
			Matrix<Rows, Cols, T> result;
			for (msize_t r = 0; r < Cols; r++)
			{
				Vector<Rows, T>& row = result[r];
				for (msize_t c = 0; c < Rows; c++)
				{
					row.setAt(c, get(c, r));
				}
			}
			return result;
		}
		
	private:
		/*
		template <typename U = T>
		U detHelper(msize_t r, msize_t c, msize_t size, msize_t target) const
		{
			if (size <= 2) {
				if (c + 1 == target)
				{
					return static_cast<U>(get(r, c) * get(r + 1, c + 2) - get(r, c + 2) * get(r + 1, c));
				}
				if (c == target)
				{
					c++;
				}
				return static_cast<U>(get(r, c) * get(r + 1, c + 1) - get(r, c + 1) * get(r + 1, c));
			}

			U sum = static_cast<U>(0);
			U flip = static_cast<U>(1);
			for (msize_t i = 0; i < size; i++)
			{
				if (c + i == target)
				{
					continue;
				}
				sum += flip * (get(r, c + i) * detHelper(r + 1, c, size - 1, c + i));
				flip = static_cast<U>(0) - flip;
			}

			return sum;
		}
		*/

		template <typename U = T>
		U detHelper(msize_t r, msize_t c[], msize_t size) const
		{
			if (size <= 2)
			{
				return static_cast<U>(get(r, c[0]) * get(r + 1, c[1]) - get(r, c[1]) * get(r + 1, c[0]));
			}

			U sum = static_cast<U>(0);
			U flip = static_cast<U>(1);
			for (msize_t i = 0; i < size; i++)
			{
				msize_t c2[size - 1];
				msize_t j = 0;
				for (msize_t k = 0; k < size - 1; k++)
				{
					if (j == i)
					{
						j++;
					}
					c2[k] = c2[j];
					j++;
				}
				sum += flip * (get(r, c[i]) * detHelper(r + 1, c2, size - 1));
				flip = static_cast<U>(0) - flip;
			}

			return sum;
		}

	public:
		template <typename U = T>
		U determinant() const requires (Cols == Rows) && (Cols >= 2) && Arithmetic2<T, U>
		{
			msize_t c[Cols];
			for (msize_t i = 0; i < Cols; i++)
			{
				c[i] = i;
			}
			return detHelper<U>(0, c, Cols);
		}

	};

}

#endif