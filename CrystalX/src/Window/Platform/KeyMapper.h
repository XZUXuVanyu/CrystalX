// Platform/KeyMapper.h
#pragma once
#include "Core.h"
#include "Event/KeyEvent.h"

namespace CrystalX
{
    class CRYSTALX_API KeyMapper
    {
    public:
        static void Initialize();
        static bool GetInitializeState();
        static void Disable();

        static KeyCode ToCrystalXKeyCode(int platformkeycode);
        static int ToPlatformKeyCode(KeyCode CrystalXkeycode);
        static KeyModifier ToCrystalXKeyModifier(int platformkeymodifier);
        static int ToPlatformKeyModifier(KeyModifier CrystalXkeymodifier);

    private:
        inline static std::atomic<bool> s_Initialized{ false };

        static std::unordered_map<int, KeyCode> s_PlatformToCrystalX;
        static std::unordered_map<KeyCode, int> s_CrystalXToPlatform;
        static std::unordered_map<int, KeyModifier> s_PlatformModifierToCrystalX;
        static std::unordered_map<KeyModifier, int> s_CrystalXModifierToPlatform;

        static void InitializeMappings();
    };
}
