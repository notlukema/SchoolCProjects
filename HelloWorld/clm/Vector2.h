#include "VectorImpl.h"

#ifndef CLM_VECTOR_2_H
#define CLM_VECTOR_2_H

namespace clfe
{

	template <typename T>
	using Vector2 = Vector<2, T>;

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int>;

}

#endif