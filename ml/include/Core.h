#ifndef __CORE_H__
#define __CORE_H__

#include "types.h"

namespace ml
{
	class Window;
	struct WindowCreationOptions;
	class Core
	{
	public:
		Core() {}
		virtual ~Core() {}

		virtual void init() = 0;
		virtual void finish() = 0;

		template <class T> T *getNewWindow(const WindowCreationOptions &options)
		{
			Window *w = new T();
			registerWindow(w, options);
			return w;
		}

		virtual bool registerWindow(Window *,const WindowCreationOptions&) = 0;
		virtual bool unregisterWindow(Window *win) = 0;
		virtual f64 getTime() = 0;
		virtual void enterMainLoop() = 0;
		virtual void setVsync(bool) = 0;

		virtual void finishLoop() = 0;
		virtual void deleteWindow(Window *) = 0;
	};
}

#endif
