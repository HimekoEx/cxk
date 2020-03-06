(D:/Android/android-ndk-r13b/ndk-build.cmd)^
&& (adb push "../libs/armeabi-v7a/libCyBL.so" "/sdcard/libCyBL.so")^
&& (adb shell "su root -c rm /data/data/dkplugin.mihoyo.hk3.gf/lib/libCyBL.so")^
&& (adb shell "su root -c mv /sdcard/libCyBL.so /data/data/dkplugin.mihoyo.hk3.gf/lib/libCyBL.so")^
&& (adb shell "su root -c chmod 777 /data/data/dkplugin.mihoyo.hk3.gf/lib/libCyBL.so")