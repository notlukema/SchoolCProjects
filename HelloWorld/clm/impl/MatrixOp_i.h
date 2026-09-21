#ifndef CLM_MATRIX_OP_I_H
#define CLM_MATRIX_OP_I_H

#include "VectorMatrixCommon_i.h"
#include "Matrix_i.h"

namespace clfe
{

	//
	// Inter-matrix operations
	//

	// Addition

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) + mat2.get(r));
		}
		return result;
	}

	template <msize_t Cols1, msize_t Rows1, msize_t Cols2, msize_t Rows2, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Matrix<Cols1, Rows1, T>& mat1, const Matrix<Cols2, Rows2, U>& mat2) -> Matrix<smax(Cols1, Cols2), smax(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		// Experimental implementation that may be more efficient
		auto result = Matrix<smax(Cols1, Cols2), smax(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>();
		msize_t r = 0;
		for (; r < smin(Rows1, Rows2); r++)
		{
			result.setRow(r,mat1.getRow(r) + mat2.getRow(r));
		}
		if (Rows2 < Rows1)
		{
			for (; r < Rows1; r++)
			{
				result.setRow(r, resize<smax(Cols1, Cols2)>(mat1.getRow(r)));
			}
		}
		else
		{
			for (; r < Rows2; r++)
			{
				result.setRow(r, resize<smax(Cols1, Cols2)>(mat2.getRow(r)));
			}
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator+=(Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat1.setRow(r, mat1.getRow(r) + mat2.getRow(r));
		}
		return mat1;
	}

	// Subtraction

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) - mat2.get(r));
		}
		return result;
	}

	template <msize_t Cols1, msize_t Rows1, msize_t Cols2, msize_t Rows2, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Matrix<Cols1, Rows1, T>& mat1, const Matrix<Cols2, Rows2, U>& mat2) -> Matrix<smax(Cols1, Cols2), smax(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<smax(Cols1, Cols2), smax(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < smax(Rows1, Rows2); r++)
		{
			result.setRow(r,
				((r < Rows1) ? mat1.getRow(r) : Vector<Cols1, T>()) -
				((r < Rows2) ? mat2.getRow(r) : Vector<Cols2, U>())
			);
		}
		return result;
		
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator-=(Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat1.setRow(r, mat1.getRow(r) - mat2.getRow(r));
		}
		return mat1;
	}

	// Multiplication (special)

	template <msize_t Cols1, msize_t Rows1, msize_t Cols2, msize_t Rows2, typename T, typename U>
		requires (Cols1 == Rows2) && Arithmetic<T>&& Arithmetic<U>
	auto operator*(const Matrix<Cols1, Rows1, T>& mat1, const Matrix<Cols2, Rows2, U>& mat2) -> Matrix<Cols2, Rows1, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols2, Rows1, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows1; r++)
		{
			for (msize_t c = 0; c < Cols2; c++)
			{
				decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
				for (msize_t k = 0; k < Cols1; k++)
				{
					sum += mat1.get(k, r) * mat2.get(c, k);
				}
				result.setAt(c, r, sum);
			}
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T>&& Arithmetic<U>
	auto flatmatmul(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) * mat2.get(r));
		}
		return result;
	}

	// Division

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator/(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) / mat2.get(r));
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator/=(Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat1.setRow(r, mat1.getRow(r) / mat2.getRow(r));
		}
		return mat1;
	}

	//
	// Scalar operations
	//

	// Addition

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) + scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator+=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) + scalar);
		}
		return mat;
	}

	// Subtraction

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) - scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator-=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) - scalar);
		}
		return mat;
	}

	// Multiplication

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator*(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) * scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator*=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) * scalar);
		}
		return mat;
	}

	// Division

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator/(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) / scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator/=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) / scalar);
		}
		return mat;
	}

	//
	// Comparisons
	//

	template <msize_t Cols, msize_t Rows, typename T, typename U>
	bool operator==(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			if (mat1.getRow(r) != mat2.getRow(r))
			{
				return false;
			}
		}
		return true;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
	bool operator!=(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			if (mat1.getRow(r) != mat2.getRow(r))
			{
				return true;
			}
		}
		return false;
	}

}

#endif