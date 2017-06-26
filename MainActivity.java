package com.example.borameral.gpbarcode;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.content.Intent;
import android.content.Context;

import android.net.Uri;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v4.content.ContextCompat;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebView;
import android.widget.ImageView;
import android.widget.TextView;
import android.telephony.SmsManager;

import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity {
    Button button_1;
    Button button_2;
    Button button_3;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        addListenerOnButton();
    }
    public void addListenerOnButton() {
        final Context context = this;

        button_1 = (Button) findViewById(R.id.button1);
        button_1.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(context, BarcodeScanner.class);
                startActivity(intent);
            }
        });

        button_2 = (Button) findViewById(R.id.button2);
        button_2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(context, SMS.class);
                startActivity(intent);
            }
        });

        button_3=(Button) findViewById(R.id.button3);
        button_3.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(context, billScanner.class);
                startActivity(intent);
        /*button_3.setOnClickListener(new OnClickListener() {
            public void onClick(View arg0) {
                Uri uri = Uri.parse("http://online.gedizelektrik.com.tr/hizliborcsorgulama.aspx");
                Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                WebView webView = new WebView(context);
                setContentView(webView);
                startActivity(intent);*/
            }

        });
    }
}
