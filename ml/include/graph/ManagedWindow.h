#ifndef __MANAGERWINDOW_H__
#define __MANAGERWINDOW_H__

#include "../mlcconfig.h"
#include "../Window.h"
#include "RenderManager.h"
#include "ResourceManager.h"

namespace ml
{
	namespace graph
	{
		class ML_API ManagedWindow : public Window
		{
		public:
			ManagedWindow();
			virtual ~ManagedWindow();

			virtual void onRenderModel() = 0;
			virtual void onMouseCursorMoved(const MousePosition&) = 0;
			virtual void onMouseButtons(const MouseButtons&,const MouseButtonId) = 0;
			virtual void onResized(const Size&) = 0;
			virtual void onKey(const KeyCodeType&, const KeyCodeType&, const KeyActionType&) = 0;
			virtual void onInitialized() = 0;
			int lastReadFPS();
			void setDrawFPS(bool);
			void setAutoClear(bool);

		protected:
			RenderManager *renderManager;
			ResourceManager *resourceManager;

			virtual bool destroy() override;
			virtual bool init(const WindowCreationOptions&) override;
		private:
			void onRender();
			bool onCloseRequested();
			void onResize(const Size&);
			void onMouseMoved(const MousePosition&);
			void onMouseButtonsChanged(const MouseButtons&,const MouseButtonId);
			void onKeyChanged(const KeyCodeType&, const KeyCodeType&, const KeyActionType&);
			void onInitCompleted();

			f64 timer;
			int fpsCounter;
			int lastReadFPS_;
			bool drawFPS;
			bool autoClear;
		};
	}
}

#endif
