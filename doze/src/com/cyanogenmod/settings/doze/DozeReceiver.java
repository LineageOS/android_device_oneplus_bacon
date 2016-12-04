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
package com.cyanogenmod.settings.doze;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import cyanogenmod.preference.RemotePreferenceUpdater;

public class DozeReceiver extends RemotePreferenceUpdater {

    private static final boolean DEBUG = false;
    private static final String TAG = "OneplusDoze";

    private static final String DOZE_CATEGORY_KEY = "doze_device_settings";

    @Override
    public void onReceive(Context context, Intent intent) {
        super.onReceive(context, intent);

        if (intent.getAction().equals(Intent.ACTION_BOOT_COMPLETED)) {
            if (Utils.isDozeEnabled(context) && Utils.sensorsEnabled(context)) {
                if (DEBUG) Log.d(TAG, "Starting service");
                Utils.startService(context);
            }
        }
    }

    @Override
    public String getSummary(Context context, String key) {
        if (DOZE_CATEGORY_KEY.equals(key)) {
            return DozeSettingsFragment.getDozeSummary(context);
        }
        return null;
    }

    static void notifyChanged(Context context) {
        notifyChanged(context, DOZE_CATEGORY_KEY);
    }
}
