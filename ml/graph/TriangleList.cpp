#include "../include/graph/TriangleList.h"
#include "../openglPriv.h"
#include "../include/graph/Box.h"

#define TRLERROR(x) LOG_PRIVATE_DEBUG_ERROR("Triangle list: "<<x)

namespace ml
{
	namespace graph
	{
		TriangleList::TriangleList()
		{
		}

		TriangleList::~TriangleList()
		{
		}

		TriangleList & TriangleList::addCircle(f32 radius, u32 nVertex,
			const Rectanglef32 &textureRectangle,
			const ColorArray &colorArray)
		{
			PointArray va;

			Point temp;
			const f32 tBase = 2.0f * 3.1415926f / nVertex;
			for (u32 i = 0; i < nVertex; ++i)
			{
				const f32 theta = i * tBase;

				temp.x = radius * std::cosf(theta);//calculate the x component 
				temp.y = radius * std::sinf(theta);//calculate the y component
				va.push_back(temp);
			}
			return add(va,textureRectangle,colorArray);
		}

		TriangleList &TriangleList::addQuad(const Rectanglef32 &rect,
			const Rectanglef32 &tCoordinates, const ColorArray &colorArray)
		{
			return add(PointArray{
				Point(rect.x, rect.y2), Point(rect.x, rect.y), Point(rect.x2, rect.y), Point(rect.x2, rect.y2) },
				tCoordinates, colorArray);
		}

		TriangleList & TriangleList::add(const VertexArray &source)
		{
			if (source.size() < 3)
			{
				TRLERROR("Invalid number of vertex: " << source.size());
				return *this;
			}

			u32 oldSize = size();
			insert(source);
			u32 newSize = size();
			u32 newElements = newSize - oldSize;

			u32 polygonIndex(oldSize);

			for (u32 j = 1; j < source.size() - 1; j++)
			{
				indices.push_back(polygonIndex);
				indices.push_back(polygonIndex + j);
				indices.push_back(polygonIndex + j + 1);
			}
			return *this;
		}

		TriangleList & TriangleList::add(const PointArray &source, 
			const Rectanglef32 &textureRectangle, 
			const ColorArray &colorArray)
		{
			VertexArray va;
			Box box{ source };
			u32 count{ 0 };

			for (const Point p : source)
			{
				Point t(p - box.xy());
				t.x /= box.width();
				t.y /= box.height();

				Point2d result(textureRectangle.x + (textureRectangle.width() * t.x),
					textureRectangle.y + (textureRectangle.height() * t.y));

				Vertex v(p, Color(1.0f,1.0f,1.0f,1.0f), result);

				if (count < colorArray.size())
					v.color = colorArray[count];
				else
					v.color = colorArray[colorArray.size() - 1];

				va.data.push_back(v);
			}

			return add(va);
		}
	}
}
