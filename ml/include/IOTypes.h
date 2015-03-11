#ifndef __IOTYPES_H__
#define __IOTYPES_H__

#include "types.h"
#include <array>

namespace ml
{

	// Mouse input
	typedef u16 MouseRange;
	typedef s32 MouseButtonState;
	typedef Vector2d<MouseRange> MousePosition;
	typedef enum MouseButtonId
	{
		LeftButton = 0,
		RightButton = 1,
		CenterButton = 2,
		NumButtons = 3
	};

	struct MouseButtons
	{
		std::array<MouseButtonState, MouseButtonId::NumButtons> pressed;
	};

	struct MouseState
	{
		MousePosition position;
		MouseButtons buttons;
	};

	// Keyboard input
	typedef s16 KeyCodeType;
	typedef s16 KeyActionType;
	typedef struct
	{
		KeyActionType Pressed;
		KeyActionType Pressing;
		KeyActionType Released;
	} KeyAction;

	typedef struct
	{
		KeyCodeType Shift;
		KeyCodeType Control;
		KeyCodeType Alt;
		KeyCodeType Super;
	} KeyModifs;

	typedef struct
	{
		KeyCodeType Unknown;

		KeyCodeType Space;
		KeyCodeType Apostrphe;
		KeyCodeType Comma;
		KeyCodeType Minus;
		KeyCodeType Perios;
		KeyCodeType Slash;
		KeyCodeType Number0;
		KeyCodeType Number1;
		KeyCodeType Number2;
		KeyCodeType Number3;
		KeyCodeType Number4;
		KeyCodeType Number5;
		KeyCodeType Number6;
		KeyCodeType Number7;
		KeyCodeType Number8;
		KeyCodeType Number9;
		KeyCodeType Semicolon;
		KeyCodeType Equal;
		KeyCodeType KeyA;
		KeyCodeType KeyB;
		KeyCodeType KeyC;
		KeyCodeType KeyD;
		KeyCodeType KeyE;
		KeyCodeType KeyF;
		KeyCodeType KeyG;
		KeyCodeType KeyH;
		KeyCodeType KeyI;
		KeyCodeType KeyJ;
		KeyCodeType KeyK;
		KeyCodeType KeyL;
		KeyCodeType KeyM;
		KeyCodeType KeyN;
		KeyCodeType KeyO;
		KeyCodeType KeyP;
		KeyCodeType KeyQ;
		KeyCodeType KeyR;
		KeyCodeType KeyS;
		KeyCodeType KeyT;
		KeyCodeType KeyU;
		KeyCodeType KeyV;
		KeyCodeType KeyW;
		KeyCodeType KeyX;
		KeyCodeType KeyY;
		KeyCodeType KeyZ;
		KeyCodeType LeftBracket;
		KeyCodeType BackSlash;
		KeyCodeType RightBracket;
		KeyCodeType GraveAccent;
		KeyCodeType Unknown1;
		KeyCodeType Unknown2;
		KeyCodeType Escape;
		KeyCodeType Enter;
		KeyCodeType Tab;
		KeyCodeType Backspace;
		KeyCodeType Insert;
		KeyCodeType Delete;
		KeyCodeType Right;
		KeyCodeType Left;
		KeyCodeType Down;
		KeyCodeType Up;
		KeyCodeType Home;
		KeyCodeType End;
		KeyCodeType PageUp;
		KeyCodeType PageDown;
		KeyCodeType CapsLock;
		KeyCodeType ScrollLock;
		KeyCodeType NumLock;
		KeyCodeType PrintScreen;
		KeyCodeType Pause;
		KeyCodeType F1;
		KeyCodeType F2;
		KeyCodeType F3;
		KeyCodeType F4;
		KeyCodeType F5;
		KeyCodeType F6;
		KeyCodeType F7;
		KeyCodeType F8;
		KeyCodeType F9;
		KeyCodeType F10;
		KeyCodeType F11;
		KeyCodeType F12;
		KeyCodeType F13;
		KeyCodeType F14;
		KeyCodeType F15;
		KeyCodeType F16;
		KeyCodeType F17;
		KeyCodeType F18;
		KeyCodeType F19;
		KeyCodeType F20;
		KeyCodeType F21;
		KeyCodeType F22;
		KeyCodeType F23;
		KeyCodeType F24;
		KeyCodeType F25;
		KeyCodeType KeyPad0;
		KeyCodeType KeyPad1;
		KeyCodeType KeyPad2;
		KeyCodeType KeyPad3;
		KeyCodeType KeyPad4;
		KeyCodeType KeyPad5;
		KeyCodeType KeyPad6;
		KeyCodeType KeyPad7;
		KeyCodeType KeyPad8;
		KeyCodeType KeyPad9;
		KeyCodeType KeyPadDecimal;
		KeyCodeType KeyPadDivide;
		KeyCodeType KeyPadMultiply;
		KeyCodeType KeyPadSubtract;
		KeyCodeType KeyPadAdd;
		KeyCodeType KeyPadEnter;
		KeyCodeType KeyPadEqual;
		KeyCodeType LeftShift;
		KeyCodeType LeftControl;
		KeyCodeType LeftAlt;
		KeyCodeType LeftSuper;
		KeyCodeType RightSifht;
		KeyCodeType RightControl;
		KeyCodeType RightAlt;
		KeyCodeType RightSuper;
		KeyCodeType Menu;
	} KeyCode;
}

#endif
