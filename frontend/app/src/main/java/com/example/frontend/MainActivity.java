package com.example.frontend;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private BluetoothAdapter bluetoothAdapter;
    private BluetoothDevice bluetoothDevice;
    private BluetoothSocket bluetoothSocket;
    private InputStream inputStream;
    private OutputStream outputStream;
    private TextView distanceTextView;
    private Button measureButton;
    private StringBuilder dataReceived = new StringBuilder();
    private boolean connected = false;
    private final UUID UUID_SERIAL_PORT_SERVICE = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); // Serial Port Service ID

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        distanceTextView = findViewById(R.id.distanceTextView);
        measureButton = findViewById(R.id.measureButton);

        // Initialize Bluetooth adapter
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null) {
            Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        // Connect to Bluetooth device
        connectToBluetoothDevice();

        // Set up button click listener
        measureButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                measureDistance();
            }
        });
    }

    private void connectToBluetoothDevice() {
        String deviceAddress = "00:00:00:00:00:00"; // Replace with your Bluetooth device address
        bluetoothDevice = bluetoothAdapter.getRemoteDevice(deviceAddress);

        new Thread(() -> {
            try {
                bluetoothSocket = bluetoothDevice.createRfcommSocketToServiceRecord(UUID_SERIAL_PORT_SERVICE);
                bluetoothSocket.connect();
                inputStream = bluetoothSocket.getInputStream();
                outputStream = bluetoothSocket.getOutputStream();
                connected = true;
            } catch (IOException e) {
                e.printStackTrace();
                connected = false;
            }
        }).start();
    }

    private void measureDistance() {
        if (!connected) {
            Toast.makeText(this, "Not connected to Bluetooth device", Toast.LENGTH_SHORT).show();
            return;
        }

        try {
            // Send command to Arduino to initiate measurement
            outputStream.write("measure".getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Remaining code for receiving data from Arduino and updating UI omitted for brevity
}
