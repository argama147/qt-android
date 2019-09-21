package com.eugo.example.activityjavasample;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class SubActivity extends AppCompatActivity {
    private String mMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sub);

        Intent intent = getIntent();
        String message = new String(intent.getByteArrayExtra(MainActivity.EXTRA_MAIN_MSG_KEY));
        TextView tv = findViewById(R.id.textViewData);
        tv.setText(message);
        mMessage = message;

        Button btn = findViewById(R.id.button_close);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.putExtra(MainActivity.EXTRA_SUB_MSG_KEY, mMessage + " and SubActivityData");
                setResult(RESULT_OK, intent);
                finish();
            }
        });
    }
}
