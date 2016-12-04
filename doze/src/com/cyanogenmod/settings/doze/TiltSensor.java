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
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.os.SystemClock;
import android.util.Log;

public class TiltSensor implements SensorEventListener {

    private static final boolean DEBUG = false;
    private static final String TAG = "TiltSensor";

    private static final int SENSOR_WAKELOCK_DURATION = 200;
    private static final int BATCH_LATENCY_IN_MS = 100;
    private static final int MIN_PULSE_INTERVAL_MS = 2500;

    private PowerManager mPowerManager;
    private SensorManager mSensorManager;
    private Sensor mSensor;
    private WakeLock mSensorWakeLock;
    private Context mContext;

    private long mEntryTimestamp;

    public TiltSensor(Context context) {
        mContext = context;
        mPowerManager = (PowerManager) mContext.getSystemService(Context.POWER_SERVICE);
        mSensorManager = (SensorManager) mContext.getSystemService(Context.SENSOR_SERVICE);
        mSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_TILT_DETECTOR);
        mSensorWakeLock = mPowerManager.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK,
                "SensorWakeLock");
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (DEBUG) Log.d(TAG, "Got sensor event: " + event.values[0]);

        long delta = SystemClock.elapsedRealtime() - mEntryTimestamp;
        if (delta < MIN_PULSE_INTERVAL_MS) {
            return;
        } else {
            mEntryTimestamp = SystemClock.elapsedRealtime();
        }

        if (event.values[0] == 1) {
            Utils.launchDozePulse(mContext);
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        /* Empty */
    }

    protected void enable() {
        if (DEBUG) Log.d(TAG, "Enabling");
        mSensorManager.registerListener(this, mSensor,
                SensorManager.SENSOR_DELAY_NORMAL, BATCH_LATENCY_IN_MS * 1000);
        mEntryTimestamp = SystemClock.elapsedRealtime();
    }

    protected void disable() {
        if (DEBUG) Log.d(TAG, "Disabling");
        mSensorManager.unregisterListener(this, mSensor);
    }
}
