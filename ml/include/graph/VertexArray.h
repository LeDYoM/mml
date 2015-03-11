#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "../mlcconfig.h"
#include "../types.h"

namespace ml
{
	namespace graph
	{
		class ML_API VertexArray
		{
		public:
			VertexData data;

			VertexArray();
			virtual ~VertexArray();
			VertexArray(const VertexArray &other) = delete;
			VertexArray(const std::vector<Vertex> &data);
			VertexArray(const std::initializer_list<Vertex> &data);
			VertexArray(VertexArray&&other);
			VertexArray &operator=(VertexArray&&);
			VertexArray &operator=(const VertexArray&) = delete;
			VertexArray& insert(const VertexArray&other);

			u32 size() const { return data.size(); }
			void clear();

			const Point &getPointAt(u32 index) const { return data[index].position; }

			const VertexData &getData() const { return data; }
			const Vertex *getDataPointer() const { return &(getData()[0]); }
			const Point *getPositionsPointer() const { return &(getData()[0].position); }
			const Point2d *getTextureCoordinatesPointer() const { return &(getData()[0].tCoordinates); }
			const Color* getColorsPointer() const { return &(getData()[0].color); }
		};
	}
}

#endif
