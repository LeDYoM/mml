#ifndef __TEXTUREOPTIONS_H__
#define __TEXTUREOPTIONS_H__
#include "../mlcconfig.h"

namespace ml
{
	namespace graph
	{
		class ML_API TextureOptions
		{
		public:
			TextureOptions();
			virtual ~TextureOptions();
			const bool linearOption() const { return linear; }
			const bool mipmapOption() const { return mipmapping; }
			const bool useAlphaOption() const { return useAlpha; }

			void setLinearOption(bool linear_) { linear = linear_; }
			void setMipmapOption(bool mipmap_) { mipmapping = mipmap_; }
			void setUseAlphaOption(bool useAlpha_) { useAlpha = useAlpha_; }
		protected:
			bool linear;
			bool mipmapping;
			bool useAlpha;
		};
	}
}
#endif
