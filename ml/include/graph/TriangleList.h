#ifndef __TRIANGLELIST_H__
#define __TRIANGLELIST_H__

#include <vector>
#include "../types.h"
#include "../../mlprivcconfig.h"
#include "VertexArray.h"
#include <memory>

namespace ml
{
	namespace graph
	{
		class ML_API TriangleList : public VertexArray
		{
		public:
			IndexArray indices;
			bool hasIndices() const { return indices.size() > 0; }
			const IndexArray &getIndices() const { return indices; }
			const u16 *getIndicesPointer() const { return &(getIndices()[0]); }

			TriangleList();
			TriangleList(const TriangleList &other) = delete;
			TriangleList &operator=(const VertexArray&) = delete;
			virtual ~TriangleList();

			// Generators.
			TriangleList &addCircle(f32 radius, u32 nVertex, 
				const Rectanglef32 &textureRectangle = Rectanglef32(0.0f, 0.0f, 1.0f, 1.0f),
				const ColorArray &colorArray = { Color(1.0f, 1.0f, 1.0f) });
			TriangleList &addQuad(const Rectanglef32 &rect, 
				const Rectanglef32 &textureRectangle = Rectanglef32(0.0f,0.0f,1.0f,1.0f),
				const ColorArray &colorArray = { Color(1.0f, 1.0f, 1.0f) });
		public:
			TriangleList &add(const VertexArray &source);
			TriangleList &add(const PointArray &source, 
				const Rectanglef32 &textureRectangle, 
				const ColorArray &colorArray);

			friend class RenderManager;
		};
	}
}

#endif
