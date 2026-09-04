#pragma once
#include <cstdint>
#include <sys/types.h>
#include <cstddef>


namespace Memory {

    pid_t FindProcess(const char* name);
    uintptr_t GetModuleBase(pid_t pid, const char* module);
    bool Read(pid_t pid, uintptr_t addr, void* buf, size_t size);
    bool Write(pid_t pid, uintptr_t addr, const void* buf, size_t size);
    bool IsAlive(pid_t pid);
 
}