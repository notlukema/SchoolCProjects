#include "MatrixImpl.h"

#ifndef CLFE_MATRIX_2X2_H
#define CLFE_MATRIX_2X2_H

namespace clfe
{

	template <typename T>
	using Matrix2x2 = Matrix<2, 2, T>;

	using Matrix2x2f = Matrix2x2<float>;
	using Matrix2x2d = Matrix2x2<double>;
	using Matrix2x2i = Matrix2x2<int>;

}

#endif