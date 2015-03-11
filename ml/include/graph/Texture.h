#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "../mlcconfig.h"
#include "../types.h"
#include "Image.h"
#include <string>
#include "TextureOptions.h"

namespace ml
{
	namespace graph
	{
		class ML_API Texture : public TextureOptions
		{
		public:
			Texture();
			Texture(const std::string &fileName);
			virtual ~Texture();

			bool Load(const std::string &fileName);
			bool Load(const Image &image);
			static Texture *fromImage(const Image &);
			void Remove();

			const bool isValid() const { return internalid > 0; }
			const u32 id() const { return internalid; }

			void use() const;
			void unuse() const;

		private:
			Size size;
			u32 internalid;

		};
	}
}

#endif
