#ifndef _TWWGLFW_H__
#define _TWWGLFW_H__

#include "twglfw.h"
#include "../include/IOTypes.h"

namespace ml
{
	namespace priv
	{
		class twwglfw : public TWWrapper
		{
		public:
			twwglfw();
			virtual ~twwglfw();

			bool windowIsRequestingClose();
			void postDrawWindow();
			Size getWindowSize();
			void setWindowTitle(const std::string&);
			const MousePosition &getCursorPosition();
			MouseButtonState getMouseButtonState(const MouseButtonId &);
			const MouseButtons &getMouseButtonsStates();
			void linkToWindow(Window *);
		private:
			GLFWwindow *window;
			friend class twglfw;

			void registerCallbacksForWindow(GLFWwindow *);
			static void onRedraw(GLFWwindow *);
			static void onResize(GLFWwindow *, int, int);
			static void onCursorMoved(GLFWwindow *, double, double);
			static void onMouseButtonsStateChanged(GLFWwindow*, int, int, int);
			static void onKeyChanged(GLFWwindow*, int, int, int, int);
			KeyActionType getKeyState(const KeyCodeType &);

			static MousePosition cachedMousePosition;
			static MouseButtons cacheMouseButtons;
		};
	}
}

#endif
