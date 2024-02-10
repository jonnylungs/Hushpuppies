package com.example.hushpuppies

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.Button
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import java.io.IOException
import java.util.*

class MainActivity : AppCompatActivity() {

    private val deviceaddress = "00:00:00:00:00:00" // Replace with your device's address
    private val serviceuuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB") // Standard UUID for SPP
    private var bluetoothAdapter: BluetoothAdapter? = null
    private var bluetoothDevice: BluetoothDevice? = null
    private var bluetoothSocket: BluetoothSocket? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button1 = findViewById<Button>(R.id.button1)
        val button2 = findViewById<Button>(R.id.button2)
        val button3 = findViewById<Button>(R.id.button3)
        val button4 = findViewById<Button>(R.id.button4)
        val button5 = findViewById<Button>(R.id.button5)

        button1.setOnClickListener { sendCommand("Command 1") }
        button2.setOnClickListener { sendCommand("Command 2") }
        button3.setOnClickListener { sendCommand("Command 3") }
        button4.setOnClickListener { sendCommand("Command 4") }
        button5.setOnClickListener { sendCommand("Command 5") }

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
        if (bluetoothAdapter == null) {
            Toast.makeText(this, "Bluetooth not supported", Toast.LENGTH_SHORT).show()
            finish()
            return
        }
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        menuInflater.inflate(R.menu.main_menu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.menu_connect -> {
                connectToBluetoothDevice()
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }

    private fun connectToBluetoothDevice() {
        bluetoothDevice = bluetoothAdapter?.getRemoteDevice(deviceaddress)
        try {
            bluetoothSocket = bluetoothDevice?.createRfcommSocketToServiceRecord(serviceuuid)
            bluetoothSocket?.connect()
            // Handle successful connection
            Toast.makeText(this, "Connected to Bluetooth device", Toast.LENGTH_SHORT).show()
        } catch (e: IOException) {
            // Handle connection failure
            e.printStackTrace()
            Toast.makeText(this, "Failed to connect to Bluetooth device", Toast.LENGTH_SHORT).show()
        }
    }

    private fun sendCommand(command: String) {
        if (bluetoothSocket != null && bluetoothSocket!!.isConnected) {
            try {
                bluetoothSocket!!.outputStream.write(command.toByteArray())
                // Handle command sent successfully
                Toast.makeText(this, "Command sent: $command", Toast.LENGTH_SHORT).show()
            } catch (e: IOException) {
                // Handle error sending command
                e.printStackTrace()
                Toast.makeText(this, "Failed to send command", Toast.LENGTH_SHORT).show()
            }
        } else {
            Toast.makeText(this, "Bluetooth device not connected", Toast.LENGTH_SHORT).show()
        }
    }
}
