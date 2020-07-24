package com.ekutt.example.imageconverter;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.content.pm.PackageManager;

import android.Manifest;
import android.app.AlertDialog;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

import com.ekutt.example.imageconverter.R;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("imageOps-jni");
    }
    String filepath = "";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button selectImageButton = (Button) findViewById(R.id.selectImageButton);
        selectImageButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                selectImage();
            }
        });

        Button convertToPngButton = (Button) findViewById(R.id.convertToPngButton);
        convertToPngButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                convertImage();
            }
        });
    }

    private void selectImage()
    {
        Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setType("image/*");

        startActivityForResult(intent, 1);
    }

    private void convertImage()
    {
        ActivityCompat.requestPermissions(MainActivity.this,
            new String[]{Manifest.permission.READ_EXTERNAL_STORAGE,
                        Manifest.permission.WRITE_EXTERNAL_STORAGE},
            5);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {
            case 5: {
                if (grantResults.length > 0
                    && grantResults[0] == PackageManager.PERMISSION_GRANTED) {

                    File dir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
                    String filename = this.filepath.substring(this.filepath.lastIndexOf("/")+1);
                    String rawFilename = filename.substring(0, filename.lastIndexOf("."));

                    try
                    {
                        ImageConverter.convertJPEGtoPNG(filepath, dir.getCanonicalPath()+"/"+rawFilename+".tiff");

                        new AlertDialog.Builder(this)
                            .setTitle("Success!")
                            .setMessage(rawFilename+".tiff"+" has been successfully written to Pictures directory.")
                            .create().show();
                    }
                    catch (Exception ex) {
                        new AlertDialog.Builder(this)
                            .setTitle("Error")
                            .setMessage(ex.getMessage())
                            .create().show();
                    }

                }
                else
                {
                    Toast.makeText(MainActivity.this, "Permission denied to read your External storage", Toast.LENGTH_SHORT).show();
                }
                return;
            }

            // other 'case' lines to check for other
            // permissions this app might request
        }
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        TextView view = (TextView) findViewById(R.id.textView);
        if (resultCode != RESULT_OK) {
            return;
        }
        if (requestCode == 1) {
            Uri selectedImage = data.getData();

            String[] filePathColumn = { MediaStore.Images.Media.DATA };
            Cursor cursor = getContentResolver().query(selectedImage, filePathColumn,
                null, null, null);
            cursor.moveToFirst();
            int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
            String path = cursor.getString(columnIndex);
            String filename = path.substring(path.lastIndexOf("/")+1);

            cursor.close();
            this.filepath = path;
            view.setText(filename);
        }
    }
}
