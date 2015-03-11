#ifndef __TWRAPPER_H__
#define __TWRAPPER_H__

#include "TWWrapper.h"
#include "include/types.h"

namespace ml
{
	struct WindowCreationOptions;

	namespace priv
	{
		class TWrapper
		{
		public:

			TWrapper() {}
			virtual ~TWrapper() {}

			virtual bool initWindowSystem() = 0;
			virtual void stopWindowSystem() = 0;

			virtual TWWrapper *createNativeWindow(const WindowCreationOptions &) = 0;
			virtual bool destroyNativeWindow(TWWrapper *) = 0;

			virtual void setVSync(bool) = 0;

			virtual f64 getTime() = 0;

			virtual void enterMainLoop() = 0;
			virtual void finishFrame() = 0;
		};
	}
}

#endif
