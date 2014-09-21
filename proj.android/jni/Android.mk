LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Macaron

MCR_SRC := ../../src

LOCAL_SRC_FILES := \
	$(MCR_SRC)/MacaronPch.cpp \
	$(MCR_SRC)/LibCurl.cpp \
	$(MCR_SRC)/RapidJson.cpp \
	$(MCR_SRC)/TinyXml2.cpp
	

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../src \
	$(LOCAL_PATH)/../../include \
	$(GIT_ROOT)/Caramel/include \
	$(GIT_ROOT)/CandyJar/include


LOCAL_CFLAGS += \
	-D__STDINT_MACROS

	
include $(BUILD_STATIC_LIBRARY)
 
