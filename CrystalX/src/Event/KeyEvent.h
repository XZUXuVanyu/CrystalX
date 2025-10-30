#pragma once
#include "Event/Event.h"

namespace CrystalX
{
    enum class KeyCode : uint16_t
    {
        Unknown = 0,

        D0 = '0', D1, D2, D3, D4, D5, D6, D7, D8, D9,
        A = 'A', B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10,
        F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,
        F21, F22, F23, F24,

        ArrowUp = 328,
        ArrowDown,
        ArrowLeft,
        ArrowRight,

        Home = 335,
        End,
        PageUp,
        PageDown,

        Insert = 342,
        Delete,
        Backspace = 348,
        Enter = 350,
        Tab,
        Space = ' ',

        LeftShift = 360,
        LeftControl,
        LeftAlt,
        //windows in windows or command in mac
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,

        CapsLock = 370,
        NumLock,
        ScrollLock,

        NumPad0 = 380, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
        NumPadDecimal,
        NumPadDivide,
        NumPadMultiply,
        NumPadSubtract,
        NumPadAdd,
        NumPadEnter,
        NumPadEqual,

        Apostrophe = '\'',
        Comma = ',',
        Minus = '-',
        Period = '.',
        Slash = '/',
        Semicolon = ';',
        Equal = '=',
        LeftBracket = '[',
        Backslash = '\\',
        RightBracket = ']',
        GraveAccent = '`',

        Escape = 256,
        PrintScreen = 365,
        Pause = 366
    };
    enum class KeyModifier : uint8_t
    {
        None = 0,
        Ctrl = BIT_MASK(1),
        Shift = BIT_MASK(2),
        Alt = BIT_MASK(3),
    };

    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(KeyCode keycode, KeyModifier keymodifier) {
            m_KeyCode = keycode;
            m_KeyModifier = keymodifier;
        };
        ~KeyPressEvent() {};
        KeyCode GetKeyCode() { return m_KeyCode; };
        KeyModifier GetKeyModifier() { return m_KeyModifier; };
        CRYSTALX_EVENT_REGISTER(KeyPressEvent);
    private:
        KeyCode m_KeyCode;
        KeyModifier m_KeyModifier;
    };
    class KeyReleaseEvent : public Event
    {
    public:
        KeyReleaseEvent(KeyCode keycode, KeyModifier keymodifier) {
            m_KeyCode = keycode;
            m_KeyModifier = keymodifier;
        };
        ~KeyReleaseEvent() {};
        KeyCode GetKeyCode() { return m_KeyCode; };
        KeyModifier GetKeyModifier() { return m_KeyModifier; };
        CRYSTALX_EVENT_REGISTER(KeyReleaseEvent);
    private:
        KeyCode m_KeyCode;
        KeyModifier m_KeyModifier;
    };
    class KeyRepeatEvent : public Event
    {
    public:
        KeyRepeatEvent(KeyCode keycode, KeyModifier keymodifier) {
            m_KeyCode = keycode;
            m_KeyModifier = keymodifier;
        };
        ~KeyRepeatEvent() {};
        KeyCode GetKeyCode() { return m_KeyCode; };
        KeyModifier GetKeyModifier() { return m_KeyModifier; };
        CRYSTALX_EVENT_REGISTER(KeyRepeatEvent);
    private:
        KeyCode m_KeyCode;
        KeyModifier m_KeyModifier;
    };
}