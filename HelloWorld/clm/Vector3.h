#include "VectorImpl.h"

#ifndef CLM_VECTOR_3_H
#define CLM_VECTOR_3_H

namespace clfe
{

	template <typename T>
	using Vector3 = Vector<3, T>;

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;

}

#endif