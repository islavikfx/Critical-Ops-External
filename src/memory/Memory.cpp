#include "Memory.h"
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <cstring>
#include <string>


namespace Memory {

    pid_t FindProcess(const char* name) {
        DIR* dir = opendir("/proc");
        if (!dir) return 0;
        struct dirent* e;
        while ((e = readdir(dir))) {
            if (e->d_name[0] < '0' || e->d_name[0] > '9') continue;
            std::string path = "/proc/" + std::string(e->d_name) + "/cmdline";
            int fd = open(path.c_str(), O_RDONLY);
            if (fd < 0) continue;
            char buf[256] = {0};
            read(fd, buf, sizeof(buf) - 1);
            close(fd);
            if (strstr(buf, name)) {
                pid_t pid = atoi(e->d_name);
                closedir(dir);
                return pid;
            }
        }
        closedir(dir);
        return 0;
    }


    uintptr_t GetModuleBase(pid_t pid, const char* module) {
        std::string path = "/proc/" + std::to_string(pid) + "/maps";
        FILE* f = fopen(path.c_str(), "r");
        if (!f) return 0;
        char line[512];
        while (fgets(line, sizeof(line), f)) {
            if (strstr(line, module) && strstr(line, "r-xp")) {
                uintptr_t base;
                sscanf(line, "%lx-", &base);
                fclose(f);
                return base;
            }
        }
        fclose(f);
        return 0;
    }


    bool Read(pid_t pid, uintptr_t addr, void* buf, size_t size) {
        std::string path = "/proc/" + std::to_string(pid) + "/mem";
        int fd = open(path.c_str(), O_RDONLY);
        if (fd < 0) return false;
        lseek64(fd, addr, SEEK_SET);
        bool ok = (read(fd, buf, size) == (ssize_t)size);
        close(fd);
        return ok;
    }


    bool Write(pid_t pid, uintptr_t addr, const void* buf, size_t size) {
        std::string path = "/proc/" + std::to_string(pid) + "/mem";
        int fd = open(path.c_str(), O_RDWR);
        if (fd < 0) return false;
        lseek64(fd, addr, SEEK_SET);
        bool ok = (write(fd, buf, size) == (ssize_t)size);
        close(fd);
        return ok;
    }

    
    bool IsAlive(pid_t pid) {
        return access(("/proc/" + std::to_string(pid)).c_str(), F_OK) == 0;
    }

}