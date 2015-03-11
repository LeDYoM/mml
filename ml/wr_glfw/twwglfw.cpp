#include "twwglfw.h"
#include "../mlprivcconfig.h"
#include "../include/Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../openglPriv.h"

namespace ml
{
	namespace priv
	{
		MousePosition twwglfw::cachedMousePosition = MousePosition(0, 0);
		MouseButtons twwglfw::cacheMouseButtons = { static_cast<MouseButtonState>(0) };

		twwglfw::twwglfw() :window(0)
		{
		}


		twwglfw::~twwglfw()
		{
		}

		bool twwglfw::windowIsRequestingClose()
		{
			return glfwWindowShouldClose(window) == GL_TRUE;
		}

		void twwglfw::postDrawWindow()
		{
			glfwSwapBuffers(window);
		}

		Size twwglfw::getWindowSize()
		{
			int w, h;
			glfwGetFramebufferSize(window, &w, &h);
			return Size(w, h);
		}

		void twwglfw::setWindowTitle(const std::string &title)
		{
			glfwSetWindowTitle(window, title.c_str());
		}

		const MousePosition &twwglfw::getCursorPosition()
		{
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			cachedMousePosition.x = static_cast<ml::MouseRange>(xPos);
			cachedMousePosition.y = static_cast<ml::MouseRange>(yPos);
			return cachedMousePosition;
		}

		MouseButtonState twwglfw::getMouseButtonState(const MouseButtonId &bid)
		{
//			return glfwGetMouseButton(window, (s32)bid);
			return cacheMouseButtons.pressed[bid];
		}

		const MouseButtons & twwglfw::getMouseButtonsStates()
		{
			return cacheMouseButtons;
		}

		KeyActionType twwglfw::getKeyState(const KeyCodeType &keyCode)
		{
			return static_cast<KeyActionType>(glfwGetKey(window, static_cast<int>(keyCode)));
		}

		void twwglfw::linkToWindow(Window *win)
		{
			glfwSetWindowUserPointer(window, win);
			registerCallbacksForWindow(window);
		}

		void twwglfw::registerCallbacksForWindow(GLFWwindow *window)
		{
			glfwSetWindowRefreshCallback(window, onRedraw);
			glfwSetWindowSizeCallback(window, onResize);
			glfwSetCursorPosCallback(window, onCursorMoved);
			glfwSetMouseButtonCallback(window, onMouseButtonsStateChanged);
			glfwSetKeyCallback(window, onKeyChanged);
		}

#define DO_IFWINDOW(code)Window *win = static_cast<Window*>(glfwGetWindowUserPointer(window)); \
		if (win) \
			code

		// Callbacks (Not in interface)
		void twwglfw::onRedraw(GLFWwindow *window)
		{
			DO_IFWINDOW({})
		}

		void twwglfw::onResize(GLFWwindow *window, int w, int h)
		{
			DO_IFWINDOW({
				win->onResize(Size(w, h));
			})
		}

		void twwglfw::onCursorMoved(GLFWwindow *window, double x, double y)
		{
			DO_IFWINDOW({
				cachedMousePosition.x = static_cast<MouseRange>(x);
				cachedMousePosition.y = static_cast<MouseRange>(y);
				win->onMouseMoved(cachedMousePosition);
			})
		}

		void twwglfw::onMouseButtonsStateChanged(GLFWwindow*window, int button, int state, int modifiers)
		{
			DO_IFWINDOW({
				cacheMouseButtons.pressed[button] = state;
				win->onMouseButtonsChanged(cacheMouseButtons,static_cast<MouseButtonId>(button));
			})
		}

		void twwglfw::onKeyChanged(GLFWwindow*window, int key, int scancode, int action, int mods)
		{
			DO_IFWINDOW({
				win->onKeyChanged(static_cast<KeyCodeType> (key),
				static_cast<KeyCodeType>(mods), static_cast<KeyActionType>(action));
			})
		}
	}
}
