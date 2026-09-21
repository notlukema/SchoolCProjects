#ifndef CLM_VECTOR_2_I_H
#define CLM_VECTOR_2_I_H

#include "VectorMatrixCommon_i.h"
#include "Vector_i.h"

namespace clfe
{

	template <typename T>
	class Vector<2, T>
	{
	protected: // Vector reimplementation
		T array[2];

	public:
		Vector() : array{} {}

		Vector(T scalar) : array{ scalar, scalar } {}

		template <typename... Args>
			requires (sizeof...(Args) == 2) && AllCompatible<T, Args...>
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr) : array{
			arr[0],
			arr[1]
		} {}

		inline msize_t size() const
		{
			return 2;
		}

		inline T& operator[](msize_t i)
		{
			return array[i];
		}

		inline const T* get() const
		{
			return static_cast<const T*>(array);
		}

		inline T get(msize_t i) const
		{
			return array[i];
		}

		inline void setAt(msize_t i, T value)
		{
			array[i] = value;
		}

		template <typename U = T>
		U distance() const requires Arithmetic2<T, U>
		{
			return static_cast<U>(sqrt(static_cast<U>(
				array[0] * array[0] +
				array[1] * array[1]
			)));
		}

		template <typename U = T>
		Vector<2, U> normalized() const requires Arithmetic2<T, U>
		{
			T dist = distance<T>();
			return Vector<2, U>(
				static_cast<U>(array[0] / dist),
				static_cast<U>(array[1] / dist)
			);
		}

		Vector<2, T>& normalize() requires Arithmetic<T>
		{
			T dist = distance<T>();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
			return *this;
		}

	public: // Vector2 specific
		T x() const
		{
			return array[0];
		}

		T y() const
		{
			return array[1];
		}

		void set(T x, T y)
		{
			array[0] = x;
			array[1] = y;
		}

		void x(T x)
		{
			array[0] = x;
		}

		void y(T y)
		{
			array[1] = y;
		}

		inline T u() const
		{
			return x();
		}

		inline T v() const
		{
			return y();
		}

		void u(T u)
		{
			x(u);
		}

		void v(T v)
		{
			y(v);
		}

	};

}

#endif