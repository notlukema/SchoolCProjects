#include "MatrixImpl.h"

#ifndef CLFE_MATRIX_4X4_H
#define CLFE_MATRIX_4X4_H

namespace clfe
{

	template <typename T>
	using Matrix4x4 = Matrix<4, 4, T>;

	using Matrix4x4f = Matrix4x4<float>;
	using Matrix4x4d = Matrix4x4<double>;
	using Matrix4x4i = Matrix4x4<int>;

}

#endif