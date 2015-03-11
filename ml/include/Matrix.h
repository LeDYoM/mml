#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "mlcconfig.h"
#include <initializer_list>
#include <vector>
#include <array>
#include "types.h"

namespace ml
{
	
	template <class T,int D> class Matrix
	{
	public:
		Matrix() { loadIdentity(); }
		Matrix(T fillElement) { fill(fillElement); }
		std::array<T, D> &operator[](int row) { return data[row]; }
		const std::array<T, D> &operator[](int row) const { return data[row]; }

		void fill(T w)
		{
			for (int i = 0; i < D; ++i)
				for (int j = 0; j < D; ++j)
					operator[](i)[j] = w;
		}

		void loadIdentity()
		{
			for (int i = 0; i < D; ++i)
				for (int j = 0; j < D; ++j)
					operator[](i)[j] = (T)((i == j)? 1 : 0);
		}
		Matrix &operator*(Matrix &other)
		{
			return other;
		}

		const T *raw() const { return data[0].data(); }
		Matrix &operator=(const Matrix &other) { data = other.data; return *this; }

		virtual ~Matrix(){}
	private:
		std::array<std::array<T,D>,D> data;
	};

	template<class T> class ML_API Matrix4 : public Matrix<T,4>
	{
	};

}

#endif
