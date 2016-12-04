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

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.IBinder;
import android.util.Log;

public class DozeService extends Service {
    private static final String TAG = "DozeService";
    private static final boolean DEBUG = false;

    private ProximitySensor mProximitySensor;
    private TiltSensor mTiltSensor;

    @Override
    public void onCreate() {
        if (DEBUG) Log.d(TAG, "Creating service");
        mProximitySensor = new ProximitySensor(this);
        mTiltSensor = new TiltSensor(this);

        IntentFilter screenStateFilter = new IntentFilter(Intent.ACTION_SCREEN_ON);
        screenStateFilter.addAction(Intent.ACTION_SCREEN_OFF);
        registerReceiver(mScreenStateReceiver, screenStateFilter);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (DEBUG) Log.d(TAG, "Starting service");
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        if (DEBUG) Log.d(TAG, "Destroying service");
        super.onDestroy();
        this.unregisterReceiver(mScreenStateReceiver);
        mProximitySensor.disable();
        mTiltSensor.disable();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    private void onDisplayOn() {
        if (DEBUG) Log.d(TAG, "Display on");
        if (Utils.pickUpEnabled(this)) {
            mTiltSensor.disable();
        }
        if (Utils.handwaveGestureEnabled(this) ||
                Utils.pocketGestureEnabled(this)) {
            mProximitySensor.disable();
        }
    }

    private void onDisplayOff() {
        if (DEBUG) Log.d(TAG, "Display off");
        if (Utils.pickUpEnabled(this)) {
            mTiltSensor.enable();
        }
        if (Utils.handwaveGestureEnabled(this) ||
                Utils.pocketGestureEnabled(this)) {
            mProximitySensor.enable();
        }
    }

    private BroadcastReceiver mScreenStateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction().equals(Intent.ACTION_SCREEN_ON)) {
                onDisplayOn();
            } else if (intent.getAction().equals(Intent.ACTION_SCREEN_OFF)) {
                onDisplayOff();
            }
        }
    };
}
