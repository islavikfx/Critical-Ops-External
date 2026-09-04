## Critical Ops External

Imgui menu for Shitical Ops with some features for 1.70.1.f3300.

![Menu](https://github.com/islavikfx/Critical-Ops-External/blob/main/photo/input.png?raw=true)

Run it on Termux or manually in /data/local/tmp by executing ./ShiticalOps.

### Instruction for Termux:
```bash
termux-setup-storage
pkg install git
cd /sdcard/
git clone https://github.com/islavikfx/Critical-Ops-External.git
su
mv /sdcard/Critical-Ops-External /data/local/tmp
cd /data/local/tmp/Critical-Ops-External
su -c "sh 1.70.1.f3300x64.sh"
```

Custom android overlay, no Ptrace, working with /dev/input/, Android Surface, patching /proc/X/mem.

Menu may not support on most devices because its working with custom logic. Try set phone screen resolution to 1600x720 - it can help you.

If you will improve menu - it is better to do it by scaling the interface itself not through the global ImGui settings, use /src/overlay/SurfaceWindow.h to adapt it.

Telegram & Discord: @jeddy01759
