#include "../include/graph/Image.h"
#include "soil/SOIL.h"
#include "../mlprivcconfig.h"

#include "soil/stb_image_aug.h"

#include <stdlib.h>
#include <string.h>

namespace ml
{
	namespace graph
	{
		Image::Image() :data(nullptr), size(0, 0)
		{
		}

		Image::Image(const std::string &fileName)
		{
			if (!Load(fileName))
			{
				remove();
			}
		}

		bool Image::Load(const std::string &fileName)
		{
			int force_channels(SOIL_LOAD_RGBA);
			data = SOIL_load_image(fileName.c_str(), (int*)&(size.x), (int*)&(size.y), &bpp, force_channels);

			if (!data)
			{
				LOG_PRIVATE_DEBUG_ERROR("Error loading " << fileName.c_str() << ":" << stbi_failure_reason());
				return false;
			}
			LOG_PRIVATE_DEBUG("File " << fileName << " loaded. ImageCharacteristics:");
			LOG_PRIVATE_DEBUG("\tImage size: " << size.x << "," << size.y);
			LOG_PRIVATE_DEBUG("\tChannels: " << bpp);
//			InvertY();
			return true;
		}

		Image::~Image()
		{
			remove();
		}

		void Image::remove()
		{
			if (data)
			{
				SOIL_free_image_data(data);
				data = nullptr;
				size = Size(0, 0);
				bpp = 0;
			}
		}

		void  Image::InvertY()
		{
			unsigned int i, j;
			for (j = 0; j * 2 < size.y; ++j)
			{
				int index1 = j * size.x * bpp;
				int index2 = (size.y - 1 - j) * size.x * bpp;
				for (i = size.x * bpp; i > 0; --i)
				{
					unsigned char temp = data[index1];
					data[index1] = data[index2];
					data[index2] = temp;
					++index1;
					++index2;
				}
			}
		}

		const Color Image::getPixel(const Size &position) const
		{
			u32 offset = ((position.y * size.x) + position.x) * bpp;
			Color c;
			c.setRByte(data[offset]);
			switch (bpp)
			{
			case 2:
				c.setGByte(data[offset]);
				c.setBByte(data[offset]);
				c.setAByte(data[offset + 1]);
				break;
			case 3:
				c.setGByte(data[offset + 1]);
				c.setBByte(data[offset + 2]);
				c.a = 1.0;
			case 4:
				c.setGByte(data[offset + 1]);
				c.setBByte(data[offset + 2]);
				c.setAByte(data[offset + 3]);
			}
			return c;
		}

		void Image::setPixel(const Size &position, const Color &c)
		{
			u32 offset = ((position.y * size.x) + position.x) * bpp;
			data[offset] = c.getRByte();
			switch (bpp)
			{
			case 2:
				data[offset + 1] = c.getAByte();
				break;
			case 3:
				data[offset + 1] = c.getGByte();
				data[offset + 2] = c.getBByte();
			case 4:
				data[offset + 1] = c.getGByte();
				data[offset + 2] = c.getBByte();
				data[offset + 3] = c.getAByte();
			}
		}
	}
}
