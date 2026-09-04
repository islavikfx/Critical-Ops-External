#pragma once
#include <cstdint>


// # github.com/islavikfx
// # 1.70.1.f3300 (arm64-v8a)
namespace Offsets {

    constexpr uintptr_t LibSplit = 0x13a400;

    // # internal class O8F11B77EF
    // # Anti-Cheat Bypass offsets removed by request.
    // # ** Executable file ShiticalOps apply Bypass automatically for this version.

    // # public System.Void OFF2F5C089(O1D5DCF3C9.OFA0D360B5<System.Int32>& O35ED70003) { }
    constexpr uintptr_t Espradar = 0x1b1897c + 0xac;
    // # cmn w8, #1
    constexpr uint8_t EspOFF[4] = {0x1f, 0x05, 0x00, 0x31};
    // # mov w8, #1
    constexpr uint8_t EspON[4] = {0x28, 0x00, 0x80, 0x52};
    
    // # public System.Boolean O1B15C5CF6(UnityEngine.Ray OE4DE99116, UnityEngine.Vector3& OB368683FF, System.Single& OD16375153) { }
    constexpr uintptr_t Hitboxes = 0x1b9b7fc + 0x190;
    // # ldr s7, [x22, #0x2c]
    constexpr uint8_t HitboxOFF[4] = {0xc7, 0x2e, 0x40, 0xbd};
    // # fmov s7, #21.0
    constexpr uint8_t HitboxON[4] = {0x07, 0xb0, 0x26, 0x1e};

    // # private System.Void O7CC5CCB4C(UnityEngine.RaycastHit O9F54E6474, OCE149BFBC.OB5F73252A O4D909A660, System.Int32& OC06639DC6, OA7DE12614.O65B09C86D& O7605DD63C) { }
    constexpr uintptr_t Wallshot = 0x1a93b30 + 0x190;
    // # tbz w0, #0x0, #0x50
    constexpr uint8_t WallOFF[4] = {0x80, 0x02, 0x00, 0x36};
    // # b.al #0x50
    constexpr uint8_t WallON[4] = {0x8e, 0x02, 0x00, 0x54};

}
