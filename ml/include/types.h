#ifndef __TYPES_H__
#define __TYPES_H__

#include "mlcconfig.h"
#include <vector>
#undef  abs
#include <cmath>
#include <map>

namespace ml
{
	typedef unsigned char u8;
	typedef signed char s8;
	typedef u8 byte;

	typedef unsigned short u16;
	typedef signed short s16;

	typedef unsigned int u32;
	typedef signed int s32;

	typedef float f32;
	typedef double f64;

	template <class T>
	class ML_API Vector2d
	{
	public:
		Vector2d() :x(), y() {}
		Vector2d(T x_, T y_) :x(x_), y(y_) {}
		Vector2d(const Vector2d<T> &other) : x(other.x), y(other.y) {}
		Vector2d &operator=(const Vector2d<T> &other) { x = other.x; y = other.y; return *this; }
		bool &operator==(const Vector2d<T> &other) { return x == other.x && y == other.y; }
		bool &operator!=(const Vector2d<T> &other) { return !(*this == other); }
		Vector2d operator*(const Vector2d<T> &other) { return Vector2d<T>(x*other.x, y*other.y); }
		Vector2d &operator*=(const Vector2d<T> &other) { x *= (T)other.x; y *= (T)other.y; return this; }
		template <class V> Vector2d operator+(const Vector2d<V> &other) const
		{
			return Vector2d<T>(x + (T)other.x, y + (T)other.y);
		}
		template <class V> Vector2d operator-(const Vector2d<V> &other) const 
		{
			return Vector2d<T>(x - (T)other.x, y - (T)other.y);
		}

		template <class V> Vector2d operator*(const Vector2d<V> &other) const
		{
			return Vector2d<T>(x * (T)other.x, y * (T)other.y);
		}

		template <class V> Vector2d operator*(const V other) const
		{
			return Vector2d<T>(x * (T)other, y * (T)other);
		}

		template <class V> Vector2d &operator*=(const Vector2d<V> &other)
		{
			x *= (T)other.x;
			y *= (T)other.y;
			return *this;
		}

		template <class V> Vector2d &operator*=(const V other)
		{
			x *= (T)other;
			y *= (T)other;
			return *this;
		}
		const T *raw() const { return &x; }
		T x;
		T y;
	};

	typedef Vector2d<u32> Size;

	template <class T>
	class Vector3d : public Vector2d<T>
	{
	public:
		Vector3d() :Vector2d(),z() {}
		Vector3d(T x_, T y_) :Vector2d(x_, y_), z() {}
		Vector3d(T x_, T y_, T z_) :Vector2d(x_,y_),z(z_) {}
		Vector3d(const Vector2d<T> &other) : Vector2d(other), z() {}
		Vector3d(const Vector3d<T> &other) : Vector2d(other.x, other.y), z(other.z) {}
		Vector3d &operator=(const Vector2d<T> &other) { z = 0; Vector2d::operator =(other); return *this; }
		Vector3d &operator=(const Vector3d<T> &other) { x = other.x; y = other.y; z = other.z; return *this; }
		bool operator==(const Vector3d<T> &other) { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const Vector3d<T> &other) { return !(*this == other); }

		T z;
	};

	template <class T>
	class Rectangle
	{
	public:
		Rectangle() :x(0), y(0), x2(0), y2(0) {}
		Rectangle(T x_, T y_, T x2_, T y2_) :x(x_), y(y_), x2(x2_), y2(y2_) {}
		Rectangle(const Vector2d<T> &p1, const Vector2d<T> &p2) : x(p1.x), y(p1.y), x2(p2.x), y2(p2.y) {}
		Rectangle(const Vector2d<T> &p1, T x2_, T y2_) : x(p1.x), y(p1.y), x2(x2_), y2(y2_) {}
		Rectangle(T x_, T y_, const Vector2d<T> &p2) : x(x_), y(y_), x2(p2.x), y2(p2.y) {}

		template <class Y>
		Rectangle(const Rectangle<Y> &other) : x((T)other.x), y((T)other.y), x2((T)other.x2), y2((T)other.y2){}
		T x, y, x2, y2;
		const Vector2d<T> center() const { return Vector2d<T>(((x2 - x) / (T)2), ((y2 - y) / (T)2)); }
		Vector2d<T> xy() const { return Vector2d<T>(x, y); }
		Vector2d<T> x2y2() const { return Vector2d<T>(x2, y2); }

