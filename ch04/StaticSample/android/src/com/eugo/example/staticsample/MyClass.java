package com.eugo.example.staticsample;

import android.util.Log;

public class MyClass {
    private final static String TAG = "MyClass";

    //【1】
    public static void method1() {
        Log.d(TAG, "method1()");
    }

    //【2】
    public static int method2() {
        Log.d(TAG, "method2()");
        return 10;
    }

    //【3】
    public static void method3(int data) {
        Log.d(TAG, "method3() data=" + data);
    }

    //【4】
    public static int method4(int data) {
        Log.d(TAG, "method4() data=" + data);
        return data + 100;
    }

    //【5】
    public static int method5(int data, long data2) {
        Log.d(TAG, "method5() data=" + data + " data2=" + data2);
        return data + (int)data2;
    }

    //【6】
    public static void method6(String str) {
        Log.d(TAG, "method6() str=" + str);
    }

    //【7】
    public static String method7() {
        Log.d(TAG, "method7()");
        return "method7";
    }

    //【8】
    public static String method8(String str) {
        Log.d(TAG, "method8() str=" + str);
        return "method8:" + str;
    }

    //【9】
    public static String method9(String str1, String str2) {
        Log.d(TAG, "method9() str1=" + str1 + " str2=" + str2);
        return str1 + " " + str2;
    }
}
