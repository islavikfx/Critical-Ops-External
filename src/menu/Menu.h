#pragma once
#include <atomic>


namespace Menu {

    void Init();
    void Render(int screenW, int screenH);
    void Shutdown();
    void SetEspRadar(bool on);
    void SetHitboxes(bool on);
    void SetWallshot(bool on);
    bool IsEspRadarOn();
    bool IsHitboxesOn();
    bool IsWallshotOn();

}