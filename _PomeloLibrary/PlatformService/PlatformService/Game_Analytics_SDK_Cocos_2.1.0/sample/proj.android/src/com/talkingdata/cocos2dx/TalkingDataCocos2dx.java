
package com.talkingdata.cocos2dx;

import com.tendcloud.tenddata.TalkingDataGA;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.util.Log;

public class TalkingDataCocos2dx extends Cocos2dxActivity {

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TalkingDataGA.sPlatformType = TalkingDataGA.PLATFORM_TYPE_COCOS2DX;
        // 代码初始化, 也可以在AndroidManifest.xml中声明.
         TalkingDataGA.init(this, "2E9D3A639C5BA2677DD652E02FEBC489", "cocos");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d("TalkingDataCocos2dx", "onResume");
        TalkingDataGA.onResume(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d("TalkingDataCocos2dx", "onPause");
        TalkingDataGA.onPause(this);
    }

    static {
        System.loadLibrary("talkingdata");
    }
}
