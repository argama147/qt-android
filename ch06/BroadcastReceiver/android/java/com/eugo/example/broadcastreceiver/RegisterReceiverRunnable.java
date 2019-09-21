package com.eugo.example.broadcastreceiver;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentFilter;

public class RegisterReceiverRunnable implements Runnable
{
    private Activity m_activity;
    private MyReceiver m_receiver;

    public RegisterReceiverRunnable(Activity activity) {
        m_activity = activity;
        m_receiver = new MyReceiver();
    }

    @Override
    public void run() {
        IntentFilter filter = new IntentFilter();
        filter.addAction(MyReceiver.ACTION_SAMPLE);
        m_activity.registerReceiver(m_receiver, filter);
    }

    public MyReceiver getReceiver() {
        return m_receiver;
    }
}
