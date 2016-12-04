/*
 * Copyright (C) 2015 The CyanogenMod Project
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

import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.database.ContentObserver;
import android.os.Bundle;
import android.os.Handler;
import android.support.v14.preference.PreferenceFragment;
import android.support.v14.preference.SwitchPreference;
import android.support.v7.preference.Preference;
import android.support.v7.preference.Preference.OnPreferenceChangeListener;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.Switch;

public class DozeSettingsFragment extends PreferenceFragment implements OnPreferenceChangeListener,
        CompoundButton.OnCheckedChangeListener {

    private SharedPreferences mPreferences;

    private Switch mSwitch;

    private SwitchPreference mPickUpPreference;
    private SwitchPreference mHandwavePreference;
    private SwitchPreference mPocketPreference;

    private ContentObserver mDozeObserver = new ContentObserver(new Handler()) {
        @Override
        public void onChange(boolean selfChange) {
            super.onChange(selfChange);

            boolean enabled = Utils.isDozeEnabled(getActivity());

            updateSwitches(Utils.isDozeEnabled(getActivity()));
            DozeReceiver.notifyChanged(getActivity());
        }
    };

    static String getDozeSummary(Context context) {
        if (Utils.isDozeEnabled(context)) {
            return context.getString(R.string.ambient_display_summary_on);
        }
        return context.getString(R.string.ambient_display_summary_off);
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        getActivity().getActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view = LayoutInflater.from(getContext()).inflate(R.layout.doze, container, false);
        ((ViewGroup) view).addView(super.onCreateView(inflater, container, savedInstanceState));
        return view;
    }

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        addPreferencesFromResource(R.xml.doze_settings);

        // get shared preference
        mPreferences = getActivity().getSharedPreferences("doze_settings", Activity.MODE_PRIVATE);

        if (savedInstanceState == null && !mPreferences.getBoolean("first_help_shown", false)) {
            showHelp();
        }

        mPickUpPreference =
                (SwitchPreference) findPreference(Utils.PICK_UP_KEY);
        mPickUpPreference.setOnPreferenceChangeListener(this);

        mHandwavePreference =
                (SwitchPreference) findPreference(Utils.GESTURE_HAND_WAVE_KEY);
        mHandwavePreference.setOnPreferenceChangeListener(this);

        mPocketPreference =
                (SwitchPreference) findPreference(Utils.GESTURE_POCKET_KEY);
        mPocketPreference.setOnPreferenceChangeListener(this);
    }

    @Override
    public void onResume() {
        super.onResume();
        getActivity().getContentResolver().registerContentObserver(
                Utils.DOZE_ENABLED_URI, false, mDozeObserver);
        updateSwitches(Utils.isDozeEnabled(getActivity()));
    }

    @Override
    public void onPause() {
        super.onPause();
        getActivity().getContentResolver().unregisterContentObserver(mDozeObserver);
    }

    private void updateSwitches(boolean enabled) {
        mPickUpPreference.setEnabled(enabled);
        mHandwavePreference.setEnabled(enabled);
        mPocketPreference.setEnabled(enabled);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        View switchBar = view.findViewById(R.id.switch_bar);
        mSwitch = (Switch) switchBar.findViewById(android.R.id.switch_widget);
        mSwitch.setChecked(Utils.isDozeEnabled(getActivity()));
        mSwitch.setOnCheckedChangeListener(this);

        switchBar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mSwitch.setChecked(!mSwitch.isChecked());
            }
        });
    }


    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        final String key = preference.getKey();
        final boolean value = (Boolean) newValue;
        if (Utils.PICK_UP_KEY.equals(key)) {
            mPickUpPreference.setChecked(value);
        } else if (Utils.GESTURE_HAND_WAVE_KEY.equals(key)) {
            mHandwavePreference.setChecked(value);
        } else if (Utils.GESTURE_POCKET_KEY.equals(key)) {
            mPocketPreference.setChecked(value);
        } else {
            return false;
        }

        Utils.startService(getActivity());
        return true;
    }

    @Override
    public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
        Utils.enableDoze(b, getActivity());
    }

    public static class HelpDialogFragment extends DialogFragment {
        @Override
        public Dialog onCreateDialog(Bundle savedInstanceState) {
            return new AlertDialog.Builder(getActivity())
                    .setTitle(R.string.doze_settings_help_title)
                    .setMessage(R.string.doze_settings_help_text)
                    .setNegativeButton(R.string.dlg_ok, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.cancel();
                        }
                    })
                    .create();
        }

        @Override
        public void onCancel(DialogInterface dialog) {
            getActivity().getSharedPreferences("doze_settings", Activity.MODE_PRIVATE)
                    .edit()
                    .putBoolean("first_help_shown", true)
                    .commit();
        }
    }

    private void showHelp() {
        HelpDialogFragment fragment = new HelpDialogFragment();
        fragment.show(getFragmentManager(), "help_dialog");
    }
}
