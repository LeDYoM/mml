#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "mlcconfig.h"
#include "types.h"
#include "IOTypes.h"
#include "WindowCreationOptions.h"
#include <string>

namespace ml
{
	namespace priv
	{
		class CorePriv;
		class TWrapper;
		struct WindowPrivate;
	}

	class ML_API Window
	{
	public:
		Window();
		virtual ~Window();

		Size getWindowSize();
		f64 getTime();
		MousePosition getCursorPos();
		KeyActionType getKeyState(const KeyCodeType &);

		void setTitle(const std::string &);

		virtual void onRender() = 0;
		virtual bool onCloseRequested() = 0;
		virtual void onResize(const Size&) = 0;
		virtual void onInitCompleted() = 0;
		virtual void onMouseMoved(const MousePosition&) = 0;
		virtual void onMouseButtonsChanged(const MouseButtons&,const MouseButtonId) = 0;
		virtual void onKeyChanged(const KeyCodeType&, const KeyCodeType&, const KeyActionType&) = 0;

	protected:
		virtual bool init(const WindowCreationOptions&);
		virtual bool destroy();

		bool hasRequestedClose();

		void doWindowLoopStep();
		void finishFrame();
	
		priv::WindowPrivate *wPriv;

		friend class priv::CorePriv;
		friend class priv::TWrapper;
	};

}

#endif
