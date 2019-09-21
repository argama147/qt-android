package com.eugo.example.broadcastreceiver;

import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import org.qtproject.qt5.android.bindings.QtActivity;

import static com.eugo.example.broadcastreceiver.MyReceiver.ACTION_SAMPLE;

public class MyActivity extends org.qtproject.qt5.android.bindings.QtActivity
{
    private MyReceiver mReceiver;

    public void registerBroadcastReceiver() {
        RegisterReceiverRunnable runnable = new RegisterReceiverRunnable(this);
        mReceiver = runnable.getReceiver();
        runOnUiThread(runnable);
    }

    public void sendBroadcast() {
        final Intent intent = new Intent(ACTION_SAMPLE);
        intent.putExtra("test1", 100);
        intent.putExtra("test2", "test2Data");
        sendBroadcast(intent);
    }

    protected void onDestroy() {
        if (mReceiver != null) {
            unregisterReceiver(mReceiver);
        }

        super.onDestroy();
    }
}
