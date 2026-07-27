#!/system/bin/sh
#!github.com/islavikfx

if [ "$(id -u)" -ne 0 ]; then
    echo "Root not found. Execute script with root privileges."
    exit 1
fi

clear
cd /data/local/tmp/Critical-Ops-External
echo "Be sure your running version «1.70.1.f3300», otherwise offsets may not match and you can get permanently banned.\n"
sleep 3


arm=$(getprop ro.product.cpu.abi)
if [ "$arm" != "arm64-v8a" ]; then
    echo "Menu support only arm64-v8a (x64)."
    exit 1
fi

a=$(getprop ro.build.version.sdk)
if [ "$a" -lt 28 ]; then
    echo "Menu supports only Android 9+."
    exit 1
fi

pkg="com.criticalforceentertainment.criticalops"
if ! pm list packages | grep -q "$pkg"; then
    echo "Install Shitical Ops at first."
    exit 1
fi

pid=$(pidof "$pkg" 2>/dev/null)
if [ -n "$pid" ]; then
    kill -9 $pid
    sleep 2
fi

if [ -z "$(ls -A /dev/input/ 2>/dev/null)" ]; then
    echo "Directory /dev/input/* is empty. Your device is using custom touch system."
    exit 1
fi


su -c "killall ShiticalOps" 2>/dev/null
chmod a+rwx /dev/input/*
chown root:root /dev/input/*
chmod +x ShiticalOps
magisk --denylist enable
magisk --denylist add $pkg

rm -vf /data/data/com.google.android.gms/shared_prefs/adid_settings.xml
am start -n $pkg/com.google.firebase.MessagingUnityPlayerActivity

sleep 8
./ShiticalOps
echo "Enjoy ;)"
