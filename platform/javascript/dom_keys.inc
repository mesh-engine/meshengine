/*************************************************************************/
/*  dom_keys.inc                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           MESH ENGINE                                */
/*                      https://mesh-engine.com                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "core/os/keyboard.h"

// See https://w3c.github.io/uievents-code/#code-value-tables
Key dom_code2mesh_scancode(EM_UTF8 const p_code[32], EM_UTF8 const p_key[32], bool p_physical) {
#define DOM2MESH(p_str, p_mesh_code)                                         \
	if (memcmp((const void *)p_str, (void *)p_code, strlen(p_str) + 1) == 0) { \
		return Key::p_mesh_code;                                              \
	}

	// Numpad section.
	DOM2MESH("NumLock", NUMLOCK);
	DOM2MESH("Numpad0", KP_0);
	DOM2MESH("Numpad1", KP_1);
	DOM2MESH("Numpad2", KP_2);
	DOM2MESH("Numpad3", KP_3);
	DOM2MESH("Numpad4", KP_4);
	DOM2MESH("Numpad5", KP_5);
	DOM2MESH("Numpad6", KP_6);
	DOM2MESH("Numpad7", KP_7);
	DOM2MESH("Numpad8", KP_8);
	DOM2MESH("Numpad9", KP_9);
	DOM2MESH("NumpadAdd", KP_ADD);
	DOM2MESH("NumpadBackspace", BACKSPACE);
	DOM2MESH("NumpadClear", CLEAR);
	DOM2MESH("NumpadClearEntry", CLEAR);
	//DOM2MESH("NumpadComma", UNKNOWN);
	DOM2MESH("NumpadDecimal", KP_PERIOD);
	DOM2MESH("NumpadDivide", KP_DIVIDE);
	DOM2MESH("NumpadEnter", KP_ENTER);
	DOM2MESH("NumpadEqual", EQUAL);
	//DOM2MESH("NumpadHash", UNKNOWN);
	//DOM2MESH("NumpadMemoryAdd", UNKNOWN);
	//DOM2MESH("NumpadMemoryClear", UNKNOWN);
	//DOM2MESH("NumpadMemoryRecall", UNKNOWN);
	//DOM2MESH("NumpadMemoryStore", UNKNOWN);
	//DOM2MESH("NumpadMemorySubtract", UNKNOWN);
	DOM2MESH("NumpadMultiply", KP_MULTIPLY);
	DOM2MESH("NumpadParenLeft", PARENLEFT);
	DOM2MESH("NumpadParenRight", PARENRIGHT);
	DOM2MESH("NumpadStar", KP_MULTIPLY); // or ASTERISK ?
	DOM2MESH("NumpadSubtract", KP_SUBTRACT);

	// Printable ASCII.
	if (!p_physical) {
		uint8_t b0 = (uint8_t)p_key[0];
		uint8_t b1 = (uint8_t)p_key[1];
		uint8_t b2 = (uint8_t)p_key[2];
		if (b1 == 0 && b0 > 0x1F && b0 < 0x7F) { // ASCII.
			if (b0 > 0x60 && b0 < 0x7B) { // Lowercase ASCII.
				b0 -= 32;
			}
			return (Key)b0;
		}

#define _U_2BYTES_MASK 0xE0
#define _U_2BYTES 0xC0
		// Latin-1 codes.
		if (b2 == 0 && (b0 & _U_2BYTES_MASK) == _U_2BYTES) { // 2-bytes utf8, only known latin.
			uint32_t key = ((b0 & ~_U_2BYTES_MASK) << 6) | (b1 & 0x3F);
			if (key >= 0xA0 && key <= 0xDF) {
				return (Key)key;
			}
			if (key >= 0xE0 && key <= 0xFF) { // Lowercase known latin.
				key -= 0x20;
				return (Key)key;
			}
		}
#undef _U_2BYTES_MASK
#undef _U_2BYTES
	}

	// Alphanumeric section.
	DOM2MESH("Backquote", QUOTELEFT);
	DOM2MESH("Backslash", BACKSLASH);
	DOM2MESH("BracketLeft", BRACKETLEFT);
	DOM2MESH("BracketRight", BRACKETRIGHT);
	DOM2MESH("Comma", COMMA);
	DOM2MESH("Digit0", KEY_0);
	DOM2MESH("Digit1", KEY_1);
	DOM2MESH("Digit2", KEY_2);
	DOM2MESH("Digit3", KEY_3);
	DOM2MESH("Digit4", KEY_4);
	DOM2MESH("Digit5", KEY_5);
	DOM2MESH("Digit6", KEY_6);
	DOM2MESH("Digit7", KEY_7);
	DOM2MESH("Digit8", KEY_8);
	DOM2MESH("Digit9", KEY_9);
	DOM2MESH("Equal", EQUAL);
	DOM2MESH("IntlBackslash", BACKSLASH);
	//DOM2MESH("IntlRo", UNKNOWN);
	DOM2MESH("IntlYen", YEN);

	DOM2MESH("KeyA", A);
	DOM2MESH("KeyB", B);
	DOM2MESH("KeyC", C);
	DOM2MESH("KeyD", D);
	DOM2MESH("KeyE", E);
	DOM2MESH("KeyF", F);
	DOM2MESH("KeyG", G);
	DOM2MESH("KeyH", H);
	DOM2MESH("KeyI", I);
	DOM2MESH("KeyJ", J);
	DOM2MESH("KeyK", K);
	DOM2MESH("KeyL", L);
	DOM2MESH("KeyM", M);
	DOM2MESH("KeyN", N);
	DOM2MESH("KeyO", O);
	DOM2MESH("KeyP", P);
	DOM2MESH("KeyQ", Q);
	DOM2MESH("KeyR", R);
	DOM2MESH("KeyS", S);
	DOM2MESH("KeyT", T);
	DOM2MESH("KeyU", U);
	DOM2MESH("KeyV", V);
	DOM2MESH("KeyW", W);
	DOM2MESH("KeyX", X);
	DOM2MESH("KeyY", Y);
	DOM2MESH("KeyZ", Z);

	DOM2MESH("Minus", MINUS);
	DOM2MESH("Period", PERIOD);
	DOM2MESH("Quote", APOSTROPHE);
	DOM2MESH("Semicolon", SEMICOLON);
	DOM2MESH("Slash", SLASH);

	// Functional keys in the Alphanumeric section.
	DOM2MESH("AltLeft", ALT);
	DOM2MESH("AltRight", ALT);
	DOM2MESH("Backspace", BACKSPACE);
	DOM2MESH("CapsLock", CAPSLOCK);
	DOM2MESH("ContextMenu", MENU);
	DOM2MESH("ControlLeft", CTRL);
	DOM2MESH("ControlRight", CTRL);
	DOM2MESH("Enter", ENTER);
	DOM2MESH("MetaLeft", SUPER_L);
	DOM2MESH("MetaRight", SUPER_R);
	DOM2MESH("ShiftLeft", SHIFT);
	DOM2MESH("ShiftRight", SHIFT);
	DOM2MESH("Space", SPACE);
	DOM2MESH("Tab", TAB);

	// ControlPad section.
	DOM2MESH("Delete", KEY_DELETE);
	DOM2MESH("End", END);
	DOM2MESH("Help", HELP);
	DOM2MESH("Home", HOME);
	DOM2MESH("Insert", INSERT);
	DOM2MESH("PageDown", PAGEDOWN);
	DOM2MESH("PageUp", PAGEUP);

	// ArrowPad section.
	DOM2MESH("ArrowDown", DOWN);
	DOM2MESH("ArrowLeft", LEFT);
	DOM2MESH("ArrowRight", RIGHT);
	DOM2MESH("ArrowUp", UP);

	// Function section.
	DOM2MESH("Escape", ESCAPE);
	DOM2MESH("F1", F1);
	DOM2MESH("F2", F2);
	DOM2MESH("F3", F3);
	DOM2MESH("F4", F4);
	DOM2MESH("F5", F5);
	DOM2MESH("F6", F6);
	DOM2MESH("F7", F7);
	DOM2MESH("F8", F8);
	DOM2MESH("F9", F9);
	DOM2MESH("F10", F10);
	DOM2MESH("F11", F11);
	DOM2MESH("F12", F12);
	//DOM2MESH("Fn", UNKNOWN); // never actually fired, but included in the standard draft.
	//DOM2MESH("FnLock", UNKNOWN);
	DOM2MESH("PrintScreen", PRINT);
	DOM2MESH("ScrollLock", SCROLLLOCK);
	DOM2MESH("Pause", PAUSE);

	// Media keys section.
	DOM2MESH("BrowserBack", BACK);
	DOM2MESH("BrowserFavorites", FAVORITES);
	DOM2MESH("BrowserForward", FORWARD);
	DOM2MESH("BrowserHome", OPENURL);
	DOM2MESH("BrowserRefresh", REFRESH);
	DOM2MESH("BrowserSearch", SEARCH);
	DOM2MESH("BrowserStop", STOP);
	//DOM2MESH("Eject", UNKNOWN);
	DOM2MESH("LaunchApp1", LAUNCH0);
	DOM2MESH("LaunchApp2", LAUNCH1);
	DOM2MESH("LaunchMail", LAUNCHMAIL);
	DOM2MESH("MediaPlayPause", MEDIAPLAY);
	DOM2MESH("MediaSelect", LAUNCHMEDIA);
	DOM2MESH("MediaStop", MEDIASTOP);
	DOM2MESH("MediaTrackNext", MEDIANEXT);
	DOM2MESH("MediaTrackPrevious", MEDIAPREVIOUS);
	//DOM2MESH("Power", UNKNOWN);
	//DOM2MESH("Sleep", UNKNOWN);
	DOM2MESH("AudioVolumeDown", VOLUMEDOWN);
	DOM2MESH("AudioVolumeMute", VOLUMEMUTE);
	DOM2MESH("AudioVolumeUp", VOLUMEUP);
	//DOM2MESH("WakeUp", UNKNOWN);
	return Key::UNKNOWN;
#undef DOM2MESH
}
