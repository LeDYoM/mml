#ifndef __BMTEXT_H__
#define __BMTEXT_H__

#include "bmfont.h"
#include <string>
#include <vector>
#include "../types.h"
#include "../mlcconfig.h"
#include "TriangleList.h"
#include "IRenderizable.h"
#include "Shape.h"

namespace ml
{
	namespace graph
	{

		class ML_API BMText : public Shape
		{
		public:
			BMText();
			bool Init(const BMFont *font_, const std::string &text,bool useKern=true,const Color& color=Color(1.0f,1.0f,1.0f));
			virtual ~BMText();

			virtual void Render(RenderManager &renderManager) override;

		private:
			const BMFont *font;
		};
	}
}

#endif
