/*
 * Copyright (C) 2016 The CyanogenMod Project
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

#define CAMERA_PARAMETERS_EXTRA_C \
const char CameraParameters::FOCUS_MODE_MANUAL_POSITION[] = "manual"; \
const char CameraParameters::WHITE_BALANCE_MANUAL_CCT[] = "manual-cct";

#define CAMERA_PARAMETERS_EXTRA_H \
    static const char FOCUS_MODE_MANUAL_POSITION[]; \
    static const char WHITE_BALANCE_MANUAL_CCT[];
