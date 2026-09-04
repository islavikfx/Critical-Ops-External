#include <GLES3/gl3.h>
#include "Menu.h"
#include "../Global.h"
#include "imgui.h"


namespace Menu {

    static bool g_init = false;
    static std::atomic<bool> g_esp{false};
    static std::atomic<bool> g_hitbox{false};
    static std::atomic<bool> g_wall{false};
    static std::atomic<bool> g_mini{false};
    static float g_lastX = -1, g_lastY = -1;

    void Init() {
        if (g_init) return;
        auto& s = ImGui::GetStyle();
        s.WindowRounding = 12.0f;
        s.WindowBorderSize = 2.5f;
        s.WindowPadding = ImVec2(22, 18);
        s.FramePadding = ImVec2(6, 5);
        s.ItemSpacing = ImVec2(0, 5);
        s.ItemInnerSpacing = ImVec2(5, 4);
        s.Alpha = 0.95f;
        s.FrameRounding = 8.0f;
        s.GrabRounding = 8.0f;
        auto& c = s.Colors;
        c[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.03f, 0.96f);
        c[ImGuiCol_Border] = ImVec4(0.85f, 0.12f, 0.12f, 1.0f);
        c[ImGuiCol_CheckMark] = ImVec4(0.95f, 0.28f, 0.55f, 1.0f);
        c[ImGuiCol_FrameBg] = ImVec4(0.07f, 0.07f, 0.07f, 0.85f);
        c[ImGuiCol_FrameBgHovered] = ImVec4(0.09f, 0.09f, 0.09f, 0.90f);
        c[ImGuiCol_FrameBgActive] = ImVec4(0.07f, 0.07f, 0.07f, 0.85f);
        c[ImGuiCol_Text] = ImVec4(0.88f, 0.88f, 0.88f, 1.0f);
        g_init = true;
    }


