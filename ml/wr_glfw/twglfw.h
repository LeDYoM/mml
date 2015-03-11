#ifndef __TWGLFW_H__
#define __TWGLFW_H__

#include "../TWrapper.h"
#include "../include/IOTypes.h"

#include <list>

struct GLFWwindow;

namespace ml
{
	namespace priv
	{
		class twglfw : public TWrapper
		{
		public:
			twglfw();
			virtual ~twglfw();

			bool initWindowSystem();
			void stopWindowSystem();

			TWWrapper *createNativeWindow(const WindowCreationOptions &);
			bool destroyNativeWindow(TWWrapper *);

			void setVSync(bool);

			void enterMainLoop();
			void finishFrame();
			f64 getTime();

		private:
			std::list<GLFWwindow*> registeredWindows;

			void setKeys();
			KeyCode keycodes;
			KeyModifs keyModifs;
			KeyAction keyActions;
		};
	}
}

#endif
