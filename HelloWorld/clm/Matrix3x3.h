#include "MatrixImpl.h"

#ifndef CLFE_MATRIX_3X3_H
#define CLFE_MATRIX_3X3_H

namespace clfe
{

	template <typename T>
	using Matrix3x3 = Matrix<3, 3, T>;

	using Matrix3x3f = Matrix3x3<float>;
	using Matrix3x3d = Matrix3x3<double>;
	using Matrix3x3i = Matrix3x3<int>;

}

#endif