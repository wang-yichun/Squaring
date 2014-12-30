/*
 * Copyright (C) 2012 Soomla Inc.
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

package com.soomla.store;

import android.util.Log;

public class StoreUtils {

    public static void LogDebug(String tag, String message) {
        if (StoreConfig.logDebug) {
            Log.d(tag, message);
        }
    }

    public static void LogWarning(String tag, String message) {
        Log.w(tag, message);
    }

    public static void LogError(String tag, String message) {
        Log.e(tag, message);
    }

    private static String TAG = "SOOMLA StoreUtils";
}
