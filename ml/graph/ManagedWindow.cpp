#include "../include/graph/ManagedWindow.h"
#include "../include/graph/RenderManager.h"

namespace ml
{
	namespace graph
	{
		ManagedWindow::ManagedWindow() :Window(),
			timer(0), fpsCounter(0), lastReadFPS_(-1), drawFPS(false), autoClear(true),
			renderManager(nullptr), resourceManager(nullptr)
		{
		}

		ManagedWindow::~ManagedWindow()
		{
		}

		bool ManagedWindow::destroy()
		{
			if (renderManager)
			{
				delete renderManager;
				renderManager = nullptr;
			}

			if (resourceManager)
			{
				delete resourceManager;
				resourceManager = nullptr;
			}
			return Window::destroy();
		}

		bool ManagedWindow::init(const WindowCreationOptions&wco)
		{
			bool result = Window::init(wco);

			if (result)
			{
				renderManager = new RenderManager;
				resourceManager = new ResourceManager;
			}
			return result;
		}

		void ManagedWindow::onRender()
		{
			if (autoClear)
			{
				renderManager->Clear();
			}
			onRenderModel();
			if (getTime() - timer > 1)
			{
				timer = getTime();
				if (drawFPS)
					setTitle("FPS: " + std::to_string(fpsCounter));
				lastReadFPS_ = fpsCounter;
				fpsCounter = 0;
			}
			fpsCounter++;
		}

		bool ManagedWindow::onCloseRequested()
		{
			return true;
		}

		void ManagedWindow::onResize(const Size &newSize)
		{
			onResized(newSize);
		}

		void ManagedWindow::setDrawFPS(bool nv)
		{
			drawFPS = nv;
		}

		void ManagedWindow::onMouseMoved(const MousePosition&newPos)
		{
			onMouseCursorMoved(newPos);
		}

		void ManagedWindow::onMouseButtonsChanged(const MouseButtons&newButtons, const MouseButtonId actionButton)
		{
			onMouseButtons(newButtons,actionButton);
		}

		void ManagedWindow::onKeyChanged(const KeyCodeType& keyCode, const KeyCodeType& modifCode, const KeyActionType &action)
		{
			onKey(keyCode, modifCode, action);
		}

		void ManagedWindow::onInitCompleted()
		{
			renderManager->Init();
			onInitialized();
		}

	}
}
