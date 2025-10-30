// Platform/KeyMapper.cpp
#include "KeyMapper.h"

namespace CrystalX
{
    std::unordered_map<int, KeyCode> KeyMapper::s_PlatformToCrystalX;
    std::unordered_map<KeyCode, int> KeyMapper::s_CrystalXToPlatform;
    std::unordered_map<int, KeyModifier> KeyMapper::s_PlatformModifierToCrystalX;
    std::unordered_map<KeyModifier, int> KeyMapper::s_CrystalXModifierToPlatform;
    bool KeyMapper::GetInitializeState()
    {
        return s_Initialized;
    }
    void KeyMapper::Initialize()
    {
        if (s_Initialized) {
            return;
        }
        InitializeMappings();
        s_Initialized = true;
        CRYSTALX_LOG_TRACE("KeyMapper initialized with {} key mappings",s_PlatformToCrystalX.size());
    }
    void KeyMapper::Disable()
    {
        if (s_Initialized) {
            s_PlatformToCrystalX.clear();
            s_CrystalXToPlatform.clear();
            s_PlatformModifierToCrystalX.clear();
            s_CrystalXModifierToPlatform.clear();

            s_Initialized = false;
            CRYSTALX_LOG_TRACE("KeyMapper disabled");
        }
    }
    void KeyMapper::InitializeMappings()
    {
        #ifdef CRYSTALX_WINDOWS
            s_PlatformToCrystalX = {
                {GLFW_KEY_A, KeyCode::A}, {GLFW_KEY_B, KeyCode::B},
                {GLFW_KEY_C, KeyCode::C}, {GLFW_KEY_D, KeyCode::D},
                {GLFW_KEY_E, KeyCode::E}, {GLFW_KEY_F, KeyCode::F},
                {GLFW_KEY_G, KeyCode::G}, {GLFW_KEY_H, KeyCode::H},
                {GLFW_KEY_I, KeyCode::I}, {GLFW_KEY_J, KeyCode::J},
                {GLFW_KEY_K, KeyCode::K}, {GLFW_KEY_L, KeyCode::L},
                {GLFW_KEY_M, KeyCode::M}, {GLFW_KEY_N, KeyCode::N},
                {GLFW_KEY_O, KeyCode::O}, {GLFW_KEY_P, KeyCode::P},
                {GLFW_KEY_Q, KeyCode::Q}, {GLFW_KEY_R, KeyCode::R},
                {GLFW_KEY_S, KeyCode::S}, {GLFW_KEY_T, KeyCode::T},
                {GLFW_KEY_U, KeyCode::U}, {GLFW_KEY_V, KeyCode::V},
                {GLFW_KEY_W, KeyCode::W}, {GLFW_KEY_X, KeyCode::X},
                {GLFW_KEY_Y, KeyCode::Y}, {GLFW_KEY_Z, KeyCode::Z},

                {GLFW_KEY_0, KeyCode::D0}, {GLFW_KEY_1, KeyCode::D1},
                {GLFW_KEY_2, KeyCode::D2}, {GLFW_KEY_3, KeyCode::D3},
                {GLFW_KEY_4, KeyCode::D4}, {GLFW_KEY_5, KeyCode::D5},
                {GLFW_KEY_6, KeyCode::D6}, {GLFW_KEY_7, KeyCode::D7},
                {GLFW_KEY_8, KeyCode::D8}, {GLFW_KEY_9, KeyCode::D9},

                {GLFW_KEY_F1, KeyCode::F1}, {GLFW_KEY_F2, KeyCode::F2},
                {GLFW_KEY_F3, KeyCode::F3}, {GLFW_KEY_F4, KeyCode::F4},
                {GLFW_KEY_F5, KeyCode::F5}, {GLFW_KEY_F6, KeyCode::F6},
                {GLFW_KEY_F7, KeyCode::F7}, {GLFW_KEY_F8, KeyCode::F8},
                {GLFW_KEY_F9, KeyCode::F9}, {GLFW_KEY_F10, KeyCode::F10},
                {GLFW_KEY_F11, KeyCode::F11}, {GLFW_KEY_F12, KeyCode::F12},

                {GLFW_KEY_UP, KeyCode::ArrowUp}, {GLFW_KEY_DOWN, KeyCode::ArrowDown},
                {GLFW_KEY_LEFT, KeyCode::ArrowLeft}, {GLFW_KEY_RIGHT, KeyCode::ArrowRight},

                {GLFW_KEY_LEFT_SHIFT, KeyCode::LeftShift}, {GLFW_KEY_RIGHT_SHIFT, KeyCode::RightShift},
                {GLFW_KEY_LEFT_CONTROL, KeyCode::LeftControl}, {GLFW_KEY_RIGHT_CONTROL, KeyCode::RightControl},
                {GLFW_KEY_LEFT_ALT, KeyCode::LeftAlt}, {GLFW_KEY_RIGHT_ALT, KeyCode::RightAlt},
                {GLFW_KEY_LEFT_SUPER, KeyCode::LeftSuper}, {GLFW_KEY_RIGHT_SUPER, KeyCode::RightSuper},

                {GLFW_KEY_SPACE, KeyCode::Space}, {GLFW_KEY_ENTER, KeyCode::Enter},
                {GLFW_KEY_TAB, KeyCode::Tab}, {GLFW_KEY_BACKSPACE, KeyCode::Backspace},
                {GLFW_KEY_ESCAPE, KeyCode::Escape}, {GLFW_KEY_INSERT, KeyCode::Insert},
                {GLFW_KEY_DELETE, KeyCode::Delete}, {GLFW_KEY_HOME, KeyCode::Home},
                {GLFW_KEY_END, KeyCode::End}, {GLFW_KEY_PAGE_UP, KeyCode::PageUp},
                {GLFW_KEY_PAGE_DOWN, KeyCode::PageDown}, {GLFW_KEY_CAPS_LOCK, KeyCode::CapsLock},
                {GLFW_KEY_NUM_LOCK, KeyCode::NumLock}, {GLFW_KEY_SCROLL_LOCK, KeyCode::ScrollLock},
                {GLFW_KEY_PRINT_SCREEN, KeyCode::PrintScreen}, {GLFW_KEY_PAUSE, KeyCode::Pause}
            };
            for (const auto& pair : s_PlatformToCrystalX) {
                s_CrystalXToPlatform[pair.second] = pair.first;
            }

            s_PlatformModifierToCrystalX = {
                {GLFW_MOD_SHIFT, KeyModifier::Shift},
                {GLFW_MOD_CONTROL, KeyModifier::Ctrl},
                {GLFW_MOD_ALT, KeyModifier::Alt}
            };
            for (const auto& pair : s_PlatformModifierToCrystalX) {
                s_CrystalXModifierToPlatform[pair.second] = pair.first;
            }
        #endif
    }
    KeyCode KeyMapper::ToCrystalXKeyCode(int platformkeycode)
    {
        if (!s_Initialized) {
            Initialize();
        }

        auto it = s_PlatformToCrystalX.find(platformkeycode);
        if (it != s_PlatformToCrystalX.end()) {
            return it->second;
        }
        CRYSTALX_LOG_WARN("Unknown platform keycode: {}, returning KeyCode::Unknown", platformkeycode);
        return KeyCode::Unknown;
    }
    int KeyMapper::ToPlatformKeyCode(KeyCode CrystalXkeycode)
    {
        if (!s_Initialized) {
            Initialize();
        }

        auto it = s_CrystalXToPlatform.find(CrystalXkeycode);
        if (it != s_CrystalXToPlatform.end()) {
            return it->second;
        }

        CRYSTALX_LOG_WARN("Unknown CrystalX KeyCode: {}, returning 0", static_cast<int>(CrystalXkeycode));
        return 0;
    }

    //todo: complete this two
    KeyModifier KeyMapper::ToCrystalXKeyModifier(int platformkeymodifier)
    {
        return KeyModifier::None;
    }
    int KeyMapper::ToPlatformKeyModifier(KeyModifier CrystalXkeymodifier)
    {
        return 0;
    }
}