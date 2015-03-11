#ifndef __RENDERMANAGER_H__
#define __RENDERMANAGER_H__

#include "../types.h"
#include "TransformMatrix4.h"
#include <list>

namespace ml
{
	namespace graph
	{
		class TriangleList;
		class Shape;
		class Texture;
		class VAOWrapper;

		class ML_API RenderManager
		{
		public:
			RenderManager();
			virtual ~RenderManager();

			void registerForRender(Shape &shape);
			void unRegisterForRender(Shape &shape);

			void RenderVAO(VAOWrapper *, const Texture * = nullptr);
			void setPerspective(const Rectanglef32 &perspective);
			void setViewPort(const Rectangleu32 &viewPort);
			void Init();
			void Clear();

			void applyModelViewTransform(const TransformationMatrix &mvm);

		private:
			void setPerspective(const TransformationMatrix &m);
			VAOWrapper *initVAO(const TriangleList &trList);
			void deleteVAO(VAOWrapper *vaow);
			TransformationMatrix projectionMatrix;
			TransformationMatrix modelViewMatrix;
		};
	}
}

#endif
