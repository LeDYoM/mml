#include "../include/graph/TextureOptions.h"

namespace ml
{
	namespace graph
	{
		TextureOptions::TextureOptions()
		{
			linear = true;
			mipmapping = false;
			useAlpha = true;
		}

		TextureOptions::~TextureOptions()
		{
		}
	}
}
