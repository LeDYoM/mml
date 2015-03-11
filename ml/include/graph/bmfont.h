#ifndef __BMFONT__
#define __BMFONT__

#include <vector>
#include <string>
#include "Texture.h"
#include "Image.h"
#include "Resource.h"
#include "../types.h"
#include "../../openglPriv.h"
#include "../mlcconfig.h"

namespace ml
{
	namespace graph
	{
		class PageData
		{
		public:
			std::string file;
			PageData() : file("") {}
			ml::graph::Image image;
			ml::graph::Texture texture;

			PageData(const std::string& file_) :file(file_){}
		};
		class FontInfo
		{
		public:
			std::string face;
			u16 size;
			bool bold;
			bool italic;
			std::string charset;
			bool unicode;
			f32 stretchH;
			bool smooth;
			bool aa;
			Rectangle<s16> padding;
			Vector2d<s16> spacing;
			bool outline;
		};
		class KearningInfo
		{
		public:
			s16 second;
			s16 amount;
			KearningInfo(s16 second_,s16 amount_) : second(second_), amount(amount_)	{ }
			KearningInfo() : second(0), amount(0)	{ }
		};


		class CharDescriptor
		{
		public:
			Rectangle<u16> position;
			Vector2d<s16> offset;
			s16 xadvance;
			s16 page;
			std::vector<KearningInfo> kearn;

			CharDescriptor() : position(0,0,0,0), offset(0,0),
				xadvance(0), page(0) { }

			s32 GetKerningPair(int second) const
			{
				for (u32 j = 0; j < kearn.size(); ++j)
				{
					if (kearn[j].second == second)
					{
						return kearn[j].amount;
					}
				}
				return 0;
			}

		};
		template class ML_API std::vector < CharDescriptor > ;
		template class ML_API std::vector < PageData > ;

		class BMText;
		class ML_API BMFont : public Resource
		{
		protected:
			BMFont();
			~BMFont();

			bool Load(const std::string &);
		public:
			void SetColor(const Color &color_) { color = color_; }
			void SetBlend(int b) { fblend = b; }
			float height() const { return lineHeight; }
			float stringWidth(const std::string&, bool useKern) const;

		private:
			s16 lineHeight;
			s16 base;
			Size size;
			s16 pages;
			s16 outline;
			FontInfo fInfo;
			std::vector<CharDescriptor> chars;
			std::vector<PageData> pagesData;
			Color color;
			int fblend;
			bool ParseFont(const std::string&);
			friend class BMText;
			friend class ResourceManager;
		};
	}
}

#endif
