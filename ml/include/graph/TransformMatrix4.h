#ifndef __TRANSFORMMATRIX_4_H__
#define __TRANSFORMMATRIX_4_H__

#include "../mlcconfig.h"
#include "../Matrix.h"
namespace ml
{
	template <class T> class ML_API TransformMatrix4 : public Matrix4 < T >
	{
	public:
		const int mDimension = 4;
		using Matrix4::Matrix4;
		using Matrix4::loadIdentity;
		using Matrix4::operator=;

		Matrix &setPosition(const Vector3d<T> &position_)
		{
			operator[](3)[0] = position_.x;
			operator[](3)[1] = position_.y;
			operator[](3)[2] = position_.z;
			return *this;
		}
		Matrix &setScale(const Vector3d<T> &scale_)
		{
			operator[](0)[0] = scale_.x;
			operator[](1)[1] = scale_.y;
			operator[](2)[2] = scale_.z;
			return *this;
		}
		Matrix &setOrtho(T left, T right, T bottom, T top, T zNear, T zFar)
		{
			for (int i = 0; i < mDimension; ++i)
			{
				for (int j = 0; j < mDimension; ++j)
				{
					if (i == j)
					{
						switch (i)
						{
						case 0:
							operator[](0)[0] = (T)2 / (right - left);
							break;
						case 1:
							operator[](1)[1] = (T)2 / (top - bottom);
							break;
						case 2:
							operator[](2)[2] = (T)-2 / (zFar - zNear);
							break;
						case 3:
						default:
							break;
							operator[](i)[j] = (T)1;
						}
					}
					else
					{
						if (i == 3)
						{
							switch (j)
							{
							case 0:
								operator[](3)[0] = -((right + left) / (right - left));
								break;
							case 1:
								operator[](3)[1] = -((top + bottom) / (top - bottom));
								break;
							case 2:
								operator[](3)[2] = -((zFar + zNear) / (zFar - zNear));
								break;
							default:
								//								operator[](i)[j] = (T)1;
								break;
							}
						}
						else
						{
							operator[](i)[j] = (T)0;
						}

					}
				}
			}
			return *this;
		}
	};

	typedef TransformMatrix4<f32> TransformationMatrix;
}

#endif
