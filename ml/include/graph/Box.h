#ifndef __BOX_H__
#define __BOX_H__

#include "../mlcconfig.h"
#include "../types.h"
#include "VertexArray.h"

namespace ml
{
	namespace graph
	{
		class ML_API Box : public Rectanglef32
		{
		public:
			Box();
			Box(const VertexArray&);
			Box(const PointArray&);
			virtual ~Box();

			void update(const VertexArray&);
			void update(const PointArray&);
			void reset();

			bool isInsideX(const f32 x_) const;
			bool isInsideY(const f32 y_) const;
			bool isInside(const Point2d &point) const;
			Point2d proportion(const Point2d &point) const;

		private:
			void start();
			void addPoint(const Point &);
			void end();
			bool xfound;
			bool x2found;
			bool yfound;
			bool y2found;

		};
	}
}

#endif
