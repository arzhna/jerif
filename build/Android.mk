LOCAL_PATH := $(call my-dir)
JERIF_ROOT_PATH := $(LOCAL_PATH)

# =====================================================
# For library
# =====================================================
include $(CLEAR_VARS)

LOCAL_C_INCLUDES:= $(common_C_INCLUDES) $(JERIF_ROOT_PATH)/include
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := \
	src/jerif_check.c \
	src/jerif_detect.c \
	src/jerif_misc.c \
	src/jerif_stack.c

LOCAL_MODULE := libjerif

include $(BUILD_SHARED_LIBRARY)

# =====================================================
# For testing
# =====================================================
include $(CLEAR_VARS)

LOCAL_JERIF := true
LOCAL_C_INCLUDES:= $(common_C_INCLUDES) $(JERIF_ROOT_PATH)/include
LOCAL_SRC_FILES:= src/jerif.c
LOCAL_MODULE := jerif
LOCAL_SHARED_LIBRARIES:= libjerif
LOCAL_MODULE_TAGS := debug

include $(BUILD_EXECUTABLE)
