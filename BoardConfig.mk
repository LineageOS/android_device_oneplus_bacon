#
# Copyright (C) 2016 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# inherit from Oppo msm8974-common
-include device/oppo/msm8974-common/BoardConfigCommon.mk

DEVICE_PATH := device/oneplus/bacon

# Kernel
BOARD_KERNEL_CMDLINE := androidboot.hardware=bacon ehci-hcd.park=3 androidboot.bootdevice=msm_sdcc.1
TARGET_KERNEL_CONFIG := lineageos_bacon_defconfig
TARGET_KERNEL_SOURCE := kernel/oppo/msm8974

# Assert
TARGET_OTA_ASSERT_DEVICE := bacon,A0001

# Audio
AUDIO_FEATURE_ENABLED_LOW_LATENCY_CAPTURE := true
AUDIO_FEATURE_LOW_LATENCY_PRIMARY := true
USE_XML_AUDIO_POLICY_CONF := 1

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(DEVICE_PATH)/bluetooth

# Display
TARGET_SCREEN_DENSITY := 480

# Filesystem
BOARD_BOOTIMAGE_PARTITION_SIZE     := 16777216
BOARD_CACHEIMAGE_PARTITION_SIZE    := 536870912
BOARD_PERSISTIMAGE_PARTITION_SIZE  := 33554432
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 16777216
BOARD_ROOT_EXTRA_FOLDERS := firmware persist
BOARD_SYSTEMIMAGE_PARTITION_SIZE   := 1388314624
BOARD_USERDATAIMAGE_PARTITION_SIZE := 13271448576
BOARD_USERDATAEXTRAIMAGE_PARTITION_SIZE := 59914792960
BOARD_USERDATAEXTRAIMAGE_PARTITION_NAME := 64G

TARGET_FS_CONFIG_GEN := $(DEVICE_PATH)/config.fs

# Init
SOONG_CONFIG_OPPO_MSM8974_INIT_DEVICE_LIB := //$(DEVICE_PATH):libinit_bacon

# Properties
TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

# Recovery
TARGET_RECOVERY_FSTAB := $(DEVICE_PATH)/rootdir/etc/fstab.recovery

# SELinux
BOARD_SEPOLICY_DIRS += \
    $(DEVICE_PATH)/sepolicy

# TWRP
ifeq ($(WITH_TWRP),true)
TARGET_RECOVERY_DEVICE_DIRS += $(DEVICE_PATH)/twrp
BOARD_HAS_NO_REAL_SDCARD := true
RECOVERY_SDCARD_ON_DATA := true
endif

# Inherit from the proprietary version
include vendor/oneplus/bacon/BoardConfigVendor.mk
