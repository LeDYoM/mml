#include "../include/graph/BMText.h"
#include "../include/graph/RenderManager.h"
#include "../include/graph/TriangleList.h"
#include "../include/types.h"

namespace ml
{
	namespace graph
	{
		BMText::BMText()
		{
		}

		bool BMText::Init(const BMFont *font_, const std::string &text, bool useKern/*=true*/, const Color& color/*=Color(1.0f,1.0f,1.0f)*/)
		{
			this->position = position;
			font = font_;
			Vector2d<f32> cur_;
			Vector2d<f32> nextCharPos;
			Vector2d<f32> dest;
			f32 adv = 1.0f / (f32)font_->size.x;
			const CharDescriptor  *f;
			//f32 fscale = font_.fscale;
			Rectanglef32 advancedPos;
			Rectanglef32 cur;

			for (u32 i = 0; i < text.size(); ++i)
			{
				f = &(font_->chars[text[i]]);
				cur_ = nextCharPos + f->offset;
				dest = cur_ + f->position.size();
				advancedPos = static_cast<Rectanglef32>(f->position)*adv;
				cur = Rectanglef32(cur_, dest);
				//				cur *= fscale;

				if (useKern && text.size() > 1 && i < (text.size() - 1))
				{
					nextCharPos.x += f->GetKerningPair(text[i + 1]);
				}

				nextCharPos.x += f->xadvance;
				triangleList.addQuad(cur, advancedPos);
			}
			texture = &(font->pagesData[0].texture);
			return true;
		}

		BMText::~BMText()
		{
		}

		void BMText::Render(RenderManager &renderManager)
		{
			Shape::Render(renderManager);
		}
	}
}
