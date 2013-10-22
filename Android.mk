LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := configumerator
LOCAL_SRC_FILES := configumerator.cpp
LOCAL_CFLAGS := -std=c++11 -g -Wall -Werror
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
include $(BUILD_STATIC_LIBRARY)

# This target is necessary in order to build the static library at all.
include $(CLEAR_VARS)
LOCAL_MODULE := configumerator_shared
LOCAL_STATIC_LIBRARIES := configumerator

include $(BUILD_SHARED_LIBRARY)
