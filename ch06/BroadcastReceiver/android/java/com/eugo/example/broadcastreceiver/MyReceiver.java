package com.eugo.example.broadcastreceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.util.Log;

public class MyReceiver extends BroadcastReceiver {
    public static final String ACTION_SAMPLE
            = "com.eugo.example.broadcastreceiver.intent.action.SAMPLE";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals(ACTION_SAMPLE)) {
            int test1 = intent.getIntExtra("test1", -1);
            NativeFunctions.onReceiveNativeSample1(test1);
            String test2 = intent.getStringExtra("test2");
            NativeFunctions.onReceiveNativeSample2(test2);
        }
    }
}
