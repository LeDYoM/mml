#include "include/Window.h"

#include "coreLoaderPriv.h"
#include "include/CoreLoader.h"
#include "CorePriv.h"
#include "openglPriv.h"
#include "WindowPrivate.h"
#include "mlprivcconfig.h"

namespace ml
{
	Window::Window() :wPriv(new priv::WindowPrivate)
	{
	}

	Window::~Window()
	{
		destroy();
		delete wPriv;
	}

	bool Window::init(const WindowCreationOptions &wco)
	{
		wPriv->winWrapper = priv::getPrivCore()->getWrapper()->createNativeWindow(wco);
		if (wPriv->winWrapper)
			wPriv->winWrapper->linkToWindow(this);

		LOG_PRIVATE_DEBUG("OpenGL version in this platform: " << glGetString(GL_VERSION));
		LOG_PRIVATE_DEBUG("OpenGL vendor: " << glGetString(GL_VENDOR));
		LOG_PRIVATE_DEBUG("OpenGL renderer: " << glGetString(GL_RENDERER));
		LOG_PRIVATE_DEBUG("OpenGL extensions: " << glGetString(GL_EXTENSIONS));
		int m, n;
		glGetIntegerv(GL_MAJOR_VERSION, &m);
		glGetIntegerv(GL_MINOR_VERSION, &n);
		LOG_PRIVATE_DEBUG("OpenGL version: " << m << "." << n);


		return wPriv != 0;
	}

	bool Window::destroy()
	{
		if (wPriv->winWrapper)
		{
			bool destroyed = priv::getPrivCore()->getWrapper()->destroyNativeWindow(wPriv->winWrapper);
			wPriv->winWrapper = nullptr;
			return destroyed;
		}
		return false;
	}

	MousePosition Window::getCursorPos()
	{
		MousePosition cPos = wPriv->winWrapper->getCursorPosition();
		return cPos;
	}

	bool Window::hasRequestedClose()
	{
		return wPriv->winWrapper->windowIsRequestingClose();
	}

	void Window::finishFrame()
	{
		return wPriv->winWrapper->postDrawWindow();
	}

	Size Window::getWindowSize()
	{
		Size sz = wPriv->winWrapper->getWindowSize();
		return sz;
	}

	f64 Window::getTime()
	{
		return getCore()->getTime();
	}

	void Window::setTitle(const std::string &title_)
	{
		wPriv->winWrapper->setWindowTitle(title_.c_str());
	}

	void Window::doWindowLoopStep()
	{
		onRender();
		finishFrame();
	}

	KeyActionType Window::getKeyState(const KeyCodeType &key)
	{
		return wPriv->winWrapper->getKeyState(key);
	}

}
