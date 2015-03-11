#include "CorePriv.h"
#include "TWrapperLoader.h"
#include "include/Window.h"
#include "logPriv.h"

namespace ml
{
	namespace priv
	{
		CorePriv::CorePriv()
		{
			TWrapperLoader twl;
			twrapper = twl.createWindowAndInputWrapper();

			twrapper->initWindowSystem();
		}

		CorePriv::~CorePriv()
		{
			for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end();++it)
			{
				delete (*it);
			}

			if (twrapper)
			{
				delete twrapper;
				twrapper = 0;
			}
		}

		void CorePriv::init()
		{
			twrapper->initWindowSystem();
		}

		void CorePriv::finish()
		{
			twrapper->stopWindowSystem();
		}

		bool CorePriv::registerWindow(Window *win, const WindowCreationOptions &wco)
		{
			windows.push_back(win);
			win->init(wco);
			win->onInitCompleted();
			LOG_PRIVATE_DEBUG("Window added to windows core list. Available windows: "<<windows.size());
			return true;
		}

		bool CorePriv::unregisterWindow(Window *win)
		{
			bool exit = false;
			for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end() && !exit;)
			{
				if (*(it) == win)
				{
					win->destroy();
					windows.erase(it);
					it = windows.end();
					exit = true;
				}
				else
					++it;
			}
			if (exit)
			{
				LOG_PRIVATE_DEBUG("Window deleted from window core list. Pending windows: " << windows.size());
			}
			else
			{
				LOG_PRIVATE_DEBUG_ERROR("Trying to unregister a not registered window");
			}
			return exit;
		}

		void CorePriv::enterMainLoop()
		{
			bool exit = false;
			while (!exit)
			{
				int activeWindows = doMainLoopStep();
				if (activeWindows < 1)
				{
					LOG_PRIVATE_DEBUG("No pending active windows, exiting from main loop");
					exit = true;
				}
			}
		}

		int CorePriv::doMainLoopStep()
		{
			int activeWindows(0);
			for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end(); ++it)
			{
				++activeWindows;
				Window *win = *it;
				if (!(win->hasRequestedClose()))
				{
					win->doWindowLoopStep();
				}
				else
				{
					bool isClosing = win->onCloseRequested();
					if (isClosing)
						--activeWindows;
				}
			}
			finishLoop();
			return activeWindows;
		}

		void CorePriv::finishLoop()
		{
			twrapper->finishFrame();
		}

		void CorePriv::setVsync(bool on)
		{
			twrapper->setVSync(on);
		}

		ml::f64 CorePriv::getTime()
		{
			return twrapper->getTime();
		}

		void CorePriv::deleteWindow(Window *win)
		{
			for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end();)
			{
				if ((*it) == win)
				{
					windows.erase(it);
				}
				else
					++it;
			}

			delete win;
		}

	}
}
