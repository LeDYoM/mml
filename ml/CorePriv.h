#ifndef __COREPRIVATE_H__
#define __COREPRIVATE_H__

#include "include/Core.h"
#include "TWrapper.h"
#include <vector>

namespace ml
{
	namespace priv
	{
		class CorePriv : public Core
		{
		public:
			CorePriv();
			virtual ~CorePriv();

			void init();
			void finish();

			bool registerWindow(Window *, const WindowCreationOptions&);
			bool unregisterWindow(Window *);
			void deleteWindow(Window *);

			void enterMainLoop();
			int doMainLoopStep();
			void finishLoop();
			void setVsync(bool);
			TWrapper *getWrapper() const { return twrapper; }

			f64 getTime();

		private:
			TWrapper *twrapper;
			std::vector<Window*> windows;

		};
	}
}

#endif
