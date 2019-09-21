package com.eugo.example.qtactivitysample;

import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity
{
    public static final String EXTRA_MAIN_MSG_KEY = "MainActivityData";
    public static final String EXTRA_SUB_MSG_KEY = "SubActivityData";
    public static final int REQUEST_CODE = 1;

    public static void startSubActivity(Context context){
        Intent intent = new Intent(context, SubActivity.class);
        intent.putExtra(EXTRA_MAIN_MSG_KEY, "MainActivityData");
        context.startActivity(intent);
    }
}
