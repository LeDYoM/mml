#include "twglfw.h"
#include "twwglfw.h"
#include "../mlprivcconfig.h"
#include "../include/WindowCreationOptions.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../openglPriv.h"

namespace ml
{
	namespace priv
	{
		static twglfw *instance(0);

		twglfw::twglfw()
		{
			LOG_PRIVATE_DEBUG("Creating wrapper that uses GLFW. Version: " << 
				GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION)
			LOG_PRIVATE_DEBUG("Creating twglfw...");
			if (instance)
			{
				LOG_ERROR("Creating more that one twglfw is not allowed");
			}
			instance = this;
		}


		twglfw::~twglfw()
		{
			instance = 0;
		}

		bool twglfw::initWindowSystem()
		{
			bool result = (glfwInit() == GL_TRUE);
			if (result)
			{
				setKeys();
			}
			return result;
		}

		void twglfw::stopWindowSystem()
		{
			glfwTerminate();
		}

		TWWrapper *twglfw::createNativeWindow(const WindowCreationOptions &wco)
		{
			LOG_PRIVATE_DEBUG("setting context format to RGBA: (" <<
				wco.redBits << "." << wco.greenBits << "." << wco.blueBits << "." << wco.alphaBits<<")");
			glfwWindowHint(GLFW_RED_BITS, wco.redBits);
			glfwWindowHint(GLFW_GREEN_BITS, wco.greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, wco.blueBits);
			glfwWindowHint(GLFW_ALPHA_BITS, wco.alphaBits);

			glfwWindowHint(GLFW_RESIZABLE, wco.resizable);
			glfwWindowHint(GLFW_DECORATED, wco.border);

//			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, wco.oglVersion);
//			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, wco.oglSubversion);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

//			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


			GLFWmonitor *monitor(0);
			if (wco.fullScreen)
			{
				monitor = glfwGetPrimaryMonitor();
			}

			GLFWwindow *win = glfwCreateWindow(wco.size.x, wco.size.y, wco.Title.c_str(), monitor, NULL);
			if (!win)
			{
				return 0;
			}

			glfwMakeContextCurrent(win);

			u32 result = glewInit();
			if (result != GLEW_OK)
			{
				LOG_PRIVATE_DEBUG_ERROR("Error initializing glew");
				return false;
			}

			twwglfw *wwrapper = new twwglfw();
			wwrapper->window = win;

			LOG_PRIVATE_DEBUG("Native window created successfully");

			LOG_PRIVATE_DEBUG("Window register...");
			registeredWindows.push_back(win);
			setVSync(wco.vsync);

			LOG_PRIVATE_DEBUG("Finished window creation.");
			return wwrapper;
		}

		bool twglfw::destroyNativeWindow(TWWrapper *wwrapper)
		{
			if (wwrapper)
			{
				twwglfw *mrwrapper = dynamic_cast<twwglfw*>(wwrapper);
				if (mrwrapper)
				{
					GLFWwindow *win = mrwrapper->window;
					if (win)
					{
						size_t sizeBefore = registeredWindows.size();
						registeredWindows.remove(win);
						if (registeredWindows.size() != (sizeBefore - 1))
						{
							LOG_PRIVATE_DEBUG_ERROR("Error deleting window from registered");
						}
						glfwDestroyWindow(win);
						LOG_PRIVATE_DEBUG("Window destroyed");
						return true;
					}
					else
					{
						LOG_PRIVATE_DEBUG_ERROR("Error destroying window");
						return false;
					}
				}
				LOG_PRIVATE_DEBUG_ERROR("Error: Window wrapper invalid is not a valid twwrapper");
				return false;
			}
			LOG_PRIVATE_DEBUG_ERROR("Error: Window wrapper invalid is null");
			return false;
		}

		void twglfw::enterMainLoop()
		{
			bool exit = false;
			while (!exit)
			{
				finishFrame();
			}
		}

		void twglfw::finishFrame()
		{
			glfwPollEvents();
		}

		f64 twglfw::getTime()
		{
			return (f64)(glfwGetTime());
		}

		void twglfw::setVSync(bool val)
		{
			glfwSwapInterval(val ? 1 : 0);
		}

