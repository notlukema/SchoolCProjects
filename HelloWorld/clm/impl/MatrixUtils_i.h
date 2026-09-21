#ifndef CLM_MATRIX_UTILS_I_H
#define CLM_MATRIX_UTILS_I_H

#include "VectorMatrixCommon_i.h"
#include "Matrix_i.h"
#include "Vector_i.h"
#include "VectorUtils_i.h"
#include "../Mathf.h"

namespace clfe
{

	// Default utilities

	template <msize_t Cols, msize_t Rows, msize_t Cols0, msize_t Rows0, typename T> // Could try replacing Cols and Cols0 with one template parameter, same with Rows and Rows0
	inline Matrix<Cols, Rows, T> resizeMat(const Matrix<Cols0, Rows0, T>& mat) requires (Cols == Cols0) && (Rows == Rows0)
	{
		return Matrix<Cols, Rows, T>(mat);
	}

	template <msize_t Cols, msize_t Rows, msize_t Cols0, msize_t Rows0, typename T>
	Matrix<Cols, Rows, T> resizeMat(const Matrix<Cols0, Rows0, T>& mat) requires (Cols != Cols0) || (Rows != Rows0)
	{
		Matrix<Cols, Rows, T> result;
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, (r < Rows0) ? resize<Cols>(mat.getRow(r)) : Vector<Cols, T>());
		}
		return result;
	}

	template <typename To, msize_t Cols, msize_t Rows, typename From>
		requires Compatible<From, To>
	inline Matrix<Cols, Rows, To> castMat(const Matrix<Cols, Rows, From>& mat)
	{
		Vector<Cols, To> arr[Rows];
		for (msize_t i = 0; i < Rows; i++)
		{
			arr[i] = castVec<To>(mat.getRow(i));
		}
		return Matrix<Cols, Rows, To>(arr);
	}

	// Transformation matrices

	// mat scale
	template <typename T = float>
	Matrix<4, 4, T> mscale(T scale)
	{
		return Matrix<4, 4, T>(
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, scale, 0,
			0, 0, 0, 1
		);
	}

	// mat scale
	template <typename T = float>
	Matrix<4, 4, T> mscale(T scaleX, T scaleY, T scaleZ)
	{
		return Matrix<4, 4, T>(
			scaleX, 0, 0, 0,
			0, scaleY, 0, 0,
			0, 0, scaleZ, 0,
			0, 0, 0, 1
		);
	}

	// mat translate
	template <typename T = float>
	Matrix<4, 4, T> mtranslate(T tx, T ty, T tz)
	{
		return Matrix<4, 4, T>(
			1, 0, 0, tx,
			0, 1, 0, ty,
			0, 0, 1, tz,
			0, 0, 0, 1
		);
	}

	// mat rotate x
	template <typename T = float>
	Matrix<4, 4, T> mrotateX(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	// mat rotate y
	template <typename T = float>
	Matrix<4, 4, T> mrotateY(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	// mat rotate z
	template <typename T = float>
	Matrix<4, 4, T> mrotateZ(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	// mat rotate
	template <typename T = float>
		requires Arithmetic<T>
	Matrix<4, 4, T> mrotate(float rad, Vector<3, T> axis)
	{
		axis = axis.normalized();
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		T t = static_cast<T>(1) - c;
		T x = axis.get(0);
		T y = axis.get(1);
		T z = axis.get(2);
		return Matrix<4, 4, T>(
			t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0,
			t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0,
			t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
		requires Arithmetic<T>
	Matrix<4, 4, T> mfrustum(float left, float right, float bottom, float top, float near, float far)
	{
		T rl = static_cast<T>(1) / static_cast<T>(right - left);
		T tb = static_cast<T>(1) / static_cast<T>(top - bottom);
		T fn = static_cast<T>(1) / static_cast<T>(far - near);
		return Matrix<4, 4, T>(
			static_cast<T>(2) * near * rl, 0, 0, -near * (right + left) * rl,
			0, static_cast<T>(2) * near * tb, 0, -near * (top + bottom) * tb,
			0, 0, -(far + near) * fn, -static_cast<T>(2) * far * near * fn,
			0, 0, -static_cast<T>(1), 0
		);
	}

	template <typename T = float>
		requires Arithmetic<T>
	Matrix<4, 4, T> mfov(float fov, float aspect, float near, float far)
	{
		float top = near * static_cast<float>(tan(fov * 3.141592f / 360.0f));
		float bottom = -top;
		float right = top * aspect;
		float left = -right;
		return mfrustum(left, right, bottom, top, near, far);
	}


}

#endif