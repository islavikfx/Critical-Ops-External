#!/bin/bash
cd "$(dirname "$0")"
NDK="$HOME/android-ndk-r27d"

rm -rf build
mkdir -p build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE="$NDK/build/cmake/android.toolchain.cmake" \
-DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-27 \
-DANDROID_STL=c++_shared -DCMAKE_BUILD_TYPE=Release

cmake --build . -j$(nproc)
echo " "