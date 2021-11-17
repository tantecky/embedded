package cz.antecky.bthermo

import android.Manifest
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
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

    private val btAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter();

    // Create a BroadcastReceiver for ACTION_FOUND.
    private val receiver = object : BroadcastReceiver() {

        override fun onReceive(context: Context, intent: Intent) {
            when (intent.action!!) {
                BluetoothDevice.ACTION_FOUND -> {
                    // Discovery has found a device. Get the BluetoothDevice
                    // object and its info from the Intent.
                    val device: BluetoothDevice =
                        intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE)!!
                    val deviceName = device.name
                    Log.i(TAG, deviceName)

                    if(deviceName == DEVICE_NAME) {

                    }
                }
            }
        }
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

        if (!isBtCapable) {
            toast(this, "BT is NOT supported");
            return
        }

        registerReceiver(receiver, IntentFilter(BluetoothDevice.ACTION_FOUND))


        if (!isBtEnabled) {
            enableBt();
        } else {
            findDevice()
        }
    }

    override fun onDestroy() {
        super.onDestroy()

        // Don't forget to unregister the ACTION_FOUND receiver.
        unregisterReceiver(receiver)
    }

    private fun findDevice() {
        if (gotPermissions()) {
            val ret = btAdapter!!.startDiscovery()
            Log.i(TAG, "startDiscovery: $ret")
        }
    }

    private fun gotPermissions(): Boolean {
        val version = Build.VERSION.SDK_INT
        Log.i(TAG, "SDK version $version")

        if (version >= Build.VERSION_CODES.S) {
            val gotScan = gotPermission(
                this, Manifest.permission.BLUETOOTH_SCAN
            )

            Log.i(TAG, "BLUETOOTH_SCAN: $gotScan")

            val gotConnect = gotPermission(
                this, Manifest.permission.BLUETOOTH_CONNECT
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
                this, Manifest.permission.ACCESS_FINE_LOCATION
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
                    toast(this, "BT is disabled");
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
                toast(this, "The permission is required")
            }
        }
    }
}