		Rectangle<T> operator*(T scalar) const
		{
			return Rectangle<T>(x*scalar, y*scalar, x2*scalar, y2*scalar);
		}
		template <typename V> Rectangle<T> &operator*=(V scalar)
		{
			x *= (T)scalar;
			y *= (T)scalar;
			x2 *= (T)scalar;
			y2 *= (T)scalar;
			return *this;
		}
		Rectangle<T> &operator=(const Rectangle<T> &other)
		{
			x = other.x; y = other.y; x2 = other.x2; y2 = other.y2;
			return *this;
		}

		template <typename V> void moveToxy(const Vector2d<V> &where_)
		{
			Vector2d<T> delta = x - where_;
			this->operator-=(delta);

		}
		template <typename V> Rectangle<T> &operator+=(const Vector2d<V> &scalar)
		{
			x += (T)scalar.x;
			y += (T)scalar.y;
			x2 += (T)scalar.x2;
			y2 += (T)scalar.y2;
			return *this;
		}
		template <typename V> Rectangle<T> &operator+=(const V &scalar)
		{
			return operator+(Vector2d<V>(scalar, scalar));
		}

		template <typename V> Rectangle<T> &operator-=(const Vector2d<V> &scalar)
		{
			x -= (T)scalar.x;
			y -= (T)scalar.y;
			x2 -= (T)scalar.x2;
			y2 -= (T)scalar.y2;
		}
		template <typename V> Rectangle<T> &operator-=(const V &scalar)
		{
			return operator-=(Vector2d<V>(scalar, scalar));
		}

		const T width() const { return (x2 - x); }
		const T height() const { return (y2 - y); }
		const T awidth() const { T w = width(); return (w<0) ? (T)(-1) * w : w; }
		const T aheight() const { T h = height(); return (h<0) ? (T)(-1) * h : h; }

		Vector2d<T> size() const { return Vector2d<T>(width(), height()); }
		Vector2d<T> asize() const { return Vector2d<T>(awidth(), aheight()); }

		void setWidth(const T &nw) { x2 = x + nw; }
		void setHeight(const T &nh) { y2 = y + nh; }

		template <class Y> explicit operator Rectangle<Y>() { return Rectangle<Y>((Y)x, (Y)y, (Y)x2, (Y)y2); }
	};

	template class ML_API Rectangle < f32 >;
	template class ML_API Rectangle < u32 > ;

	typedef Rectangle<f32> Rectanglef32;
	typedef Rectangle<u32> Rectangleu32;

	class ML_API Color
	{
	public:
		Color(f32 r_ = 1.0f, f32 g_ = 1.0f, f32 b_ = 1.0f, f32 a_ = 1.0f) : r(r_), g(g_), b(b_), a(a_) {}
		f32 r, g, b, a;
		byte getRByte() const { return (byte)(r * 255.0f); }
		byte getGByte() const { return (byte)(g * 255.0f); }
		byte getBByte() const { return (byte)(b * 255.0f); }
		byte getAByte() const { return (byte)(a * 255.0f); }
		void setRByte(const byte r_) { r = (float)r_ / 255.0f; }
		void setGByte(const byte g_) { r = (float)g_ / 255.0f; }
		void setBByte(const byte b_) { r = (float)b_ / 255.0f; }
		void setAByte(const byte a_) { r = (float)a_ / 255.0f; }

		const f32 *rawRGBA() const { return &r; }
		const f32 *rawRGB() const { return &r; }
	};

	typedef Vector3d<f32> Point;
	typedef Vector2d<f32> Point2d;

	class Vertex
	{
	public:
		Vertex(const Point &position_ = Point(), const Color &color_ = Color(), const Point2d &tc_ = Point2d())
			:position(position_), tCoordinates(tc_), color(color_) {}
		Vertex(f32 x,f32 y, f32 z, f32 tx, f32 ty, f32 r, f32 g, f32 b, f32 a)
		{
			position.x = x; position.y = y; position.z = z;
			tCoordinates.x = tx;
			tCoordinates.y = ty;
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}
		Point position;
		Color color;
		Point2d tCoordinates;
	};

	template class ML_API std::vector < Vertex > ;
	template class ML_API std::vector < Point > ;
	template class ML_API std::vector < Point2d > ;
	template class ML_API std::vector < Color > ;
	template class ML_API std::vector < u16 > ;

	using PointArray = std::vector < Point > ;
	using TextureCoordinatesArray = std::vector < Point2d > ;
	using ColorArray = std::vector < Color > ;
	using IndexArray = std::vector < u16 > ;
	using VertexData = std::vector < Vertex > ;


	// TO DO: Private types
	enum AttributeType
	{
		Positions = 0,
		Normals = 2,
		Colors = 3,
		Textcoord0 = 8,
		Custom = 9
	};

	using AttributeMap = std::vector<std::string>;
}

#endif
