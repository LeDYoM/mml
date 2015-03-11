#include "../include/graph/Shape.h"
#include "../include/graph/Texture.h"
#include "../mlprivcconfig.h"

namespace ml
{
	namespace graph
	{
		Shape::Shape() :vaow(nullptr)
		{

		}

		Shape::~Shape()
		{
		}

		bool Shape::Init(RenderManager &renderManager)
		{
			renderManager.registerForRender(*this);
			return true;
		}

		bool Shape::Finish(RenderManager &renderManager)
		{
			renderManager.unRegisterForRender(*this);
			return false;
		}

		void Shape::Render(RenderManager &renderManager)
		{
			transform.loadIdentity();
			transform.setPosition(position);
			transform.setScale(scale);
			renderManager.applyModelViewTransform(transform);
			renderManager.RenderVAO(vaow, texture);
		}
	}
}
