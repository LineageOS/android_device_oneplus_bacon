#
# Copyright (C) 2016 The CyanogenMod Project
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

ifneq ($(QCPATH),)
$(call inherit-product-if-exists, $(QCPATH)/common/config/device-vendor.mk)
endif

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
	device/oneplus/bacon/overlay \
	device/oneplus/bacon/overlay-lineage

# API (for CTS backward compatibility)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.first_api_level=19

# Audio
PRODUCT_COPY_FILES += \
    device/oneplus/bacon/audio/audio_platform_info.xml:system/vendor/etc/audio_platform_info.xml \
    device/oneplus/bacon/audio/audio_policy.conf:system/vendor/etc/audio_policy.conf \
    device/oneplus/bacon/audio/mixer_paths.xml:system/vendor/etc/mixer_paths.xml

# Boot animation
TARGET_SCREEN_HEIGHT := 1920
TARGET_SCREEN_WIDTH := 1080

# Camera
PRODUCT_PACKAGES += \
    camera.bacon

# Dalvik/HWUI
$(call inherit-product-if-exists, frameworks/native/build/phone-xxhdpi-3072-dalvik-heap.mk)
$(call inherit-product-if-exists, frameworks/native/build/phone-xxhdpi-3072-hwui-memory.mk)

# Display
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

# Keylayout
PRODUCT_COPY_FILES += \
    device/oneplus/bacon/configs/synaptics-rmi-ts.kl:system/usr/keylayout/synaptics-rmi-ts.kl

PRODUCT_PACKAGES += \
    android.hardware.nfc@1.0-impl \
    com.android.nfc_extras \
    NfcNci \
    nfc_nci.bacon \
    Tag

PRODUCT_COPY_FILES += \
    device/oneplus/bacon/configs/libnfc-nxp.conf:system/etc/libnfc-nxp.conf \
    device/oneplus/bacon/configs/libnfc-brcm.conf:system/etc/libnfc-brcm.conf

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.ethernet.xml:system/etc/permissions/android.hardware.ethernet.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:system/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/base/nfc-extras/com.android.nfc_extras.xml:system/etc/permissions/com.android.nfc_extras.xml \

# Ramdisk
PRODUCT_PACKAGES += \
    fstab.bacon \
    init.bacon.rc \
    init.qcom.usb.rc \
    init.recovery.bacon.rc \
    libinit_bacon \
    ueventd.bacon.rc

# System properties
TARGET_SYSTEM_PROP := device/oppo/msm8974-common/system.prop device/oneplus/bacon/system.prop

# Call the proprietary setup
$(call inherit-product, vendor/oneplus/bacon/bacon-vendor.mk)

# Inherit from msm8974-common
$(call inherit-product, device/oppo/msm8974-common/msm8974.mk)
