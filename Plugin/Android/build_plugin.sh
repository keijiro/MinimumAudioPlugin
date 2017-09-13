#!/bin/sh
echo ""
echo "Compiling NativeCode.c..."
$ANDROID_NDK_ROOT/ndk-build NDK_PROJECT_PATH=. NDK_APPLICATION_MK=Application.mk $*
mv libs/armeabi/libnative.so ..

echo ""
echo "Cleaning up / removing build folders..."  #optional..
rm -rf libs
rm -rf obj

echo ""
echo "Done!"
