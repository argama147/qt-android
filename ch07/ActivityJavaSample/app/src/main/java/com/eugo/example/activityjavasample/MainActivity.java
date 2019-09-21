package com.eugo.example.activityjavasample;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public static final String EXTRA_MAIN_MSG_KEY = "MainActivityData";
    public static final String EXTRA_SUB_MSG_KEY = "SubActivityData";
    public static final int REQUEST_CODE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btn = findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startSubActivity(MainActivity.this);
            }
        });

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        switch (requestCode) {
            case REQUEST_CODE:
                if(resultCode == RESULT_OK){
                    TextView tvResult = findViewById(R.id.textViewResult);
                    tvResult.setText(data.getStringExtra(EXTRA_SUB_MSG_KEY));
                }
                break;
        }
    }

    private void startSubActivity(Context context){
        Intent intent = new Intent(context, SubActivity.class);
        intent.putExtra(EXTRA_MAIN_MSG_KEY, "MainActivityData");
        startActivityForResult(intent, REQUEST_CODE);
    }
}
