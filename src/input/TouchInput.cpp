#include "TouchInput.h"
#include "../Global.h"
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <cstdio>


namespace Input {

    bool TouchInput::FindTouchDevice() {
        DIR* dir = opendir("/dev/input");
        if (!dir) return false;
        struct dirent* entry;
        while ((entry = readdir(dir))) {
            if (!strstr(entry->d_name, "event")) continue;
            char path[64];
            snprintf(path, sizeof(path), "/dev/input/%s", entry->d_name);
            int fd = open(path, O_RDONLY | O_SYNC | O_NONBLOCK);
            if (fd < 0) continue;
            unsigned long keyBits[12] = {0};
            ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keyBits)), keyBits);
            int bit = BTN_TOUCH;
            if (keyBits[bit / (int)(sizeof(long)*8)] & (1UL << (bit % (int)(sizeof(long)*8)))) {
                m_fd = fd;
                struct input_absinfo info;
                if (ioctl(m_fd, EVIOCGABS(ABS_MT_POSITION_X), &info) >= 0) m_maxX = info.maximum;
                if (ioctl(m_fd, EVIOCGABS(ABS_MT_POSITION_Y), &info) >= 0) m_maxY = info.maximum;
                closedir(dir);
                return true;
            }
            close(fd);
        }
        closedir(dir);
        return false;
    }

    TouchInput::TouchInput() { FindTouchDevice(); }
    TouchInput::~TouchInput() { if (m_fd >= 0) close(m_fd); }

    bool TouchInput::Poll(Event* out) {
        if (m_fd < 0) return false;
        static int lx = 0, ly = 0;
        while (true) {
            struct input_event ev;
            if (read(m_fd, &ev, sizeof(ev)) <= 0) return false;
            if (ev.type == EV_ABS && ev.code == ABS_MT_SLOT && ev.value != 0) { m_queueCount = 0; continue; }
            if (m_queueCount < 64) m_queue[m_queueCount++] = ev;
            if (ev.type == EV_SYN && ev.code == SYN_REPORT && ev.value == 0) {
                if (m_queueCount == 0) return false;
                out->action = Action::Move;
                out->x = lx; out->y = ly;
                for (int i = 0; i < m_queueCount; i++) {
                    struct input_event* e = &m_queue[i];
                    if (e->type == EV_ABS && e->code == ABS_MT_POSITION_X) { out->x = e->value; lx = e->value; }
                    if (e->type == EV_ABS && e->code == ABS_MT_POSITION_Y) { out->y = e->value; ly = e->value; }
                    if (e->type == EV_KEY && (e->code == BTN_TOUCH || e->code == BTN_TOOL_FINGER))
                        out->action = (e->value == 1) ? Action::TouchDown : Action::TouchUp;
                }
                m_queueCount = 0;
                return true;
            }
        }
    }

}