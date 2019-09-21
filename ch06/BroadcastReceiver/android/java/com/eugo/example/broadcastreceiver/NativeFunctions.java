package com.eugo.example.broadcastreceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.util.Log;

public class NativeFunctions {
    public static native void onReceiveNativeSample1(int data);
    public static native void onReceiveNativeSample2(String message);
}
