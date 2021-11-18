package cz.antecky.bthermo

import android.Manifest
import android.bluetooth.*
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.bluetooth.le.ScanSettings
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.content.pm.PackageManager
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import cz.antecky.bthermo.Utils.gotPermission
import cz.antecky.bthermo.Utils.toast

class MainActivity : AppCompatActivity() {
    private val TAG = "MainActivity"
    private val BLUETOOTH_TURN_ON_CODE = 21
    private val PERMISSION_REQUEST = 21
    private val DEVICE_NAME = "BThermo"

    private var isConnected = false

    private val scanSettings = ScanSettings.Builder()
        .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
        .build()

    private val btAdapter: BluetoothAdapter? by lazy {
        val bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothManager.adapter
    }

    private val btScanner by lazy {
        btAdapter!!.bluetoothLeScanner
    }

    private val gattCallback = object : BluetoothGattCallback() {
        override fun onConnectionStateChange(gatt: BluetoothGatt?, status: Int, newState: Int) {
            super.onConnectionStateChange(gatt, status, newState)
            when (newState) {
                BluetoothProfile.STATE_CONNECTED -> {
                    isConnected = true
                    Log.i(TAG, "GATT STATE_CONNECTED")
                }
                BluetoothProfile.STATE_DISCONNECTED -> {
                    isConnected = false
                    Log.i(TAG, "GATT STATE_DISCONNECTED")
                }
            }
        }

    }

    private val scanCallback = object : ScanCallback() {
        override fun onScanResult(callbackType: Int, result: ScanResult?) {
            super.onScanResult(callbackType, result)
            result?.let {
                val device = it.device
                val name = device.name

                Log.i(TAG, name)

                if (name == DEVICE_NAME) {
                    connect(device)
                }
            }
        }

        override fun onScanFailed(errorCode: Int) {
            super.onScanFailed(errorCode)
            Log.i(TAG, "onScanFailed errorCode: $errorCode")
        }
    }


    private fun connect(device: BluetoothDevice) {
        btScanner.stopScan(scanCallback)
        device.connectGatt(this, false, gattCallback)

    }

    private val isBtCapable: Boolean
        get() = btAdapter != null

    private val isBtEnabled: Boolean
        get() = btAdapter!!.isEnabled

    private fun enableBt() {
        startActivityForResult(
            Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), BLUETOOTH_TURN_ON_CODE
        );
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        Log.i(TAG, "onCreate")

    }

    override fun onResume() {
        super.onResume()

        Log.i(TAG, "onResume")
        Log.i(TAG, "isConnected: $isConnected")
        findDevice()
    }

    private fun findDevice() {
        if (!isBtCapable) {
            toast( "BT is NOT supported");
            return
        }

        if (!isBtEnabled) {
            isConnected = false
            enableBt();
            return;
        }

        if (isConnected) {
            return
        }

        if (gotPermissions()) {
            Log.i(TAG, "startScan")
            btScanner.startScan(null, scanSettings, scanCallback)
        }
    }

    private fun gotPermissions(): Boolean {
        val version = Build.VERSION.SDK_INT
        Log.i(TAG, "SDK version $version")

        if (version >= Build.VERSION_CODES.S) {
            val gotScan = gotPermission(
                Manifest.permission.BLUETOOTH_SCAN
            )

            Log.i(TAG, "BLUETOOTH_SCAN: $gotScan")

            val gotConnect = gotPermission(
                Manifest.permission.BLUETOOTH_CONNECT
            )

            Log.i(TAG, "BLUETOOTH_CONNECT: $gotConnect")

            if (!gotScan || !gotConnect) {
                requestPermissions(
                    arrayOf(
                        Manifest.permission.BLUETOOTH_SCAN,
                        Manifest.permission.BLUETOOTH_CONNECT
                    ),
                    PERMISSION_REQUEST
                )
                return false
            }


        } else {
            val gotFine = gotPermission(
                 Manifest.permission.ACCESS_FINE_LOCATION
            )

            Log.i(TAG, "ACCESS_FINE_LOCATION: $gotFine")

            if (!gotFine) {
                requestPermissions(
                    arrayOf(Manifest.permission.ACCESS_FINE_LOCATION),
                    PERMISSION_REQUEST
                )
                return false
            }
        }

        return true
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        when (requestCode) {
            BLUETOOTH_TURN_ON_CODE -> {
                if (!isBtEnabled) {
                    toast( "BT is disabled");
                } else {
                    findDevice()
                }
            }
        }
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)

        if (requestCode == PERMISSION_REQUEST) { // Checks if the result is for the COARSE_LOCATION request.
            if (grantResults.isNotEmpty() && grantResults.all { it == PackageManager.PERMISSION_GRANTED }) {
                findDevice()
            } else {
                toast( "The permission is required for BT")
            }
        }
    }
}