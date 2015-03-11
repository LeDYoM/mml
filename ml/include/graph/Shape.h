#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "../mlcconfig.h"
#include "Box.h"
#include "TriangleList.h"
#include "IRenderizable.h"
#include "ITransformable.h"

namespace ml
{
	namespace graph
	{
		class Texture;
		class VAOWrapper;
		class ML_API Shape : public IRenderizable, public ITransformable
		{
		public:
			Shape(const Shape&) = delete;
			virtual ~Shape();
			void setTexture(const Texture *texture_) { texture = texture_; }
			const Texture *getTexture() const { return texture; }

			virtual void Render(RenderManager &renderManager) override;

			const TriangleList &getTriangleList() const { return triangleList; }

		protected:
			Shape();
			virtual bool Init(RenderManager &renderManager);
			virtual bool Finish(RenderManager &renderManager);

			TriangleList triangleList;
			const Texture *texture;
		private:
			VAOWrapper *vaow;
		};
	}
}

#endif
