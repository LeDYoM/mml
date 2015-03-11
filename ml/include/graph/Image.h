#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "../types.h"
#include "../mlcconfig.h"
#include <string>

namespace ml
{
	namespace graph
	{
		class ML_API Image
		{
		public:
			Image();
			Image(const std::string &fileName);
			bool Load(const std::string &fileName);
			virtual ~Image();

			void remove();
			const bool isEmpty() const { return data == nullptr; }
			const u8 *getRawData() const { return data; }
			const Size &getSize() const { return size; }
			const s32 getBPP() const { return bpp; }

			const Color getPixel(const Size &) const;
			void setPixel(const Size &, const Color &);
			void InvertY();
		private:
			u8 *data;
			Size size;
			s32 bpp;
		};
	}
}

#endif
