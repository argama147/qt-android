package com.eugo.example.jnienvsample;

import android.content.Context;
import android.util.Log;

public class MyClass {
    private final static String TAG = "MyClass";

    //【1】
    public void method1() {
        Log.d(TAG, "method1()");
    }

    //【2】
    public int method2() {
        Log.d(TAG, "method2()");
        return 10;
    }

    //【3】
    public void method3(int data) {
        Log.d(TAG, "method3() data=" + data);
    }

    //【4】
    public int method4(int data) {
        Log.d(TAG, "method4() data=" + data);
        return data + 100;
    }

    //【5】
    public int method5(int data, long data2) {
        Log.d(TAG, "method5() data=" + data + " data2=" + data2);
        return data + (int)data2;
    }

    //【6】
    public void method6(String str) {
        Log.d(TAG, "method6() str=" + str);
    }

    //【6-2】
    public void method6(Context context, String str) {
        Log.d(TAG, "method6-2() str=" + str);
    }

    //【7】
    public String method7() {
        Log.d(TAG, "method7()");
        return "method7";
    }

    //【8】
    public String method8(String str) {
        Log.d(TAG, "method8() str=" + str);
        return "method8:" + str;
    }

    //【9】
    public String method9(String str1, String str2) {
        Log.d(TAG, "method9() str1=" + str1 + " str2=" + str2);
        return str1 + " " + str2;
    }
}
