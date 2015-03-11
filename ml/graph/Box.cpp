#include "../include/graph/Box.h"

namespace ml
{
	namespace graph
	{
		Box::Box() :Rectanglef32()
		{

		}

		Box::Box(const VertexArray&va)
		{
			update(va);
		}

		Box::Box(const PointArray&va)
		{
			update(va);
		}

		Box::~Box()
		{
		}

		void Box::update(const VertexArray&va)
		{
			reset();
			start();
			for (u32 i = 0; i < va.size();++i)
			{
				addPoint(va.getPointAt(i));
			}
			end();
		}

		void Box::update(const PointArray&va)
		{
			reset();
			start();
			for (u32 i = 0; i < va.size(); ++i)
			{
				addPoint(va[i]);
			}
			end();
		}

		void Box::reset()
		{
			x = x2 = y = y2 = 0.00f;
		}

		bool Box::isInsideX(const f32 x_) const
		{
			return (x_ >= x && x_ <= x2);
		}

		bool Box::isInsideY(const f32 y_) const
		{
			return (y_ >= y && y_ <= y2);
		}

		bool Box::isInside(const Point2d &point) const
		{
			// Assume x >= x2 and y >= y2
			return isInsideX(point.x) && isInsideY(point.y);
		}

		ml::Point2d Box::proportion(const Point2d &point) const
		{
			return{ (point.x - x) / width(), (point.y - y) / height() };
		}

		void Box::start()
		{
			xfound = x2found = yfound = y2found = false;
		}

		void Box::addPoint(const Point &v)
		{
			if (v.x < x || !xfound)
			{
				x = v.x;
				xfound = true;
			}

			if (v.x > x2 || !x2found)
			{
				x2 = v.x;
				x2found = true;
			}

			if (v.y < y || !yfound)
			{
				y = v.y;
				yfound = true;
			}

			if (v.y > y2 || !y2found)
			{
				y2 = v.y;
				y2found = true;
			}
		}

		void Box::end()
		{

		}

	}
}
