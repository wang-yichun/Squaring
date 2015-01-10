package com.meyougames.squaring;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.util.Log;

import com.easyjsb.classes.AndroidJSBHelper;
import com.easyndk.classes.AndroidNDKHelper;

public class JAVABridge {

	String TAG = "JAVABridge";
	Activity activity;
	String name;

	private static JAVABridge s_bridge = null;

	public static JAVABridge getInstance() {
		if (s_bridge == null) {
			s_bridge = new JAVABridge();
		}
		return s_bridge;
	}

	public void initBridge(Activity activity) {
		Log.i(TAG, "JAVA: initBridge");
		this.activity = activity;

		AndroidNDKHelper.SetNDKReciever(this);

		name = "Hello JAVABridge";
	}

	public void javab_test(JSONObject para) throws JSONException {
		Log.i(TAG, String.format("JAVA: javab_test name: %s", name));
		
		// 接收的数据
		JSONObject dic_get = para;
		Log.i(TAG, String.format("JAVA: number_float: %f", dic_get.getDouble("number_float")));
		Log.i(TAG, String.format("JAVA: number_int: %d", dic_get.getInt("number_float")));
		Log.i(TAG, String.format("JAVA: string_value1: %s", dic_get.getString("string_value1")));
		Log.i(TAG, String.format("JAVA: string_value2: %s", dic_get.getString("string_value2")));
		Log.i(TAG, String.format("JAVA: obj_key1: %d", dic_get.getJSONObject("object_value").getInt("key1")));
		Log.i(TAG, String.format("JAVA: obj_key2: %s", dic_get.getJSONObject("object_value").getString("key2")));
		
		// 发送的数据
		JSONObject dic_send = new JSONObject();
		dic_send.put("java_string_key", "java_value");
		dic_send.put("java_int_key", 123);
		dic_send.put("java_float_key", 123.455);
		dic_send.put("java_dictionary_key", dic_get);
		
		JSONArray array_send = new JSONArray();
		array_send.put("郑东新区");
		array_send.put(123);
		
		dic_send.put("java_array_key", array_send);
		
		AndroidJSBHelper.SendMessageToJS(activity, dic_get.getString("call_back"), dic_send);
	}
}
