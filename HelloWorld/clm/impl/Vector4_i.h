#ifndef CLM_VECTOR_4_I_H
#define CLM_VECTOR_4_I_H

#include "VectorMatrixCommon_i.h"
#include "Vector_i.h"

namespace clfe
{

	template <typename T>
	class Vector<4, T>
	{
	protected: // Vector reimplementation
		T array[4];

	public:
		Vector() : array{} {}

		Vector(T scalar) : array{ scalar, scalar, scalar, scalar } {}

		template <typename... Args>
			requires (sizeof...(Args) == 4) && AllCompatible<T, Args...>
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr) : array{
			arr[0],
			arr[1],
			arr[2],
			arr[3]
		} {}

		inline msize_t size() const
		{
			return 4;
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
				array[1] * array[1] +
				array[2] * array[2] +
				array[3] * array[3]
			)));
		}

		template <typename U = T>
		Vector<3, U> normalized() const requires Arithmetic2<T, U>
		{
			T dist = distance<T>();
			return Vector<4, U>(
				static_cast<U>(array[0] / dist),
				static_cast<U>(array[1] / dist),
				static_cast<U>(array[2] / dist),
				static_cast<U>(array[3] / dist)
			);
		}

		Vector<3, T>& normalize() requires Arithmetic<T>
		{
			T dist = distance<T>();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
			array[2] = array[2] / dist;
			array[3] = array[3] / dist;
			return *this;
		}

	public: // Vector4 specific
		T x() const
		{
			return array[0];
		}

		T y() const
		{
			return array[1];
		}

		T z() const
		{
			return array[2];
		}

		T w() const
		{
			return array[3];
		}

		void set(T x, T y, T z, T w)
		{
			array[0] = x;
			array[1] = y;
			array[2] = z;
			array[3] = w;
		}

		void x(T x)
		{
			array[0] = x;
		}

		void y(T y)
		{
			array[1] = y;
		}

		void z(T z)
		{
			array[2] = z;
		}

		void w(T w)
		{
			array[3] = w;
		}

		inline T r() const
		{
			return x();
		}

		inline T g() const
		{
			return y();
		}

		inline T b() const
		{
			return z();
		}

		inline T a() const
		{
			return w();
		}

		inline void r(T r)
		{
			x(r);
		}

		inline void g(T g)
		{
			y(g);
		}

		inline void b(T b)
		{
			z(b);
		}

		inline void a(T a)
		{
			w(a);
		}

	};

}

#endif