package com.eugo.example.qtactivitysample;

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView

class SubActivity : AppCompatActivity() {
    private var mMessage: String? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sub)

        val intent = getIntent()
        val message = String(intent.getByteArrayExtra(MainActivity.EXTRA_MAIN_MSG_KEY))
        val tv = findViewById<TextView>(R.id.textViewData)
        tv.setText(message)
        mMessage = message

        val btn = findViewById<Button>(R.id.button_close)
        btn.setOnClickListener {
            val intent = Intent()
            intent.putExtra(MainActivity.EXTRA_SUB_MSG_KEY, mMessage!! + " and SubActivityData")
            setResult(RESULT_OK, intent)
            finish()
        }
    }
}
