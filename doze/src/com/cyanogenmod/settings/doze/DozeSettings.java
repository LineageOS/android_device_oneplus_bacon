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

import android.app.Activity;
import android.os.Bundle;
import android.view.MenuItem;

import com.android.settingslib.drawer.SettingsDrawerActivity;

/**
 * Created by shade on 10/14/16.
 */

public class DozeSettings extends SettingsDrawerActivity {

    private static final String TAG_DOZE = "doze";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.doze);

        getFragmentManager().beginTransaction().replace(R.id.content_frame,
                new DozeSettingsFragment(), TAG_DOZE).commit();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            onBackPressed();
            return true;
        }
        return false;
    }
}