		void twglfw::setKeys()
		{
			keycodes.Unknown = GLFW_KEY_UNKNOWN;
			keycodes.Space = GLFW_KEY_SPACE;
			keycodes.Apostrphe = GLFW_KEY_APOSTROPHE;
			keycodes.Comma = GLFW_KEY_COMMA;
			keycodes.Minus = GLFW_KEY_MINUS;
			keycodes.Perios = GLFW_KEY_PERIOD;
			keycodes.Slash = GLFW_KEY_SLASH;
			keycodes.Number0 = GLFW_KEY_0;
			keycodes.Number1 = GLFW_KEY_1;
			keycodes.Number2 = GLFW_KEY_2;
			keycodes.Number3 = GLFW_KEY_3;
			keycodes.Number4 = GLFW_KEY_4;
			keycodes.Number5 = GLFW_KEY_5;
			keycodes.Number6 = GLFW_KEY_6;
			keycodes.Number7 = GLFW_KEY_7;
			keycodes.Number8 = GLFW_KEY_8;
			keycodes.Number9 = GLFW_KEY_9;
			keycodes.Semicolon = GLFW_KEY_SEMICOLON;
			keycodes.Equal = GLFW_KEY_EQUAL;
			keycodes.KeyA = GLFW_KEY_A;
			keycodes.KeyB = GLFW_KEY_B;
			keycodes.KeyC = GLFW_KEY_C;
			keycodes.KeyD = GLFW_KEY_D;
			keycodes.KeyE = GLFW_KEY_E;
			keycodes.KeyF = GLFW_KEY_F;
			keycodes.KeyG = GLFW_KEY_G;
			keycodes.KeyH = GLFW_KEY_H;
			keycodes.KeyI = GLFW_KEY_I;
			keycodes.KeyJ = GLFW_KEY_J;
			keycodes.KeyK = GLFW_KEY_K;
			keycodes.KeyL = GLFW_KEY_L;
			keycodes.KeyM = GLFW_KEY_M;
			keycodes.KeyN = GLFW_KEY_N;
			keycodes.KeyO = GLFW_KEY_O;
			keycodes.KeyP = GLFW_KEY_P;
			keycodes.KeyQ = GLFW_KEY_Q;
			keycodes.KeyR = GLFW_KEY_R;
			keycodes.KeyS = GLFW_KEY_S;
			keycodes.KeyT = GLFW_KEY_T;
			keycodes.KeyU = GLFW_KEY_U;
			keycodes.KeyV = GLFW_KEY_V;
			keycodes.KeyW = GLFW_KEY_W;
			keycodes.KeyX = GLFW_KEY_X;
			keycodes.KeyY = GLFW_KEY_Y;
			keycodes.KeyZ = GLFW_KEY_Z;
			keycodes.LeftBracket = GLFW_KEY_LEFT_BRACKET;
			keycodes.BackSlash = GLFW_KEY_BACKSLASH;
			keycodes.RightBracket = GLFW_KEY_RIGHT_BRACKET;
			keycodes.GraveAccent = GLFW_KEY_GRAVE_ACCENT;
			keycodes.Unknown1 = GLFW_KEY_WORLD_1;
			keycodes.Unknown2 = GLFW_KEY_WORLD_2;
			keycodes.Escape = GLFW_KEY_ESCAPE;
			keycodes.Enter = GLFW_KEY_ENTER;
			keycodes.Tab = GLFW_KEY_TAB;
			keycodes.Backspace = GLFW_KEY_BACKSPACE;
			keycodes.Insert = GLFW_KEY_INSERT;
			keycodes.Delete = GLFW_KEY_DELETE;
			keycodes.Right = GLFW_KEY_RIGHT;
			keycodes.Left = GLFW_KEY_LEFT;
			keycodes.Down = GLFW_KEY_DOWN;
			keycodes.Up = GLFW_KEY_UP;
			keycodes.PageUp = GLFW_KEY_PAGE_UP;
			keycodes.PageDown = GLFW_KEY_PAGE_DOWN;
			keycodes.Home = GLFW_KEY_HOME;
			keycodes.End = GLFW_KEY_END;
			keycodes.CapsLock = GLFW_KEY_CAPS_LOCK;
			keycodes.ScrollLock = GLFW_KEY_SCROLL_LOCK;
			keycodes.NumLock = GLFW_KEY_NUM_LOCK;
			keycodes.PrintScreen = GLFW_KEY_PRINT_SCREEN;
			keycodes.Pause = GLFW_KEY_PAUSE;
			keycodes.F1 = GLFW_KEY_F1;
			keycodes.F2 = GLFW_KEY_F2;
			keycodes.F3 = GLFW_KEY_F3;
			keycodes.F4 = GLFW_KEY_F4;
			keycodes.F5 = GLFW_KEY_F5;
			keycodes.F6 = GLFW_KEY_F6;
			keycodes.F7 = GLFW_KEY_F7;
			keycodes.F8 = GLFW_KEY_F8;
			keycodes.F9 = GLFW_KEY_F9;
			keycodes.F10 = GLFW_KEY_F10;
			keycodes.F11 = GLFW_KEY_F11;
			keycodes.F12 = GLFW_KEY_F12;
			keycodes.F13 = GLFW_KEY_F13;
			keycodes.F14 = GLFW_KEY_F14;
			keycodes.F15 = GLFW_KEY_F15;
			keycodes.F16 = GLFW_KEY_F16;
			keycodes.F17 = GLFW_KEY_F17;
			keycodes.F18 = GLFW_KEY_F18;
			keycodes.F19 = GLFW_KEY_F19;
			keycodes.F20 = GLFW_KEY_F20;
			keycodes.F21 = GLFW_KEY_F21;
			keycodes.F22 = GLFW_KEY_F22;
			keycodes.F23 = GLFW_KEY_F23;
			keycodes.F24 = GLFW_KEY_F24;
			keycodes.F25 = GLFW_KEY_F25;
			keycodes.KeyPad0 = GLFW_KEY_KP_0;
			keycodes.KeyPad1 = GLFW_KEY_KP_1;
			keycodes.KeyPad2 = GLFW_KEY_KP_2;
			keycodes.KeyPad3 = GLFW_KEY_KP_3;
			keycodes.KeyPad4 = GLFW_KEY_KP_4;
			keycodes.KeyPad5 = GLFW_KEY_KP_5;
			keycodes.KeyPad6 = GLFW_KEY_KP_6;
			keycodes.KeyPad7 = GLFW_KEY_KP_7;
			keycodes.KeyPad8 = GLFW_KEY_KP_8;
			keycodes.KeyPad9 = GLFW_KEY_KP_9;
			keycodes.KeyPad9 = GLFW_KEY_KP_DECIMAL;
			keycodes.KeyPadDivide = GLFW_KEY_KP_DIVIDE;
			keycodes.KeyPadMultiply = GLFW_KEY_KP_MULTIPLY;
			keycodes.KeyPadSubtract = GLFW_KEY_KP_SUBTRACT;
			keycodes.KeyPadAdd = GLFW_KEY_KP_ADD;
			keycodes.KeyPadEnter = GLFW_KEY_KP_ENTER;
			keycodes.KeyPadEqual = GLFW_KEY_KP_EQUAL;
			keycodes.LeftShift = GLFW_KEY_LEFT_SHIFT;
			keycodes.LeftControl = GLFW_KEY_LEFT_CONTROL;
			keycodes.LeftAlt = GLFW_KEY_LEFT_ALT;
			keycodes.LeftSuper = GLFW_KEY_LEFT_SUPER;
			keycodes.RightSifht = GLFW_KEY_RIGHT_SHIFT;
			keycodes.RightControl = GLFW_KEY_RIGHT_CONTROL;
			keycodes.RightAlt = GLFW_KEY_RIGHT_ALT;
			keycodes.RightSuper = GLFW_KEY_RIGHT_SUPER;
			keycodes.Menu = GLFW_KEY_MENU;

			keyModifs.Shift = GLFW_MOD_SHIFT;
			keyModifs.Control = GLFW_MOD_CONTROL;
			keyModifs.Alt = GLFW_MOD_ALT;
			keyModifs.Super = GLFW_MOD_SUPER;

			keyActions.Pressed = GLFW_PRESS;
			keyActions.Released = GLFW_RELEASE;
			keyActions.Pressing = GLFW_REPEAT;
		}
	}
}
