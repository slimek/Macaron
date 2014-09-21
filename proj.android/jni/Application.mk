APP_PLATFORM := android-15
APP_ABI := x86
APP_STL := gnustl_static

APP_CFLAGS := -fexceptions
APP_CPPFLAGS := -std=c++11 -frtti

ifeq ($(NDEBUG),1)

# Release
APP_OPTIM := release
MACARON_CONFIG := Release

else

# Debug
APP_OPTIM := debug
APP_CFLAGS += -g
MACARON_CONFIG := Debug

endif

NDK_APP_OUT := obj/$(MACARON_CONFIG)
NDK_TOOLCHAIN_VERSION := 4.8
