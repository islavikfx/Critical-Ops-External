#include "Global.h"
#include "menu/Menu.h"
#include "memory/Memory.h"
#include "overlay/SurfaceWindow.h"
#include "input/TouchInput.h"
#include "sdk/Offsets.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_android.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <ctime>
#include <cstdlib>


size_t android::anative_window_creator::detail::compat::SystemVersion = 0;
static std::atomic<bool> g_running{true};
static pid_t g_pid = 0;
static uintptr_t g_base = 0;
static int g_screenW = 1600, g_screenH = 720;


bool Init() {
    g_pid = Memory::FindProcess("com.criticalforceentertainment.criticalops");
    if (!g_pid) return false;
    g_base = Memory::GetModuleBase(g_pid, "libil2cpp.so");
    if (!g_base) return false;
    return true;
}


void ApplyAC() {
    if (!g_pid || !g_base) return;
    
    struct ACPatch {
        uintptr_t offset;
        const uint8_t* patch;
    };
    
    const ACPatch patches[] = {
        {Offsets::ACBypass1, Offsets::ACPatch1},
        {Offsets::ACBypass2, Offsets::ACPatch2},
        {Offsets::ACBypass3, Offsets::ACPatch3},
        {Offsets::ACBypass4, Offsets::ACPatch4},
        {Offsets::ACBypass5, Offsets::ACPatch5},
        {Offsets::ACBypass6, Offsets::ACPatch6},
        {Offsets::ACBypass7, Offsets::ACPatch7},
        {Offsets::ACBypass8, Offsets::ACPatch8},
        {Offsets::ACBypass9, Offsets::ACPatch9},
        {Offsets::ACBypass10, Offsets::ACPatch10},
        {Offsets::ACBypass11, Offsets::ACPatch11},
        {Offsets::ACBypass12, Offsets::ACPatch12},
        {Offsets::ACBypass13, Offsets::ACPatch13},
        {Offsets::ACBypass14, Offsets::ACPatch14},
        {Offsets::ACBypass15, Offsets::ACPatch15},
        {Offsets::ACBypass16, Offsets::ACPatch16},
        {Offsets::ACBypass17, Offsets::ACPatch17},
        {Offsets::ACBypass18, Offsets::ACPatch18},
        {Offsets::ACBypass19, Offsets::ACPatch19},
        {Offsets::ACBypass20, Offsets::ACPatch20},
        {Offsets::ACBypass21, Offsets::ACPatch21},
        {Offsets::ACBypass22, Offsets::ACPatch22},
        {Offsets::ACBypass23, Offsets::ACPatch23},
        {Offsets::ACBypass24, Offsets::ACPatch24},
        {Offsets::ACBypass25, Offsets::ACPatch25}
    };
    
    constexpr int patchCount = sizeof(patches) / sizeof(patches[0]);
    for (int i = 0; i < patchCount; i++) {
        uintptr_t addr = g_base + patches[i].offset - Offsets::LibSplit;
        if (!Memory::Write(g_pid, addr, patches[i].patch, 4)) {
            continue;
        }
    }
}


void Monitor() {
    while (g_running) {
        if (g_pid && !Memory::IsAlive(g_pid)) {
            Menu::SetEspRadar(false);
            Menu::SetHitboxes(false);
            Menu::SetWallshot(false);
            g_pid = 0;
            g_base = 0;
        }

        if (!g_pid && Init()) ApplyAC();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}


void Patcher() {
    static bool lastEsp = false, lastHit = false, lastWall = false;
    while (g_running) {
        if (!g_base) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        bool esp = Menu::IsEspRadarOn();
        bool hit = Menu::IsHitboxesOn();
        bool wall = Menu::IsWallshotOn();

        if (esp != lastEsp) {
            uintptr_t addr = g_base + Offsets::Espradar - Offsets::LibSplit;
            Memory::Write(g_pid, addr, esp ? Offsets::EspON : Offsets::EspOFF, 4);
            lastEsp = esp;
        }
        if (hit != lastHit) {
            uintptr_t addr = g_base + Offsets::Hitboxes - Offsets::LibSplit;
            Memory::Write(g_pid, addr, hit ? Offsets::HitboxON : Offsets::HitboxOFF, 4);
            lastHit = hit;
        }
        if (wall != lastWall) {
            uintptr_t addr = g_base + Offsets::Wallshot - Offsets::LibSplit;
            Memory::Write(g_pid, addr, wall ? Offsets::WallON : Offsets::WallOFF, 4);
            lastWall = wall;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


int main() {
    while (!Init()) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    ApplyAC();
    Input::TouchInput touch;
    if (!touch.IsValid()) return 1;

    int rawMaxX = touch.MaxX();
    int rawMaxY = touch.MaxY();
    g_screenW = rawMaxY + 1;
    g_screenH = rawMaxX + 1;

    android::ANativeWindowCreator::CreateOptions opts;
    opts.name = "ShiticalOps";
    opts.width = g_screenW;
    opts.height = g_screenH;
    opts.skipScreenshot = false;
    auto* w = android::ANativeWindowCreator::Create(opts);
    if (!w) return 1;

    auto dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(dpy, nullptr, nullptr);
    EGLint a[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_NONE};
    EGLConfig c;
    EGLint n;

    eglChooseConfig(dpy, a, &c, 1, &n);
    EGLint f;
    eglGetConfigAttrib(dpy, c, EGL_NATIVE_VISUAL_ID, &f);
    ANativeWindow_setBuffersGeometry(w, 0, 0, f);
    auto s = eglCreateWindowSurface(dpy, c, w, nullptr);
    EGLint ca[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    auto ctx = eglCreateContext(dpy, c, EGL_NO_CONTEXT, ca);
    eglMakeCurrent(dpy, s, s, ctx);
    glViewport(0, 0, g_screenW, g_screenH);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    auto& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(g_screenW, g_screenH);
    io.IniFilename = nullptr;
    io.FontGlobalScale = 2.2f;
    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;

    ImGui_ImplAndroid_Init(w);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    Menu::Init();
    std::thread(Monitor).detach();
    std::thread(Patcher).detach();

    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    double lt = ts.tv_sec + ts.tv_nsec / 1e9;

    while (g_running) {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        double now = ts.tv_sec + ts.tv_nsec / 1e9;
        io.DeltaTime = (float)(now - lt);
        if (io.DeltaTime <= 0) io.DeltaTime = 1.0f / 60.0f;
        lt = now;

        if (touch.IsValid()) {
            Input::Event ev;
            while (touch.Poll(&ev)) {
                float mx = (float)ev.y / (float)rawMaxY * (float)g_screenW;
                float my = (float)g_screenH - ((float)ev.x / (float)rawMaxX * (float)g_screenH);
                io.AddMousePosEvent(mx, my);
                if (ev.action == Input::Action::TouchDown)
                    io.AddMouseButtonEvent(0, true);
                else if (ev.action == Input::Action::TouchUp)
                    io.AddMouseButtonEvent(0, false);
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame();
        ImGui::NewFrame();
        Menu::Render(g_screenW, g_screenH);
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        eglSwapBuffers(dpy, s);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    Menu::Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    return 0;

}