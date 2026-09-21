#ifndef CLM_VECTORMATRIX_OP_I_H
#define CLM_VECTORMATRIX_OP_I_H

#include "VectorMatrixCommon_i.h"
#include "Vector_i.h"
#include "Matrix_i.h"

namespace clfe
{

	template <msize_t Cols, msize_t Rows, msize_t Size, typename T, typename U>
		requires (Cols == Size) && Arithmetic<T> && Arithmetic<U>
	auto operator*(const Matrix<Cols, Rows, T>& mat, const Vector<Size, U>& vec) -> Vector<Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
			for (msize_t k = 0; k < Size; k++)
			{
				sum += mat.get(k, r) * vec.get(k);
			}
			result.setAt(r, sum);
		}
		return result;
	}

	template <msize_t Size, msize_t Cols, msize_t Rows, typename T, typename U>
		requires (Size == Rows) && Arithmetic<T> && Arithmetic<U>
	auto operator*(const Vector<Size, T>& vec, const Matrix<Cols, Rows, U>& mat) -> Vector<Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t c = 0; c < Cols; c++)
		{
			decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
			for (msize_t k = 0; k < Size; k++)
			{
				sum += mat.get(c, k) * vec.get(k);
			}
			result.setAt(c, sum);
		}
		return result;
	}
	
}

#endif