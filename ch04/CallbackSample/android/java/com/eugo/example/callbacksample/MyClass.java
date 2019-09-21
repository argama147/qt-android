package com.eugo.example.callbacksample;

import android.util.Log;

public class MyClass {
    private static final String TAG = "MyClass";

    public static void method1(int x)
    {
        Log.d(TAG, "method1 x=" + x);
        callNativeInt(x);
    }

    public static void method2(String str)
    {
        Log.d(TAG, "method2 str=" + str);
        callNativeString("method2:" + str);
    }

    private static native void callNativeInt(int x);
    private static native void callNativeString(String str);
}
