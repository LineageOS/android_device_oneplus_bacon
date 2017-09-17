/*
 * Copyright (C) 2017 The LineageOS jProject
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hidl/HidlTransportSupport.h>
#include "Usb.h"

using android::sp;

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::usb::V1_0::IUsb;
using android::hardware::usb::V1_0::implementation::Usb;

using android::status_t;
using android::OK;

int main() {
    android::sp<IUsb> service = new Usb();

    configureRpcThreadpool(1, true /*callerWillJoin*/);
    status_t status = service->registerAsService();

    if (status != OK) {
        ALOGE("Cannot register USB HAL service");
        return 1;
    }

    ALOGI("USB HAL Ready.");
    joinRpcThreadpool();
    // Under noraml cases, execution will not reach this line.
    ALOGI("USB HAL failed to join thread pool.");
    return 1;
}
