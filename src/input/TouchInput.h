#pragma once
#include <cstdint>
#include <linux/input.h>


namespace Input {
    
    enum class Action : uint32_t { Move, TouchDown, TouchUp };
    struct Event { Action action = Action::Move; int x = 0, y = 0; };

    class TouchInput {
    public:
        TouchInput();
        ~TouchInput();
        bool Poll(Event* out);
        bool IsValid() const { return m_fd >= 0; }
        int MaxX() const { return m_maxX; }
        int MaxY() const { return m_maxY; }

    private:
        int m_fd = -1;
        int m_maxX = 1080, m_maxY = 2400;
        struct input_event m_queue[64];
        int m_queueCount = 0;
        bool FindTouchDevice();
    };

}