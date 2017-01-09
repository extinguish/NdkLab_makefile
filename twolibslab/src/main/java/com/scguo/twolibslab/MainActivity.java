package com.scguo.twolibslab;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        TextView textView = new TextView(this);


        int x = 3000;
        int y = 2000;
        System.loadLibrary("twolibs_second");

        int z = add(x, y);
        textView.setText("the result are " + z);
        setContentView(textView);
    }

    public native int add(int x, int y);
}
