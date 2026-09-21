#include "VectorImpl.h"

#ifndef CLM_VECTOR_4_H
#define CLM_VECTOR_4_H

namespace clfe
{

	template <typename T>
	using Vector4 = Vector<4, T>;

	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int>;

}

#endif