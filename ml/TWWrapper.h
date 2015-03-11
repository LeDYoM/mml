#ifndef __TWWRAPPER_H__
#define __TWWRAPPER_H__

#include "include/types.h"
#include "include/IOTypes.h"
#include <string>

namespace ml
{
	class Window;
	namespace priv
	{
		class TWWrapper
		{
		public:
			TWWrapper() {}
			virtual ~TWWrapper() {}

			virtual bool windowIsRequestingClose() = 0;
			virtual void postDrawWindow() = 0;
			virtual Size getWindowSize() = 0;
			virtual void setWindowTitle(const std::string&) = 0;
			virtual const MousePosition &getCursorPosition() = 0;
			virtual MouseButtonState getMouseButtonState(const MouseButtonId &) = 0;
			virtual const MouseButtons &getMouseButtonsStates() = 0;
			virtual void linkToWindow(Window *) = 0;
			virtual KeyActionType getKeyState(const KeyCodeType &) = 0;
		};
	}
}

#endif
