package com.example.borameral.gpbarcode;


import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.widget.TextView;
import android.os.Bundle;

/**
 * Created by BoraMeral on 18.05.2017.
 */

public class BarcodeScanner extends Activity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_barcode_scanner);
    }
    public void HandleClick(View arg0) {
        Intent intent = new Intent("com.google.zxing.client.android.SCAN");
        switch(arg0.getId()){
            case R.id.butQR:
                intent.putExtra("SCAN_MODE", "QR_CODE_MODE");
                break;
            case R.id.butProd:
                intent.putExtra("SCAN_MODE", "PRODUCT_MODE");
                break;
            case R.id.butOther:
                intent.putExtra("SCAN_FORMATS", "CODE_39,CODE_93,CODE_128,DATA_MATRIX,ITF,CODABAR");
                break;
        }
        startActivityForResult(intent, 0); //Barcode Scanner to scan for us
    }
    public void onActivityResult(int requestCode, int resultCode, Intent intent) {
        if (requestCode == 0) {
            TextView tvStatus=(TextView)findViewById(R.id.tvStatus);
            TextView tvResult=(TextView)findViewById(R.id.tvResult);
            if (resultCode == RESULT_OK) {
                tvStatus.setText(intent.getStringExtra("SCAN_RESULT_FORMAT"));
                tvResult.setText(intent.getStringExtra("SCAN_RESULT"));
            } else if (resultCode == RESULT_CANCELED) {
                tvStatus.setText("Press a button to start a scan.");
                tvResult.setText("Scan cancelled.");
            }
        }
    }


}
