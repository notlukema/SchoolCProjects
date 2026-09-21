#ifndef CLM_MATRIX_IMPL_H
#define CLM_MATRIX_IMPL_H

#include "VectorImpl.h" // Know for sure that matrix runs on vectors

#include "impl/Matrix_i.h"
#include "impl/Matrix2x2_i.h"
#include "impl/Matrix3x3_i.h"
#include "impl/Matrix4x4_i.h"

#include "impl/MatrixOp_i.h"
#include "impl/MatrixUtils_i.h"

// Should always be true but here for consistency
#ifdef CLM_VECTOR_IMPL_H
#include "impl/VectorMatrixOp_i.h"
#include "impl/VectorMatrixUtils_i.h"
#endif

#endif