    void Render(int screenW, int screenH) {
        if (!g_init) return;
        float sw = (float)screenW, sh = (float)screenH;

        if (g_mini) {
            ImVec2 size(65, 65);
            float posX = (g_lastX > 0) ? g_lastX : sw/2.0f - size.x/2.0f;
            float posY = (g_lastY > 0) ? g_lastY : sh/2.0f - size.y/2.0f;
            ImGui::SetNextWindowSize(size, ImGuiCond_Once);
            ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_Once);
            ImGui::Begin("##mini", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
            ImDrawList* dl = ImGui::GetWindowDrawList();
            ImVec2 wp = ImGui::GetWindowPos();
            dl->AddRect(wp, ImVec2(wp.x + 65, wp.y + 65), IM_COL32(190, 35, 35, 255), 6.0f);
            dl->AddTriangleFilled(ImVec2(wp.x + 32, wp.y + 18), ImVec2(wp.x + 20, wp.y + 44), ImVec2(wp.x + 44, wp.y + 44), IM_COL32(255, 75, 145, 255));
            if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0)) g_mini = false;
            ImGui::End();
            return;
        }

        ImVec2 size(700, 400);
        ImGui::SetNextWindowSize(size, ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(sw/2.0f - size.x/2.0f, sh/3.0f - size.y/2.0f), ImGuiCond_Once);
        ImGui::Begin("##main", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImVec2 wp = ImGui::GetWindowPos();
        float ww = ImGui::GetWindowWidth();

        g_lastX = wp.x;
        g_lastY = wp.y;

        ImVec2 closeBtn(wp.x + ww - 46, wp.y + 10);
        bool closeH = ImGui::IsMouseHoveringRect(closeBtn, ImVec2(closeBtn.x + 24, closeBtn.y + 24));
        dl->AddRectFilled(closeBtn, ImVec2(closeBtn.x + 24, closeBtn.y + 24), closeH ? IM_COL32(190,35,75,255) : IM_COL32(35,6,12,255), 5.0f);
        dl->AddRect(closeBtn, ImVec2(closeBtn.x + 24, closeBtn.y + 24), IM_COL32(255,65,135,255), 5.0f);
        dl->AddLine(ImVec2(closeBtn.x+6, closeBtn.y+6), ImVec2(closeBtn.x+18, closeBtn.y+18), IM_COL32(255,65,135,255), 2.5f);
        dl->AddLine(ImVec2(closeBtn.x+18, closeBtn.y+6), ImVec2(closeBtn.x+6, closeBtn.y+18), IM_COL32(255,65,135,255), 2.5f);
        if (closeH && ImGui::IsMouseClicked(0)) { system("su -c 'killall ShiticalOps'"); exit(0); }

        ImVec2 minBtn(wp.x + ww - 78, wp.y + 10);
        bool minH = ImGui::IsMouseHoveringRect(minBtn, ImVec2(minBtn.x + 24, minBtn.y + 24));
        dl->AddRectFilled(minBtn, ImVec2(minBtn.x + 24, minBtn.y + 24), minH ? IM_COL32(190,35,75,255) : IM_COL32(35,6,12,255), 5.0f);
        dl->AddRect(minBtn, ImVec2(minBtn.x + 24, minBtn.y + 24), IM_COL32(255,65,135,255), 5.0f);
        dl->AddTriangleFilled(ImVec2(minBtn.x+12, minBtn.y+18), ImVec2(minBtn.x+5, minBtn.y+7), ImVec2(minBtn.x+19, minBtn.y+7), IM_COL32(255,65,135,255));
        if (minH && ImGui::IsMouseClicked(0)) g_mini = true;

        ImGui::SetCursorPos(ImVec2(18, 8));
        ImGui::Text("Shitical Ops");
        ImGui::SameLine(0, 6);
        ImGui::SetCursorPosY(10);
        ImGui::TextColored(ImVec4(0.40f, 0.40f, 0.40f, 0.60f), " (External)");
        ImGui::SetCursorPosY(44);
        dl->AddLine(ImVec2(wp.x + 18, wp.y + 48), ImVec2(wp.x + ww - 18, wp.y + 48), IM_COL32(190, 35, 35, 80), 2.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        float cx = 26.0f, cy = 64.0f, dy = 48.0f;

        ImGui::SetCursorPos(ImVec2(cx, cy));
        ImGui::BeginDisabled(true);
        bool ac = true;
        ImGui::Checkbox(" Anti-Cheat Bypass", &ac);
        ImGui::EndDisabled();

        ImGui::SetCursorPos(ImVec2(cx, cy + dy));
        bool esp = g_esp.load();
        if (ImGui::Checkbox(" Esp Radar", &esp)) g_esp = esp;
        ImGui::SetCursorPos(ImVec2(cx, cy + dy * 2));
        bool hit = g_hitbox.load();
        if (ImGui::Checkbox(" Hitboxes", &hit)) g_hitbox = hit;
        ImGui::SetCursorPos(ImVec2(cx, cy + dy * 3));
        bool wall = g_wall.load();
        if (ImGui::Checkbox(" Wallshot", &wall)) g_wall = wall;
        ImGui::PopStyleVar();
        ImGui::SetCursorPosY(278);
        dl->AddLine(ImVec2(wp.x + 18, wp.y + 286), ImVec2(wp.x + ww - 18, wp.y + 286), IM_COL32(55, 55, 55, 80), 1.5f);

        ImGui::SetCursorPosY(294);
        ImGui::SetCursorPosX(18);
        ImGui::TextColored(ImVec4(0.35f, 0.35f, 0.35f, 0.60f), "Made by iSlavik (@islavikfx)");
        ImGui::SetCursorPosY(320);
        ImGui::SetCursorPosX(18);
        ImGui::TextColored(ImVec4(0.2f, 0.85f, 0.2f, 0.65f), "github.com/islavikfx");
        ImGui::SetCursorPosY(346);
        ImGui::SetCursorPosX(18);
        ImGui::TextColored(ImVec4(0.35f, 0.35f, 0.35f, 0.60f), "1.70.1.f3300 (arm64)");

        ImGui::End();
    }

    void Shutdown() { g_init = false; }
    void SetEspRadar(bool on) { g_esp = on; }
    void SetHitboxes(bool on) { g_hitbox = on; }
    void SetWallshot(bool on) { g_wall = on; }
    bool IsEspRadarOn() { return g_esp; }
    bool IsHitboxesOn() { return g_hitbox; }
    bool IsWallshotOn() { return g_wall; }

}