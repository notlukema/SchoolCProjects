#ifndef CLM_VECTOR_IMPL_H
#define CLM_VECTOR_IMPL_H

#include "impl/Vector_i.h"
#include "impl/Vector2_i.h"
#include "impl/Vector3_i.h"
#include "impl/Vector4_i.h"

#include "impl/VectorOp_i.h"
#include "impl/VectorUtils_i.h"

// Technically redundant due to matrix always including vector but here anyways
#ifdef CLM_MATRIX_IMPL_H
#include "impl/VectorMatrixOp_i.h"
#include "impl/VectorMatrixUtils_i.h"
#endif

#endif