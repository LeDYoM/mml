#ifndef __IRENDERIZABLE_H__
#define __IRENDERIZABLE_H__

#include "RenderManager.h"
#include "../mlcconfig.h"

namespace ml
{
	namespace graph
	{
		class ML_API IRenderizable
		{
		public:

			IRenderizable(){}
			virtual ~IRenderizable(){}

			virtual void Render(RenderManager &renderManager) = 0;
		};
	}
}
#endif
