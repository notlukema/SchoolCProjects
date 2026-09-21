#ifndef CLM_VECTORMATRIX_UTILS_I_H
#define CLM_VECTORMATRIX_UTILS_I_H

#include "VectorMatrixCommon_i.h"
#include "Vector_i.h"
#include "Matrix_i.h"

namespace clfe
{

	template <msize_t Size, typename T>
	Matrix<Size, 1, T> toMatrix(const Vector<Size, T>& vec)
	{
		Matrix<Size, 1, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(0, i, vec.get(i));
		}
		return result;
	}

	template <msize_t Size, typename T>
	Vector<Size, T> toVector(const Matrix<Size, 1, T>& mat)
	{
		Vector<Size, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, mat.get(i, 0));
		}
		return result;
	}

	template <msize_t Size, typename T>
	Vector<Size, T> toVector(const Matrix<1, Size, T>& mat)
	{
		Vector<Size, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, mat.get(0, i));
		}
		return result;
	}


}

#endif