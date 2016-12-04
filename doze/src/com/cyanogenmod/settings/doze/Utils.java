/*
 * Copyright (c) 2015 The CyanogenMod Project
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
import android.net.Uri;
import android.os.UserHandle;
import android.support.v7.preference.PreferenceManager;
import android.provider.Settings;
import android.util.Log;

import static android.provider.Settings.Secure.DOZE_ENABLED;

public final class Utils {

    private static final String TAG = "DozeUtils";
    private static final boolean DEBUG = false;

    private static final String DOZE_INTENT = "com.android.systemui.doze.pulse";

    protected static final String AMBIENT_DISPLAY_KEY = "doze_enabled";
    protected static final String PICK_UP_KEY = "pick_up";
    protected static final String GESTURE_HAND_WAVE_KEY = "gesture_hand_wave";
    protected static final String GESTURE_POCKET_KEY = "gesture_pocket";

    public static final Uri DOZE_ENABLED_URI = Settings.Secure.getUriFor(DOZE_ENABLED);

    protected static void startService(Context context) {
        if (DEBUG) Log.d(TAG, "Starting service");
        context.startService(new Intent(context, DozeService.class));
    }

    protected static void stopService(Context context) {
        if (DEBUG) Log.d(TAG, "Stopping service");
        context.stopService(new Intent(context, DozeService.class));
    }

    protected static boolean isDozeEnabled(Context context) {
        return Settings.Secure.getInt(context.getContentResolver(),
                DOZE_ENABLED, 1) != 0;
    }

    protected static boolean enableDoze(boolean enable, Context context) {
        boolean dozeEnabled = Settings.Secure.putInt(context.getContentResolver(),
                              DOZE_ENABLED, enable ? 1 : 0);
        if (enable) {
            startService(context);
        } else {
            stopService(context);
        }
        return dozeEnabled;
    }

    protected static void launchDozePulse(Context context) {
        if (DEBUG) Log.d(TAG, "Launch doze pulse");
        context.sendBroadcastAsUser(new Intent(DOZE_INTENT),
                new UserHandle(UserHandle.USER_CURRENT));
    }

    protected static boolean pickUpEnabled(Context context) {
        return PreferenceManager.getDefaultSharedPreferences(context)
                .getBoolean(PICK_UP_KEY, false);
    }

    protected static boolean handwaveGestureEnabled(Context context) {
        return PreferenceManager.getDefaultSharedPreferences(context)
                .getBoolean(GESTURE_HAND_WAVE_KEY, false);
    }

    protected static boolean pocketGestureEnabled(Context context) {
        return PreferenceManager.getDefaultSharedPreferences(context)
                .getBoolean(GESTURE_POCKET_KEY, false);
    }

    protected static boolean sensorsEnabled(Context context) {
        return pickUpEnabled(context) || handwaveGestureEnabled(context)
                || pocketGestureEnabled(context);
    }
}
