#ifndef __WINDOWCREATIONOPTIONS_H__
#define __WINDOWCREATIONOPTIONS_H__

#include <string>
#include "types.h"

namespace ml
{
	struct WindowCreationOptions
	{
	public:
		WindowCreationOptions()	{}
		virtual ~WindowCreationOptions() {}
		std::string Title = "ML";
		Size size = Size(640, 480);
		bool vsync = false;
		s32 redBits = 8;
		s32 greenBits = 8;
		s32 blueBits = 8;
		s32 alphaBits = 8;
		bool resizable = true;
		bool fullScreen = false;
		bool border = true;
		u16 oglVersion = 1;
		u16 oglSubversion = 0;
		bool useCompatibility = false;

	};
}

#endif
