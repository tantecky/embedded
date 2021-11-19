package cz.antecky.bthermo

import android.Manifest
import android.animation.ArgbEvaluator
import android.bluetooth.*
import android.bluetooth.le.ScanSettings
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View.GONE
import android.view.View.VISIBLE
import android.widget.Button
import android.widget.TextView
import androidx.lifecycle.ViewModelProvider
import cz.antecky.bthermo.Utils.gotPermission
import cz.antecky.bthermo.Utils.toast
import java.util.*
import android.view.animation.Animation

import android.animation.ObjectAnimator
import android.animation.ValueAnimator
import android.graphics.Color
import androidx.core.content.res.ResourcesCompat


class MainActivity : AppCompatActivity() {
    private val TAG = "MainActivity"
    private val BLUETOOTH_TURN_ON_CODE = 21
    private val PERMISSION_REQUEST = 21

    private lateinit var viewModel: ThermoViewModel

    private val scanSettings = ScanSettings.Builder()
        .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
        .build()

    private val btAdapter: BluetoothAdapter? by lazy {
        val bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothManager.adapter
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

        viewModel = ViewModelProvider(this)[ThermoViewModel::class.java]

        val buttonStartStop = findViewById<Button>(R.id.button_start)
        buttonStartStop.setOnClickListener {
            btAdapter?.let { btAdapter ->
                if (viewModel.isRunning.value!!) {
                    viewModel.onStopClicked()
                } else {
                    viewModel.onStartClicked(btAdapter)
                }
            }
        }


        val textViewTemperature = findViewById<TextView>(R.id.tv_temperature)
        val anim = ObjectAnimator.ofInt(
            textViewTemperature,
            "textColor",
            Color.WHITE,
            ResourcesCompat.getColor(resources, R.color.purple_200, null),
            Color.WHITE
        )
        anim.duration = 150
        anim.setEvaluator(ArgbEvaluator())
        anim.repeatCount = 0

        viewModel.temperature.observeForever { temperature ->
            textViewTemperature.text = "%.2f°C".format(temperature)

            anim.start()
        }

        viewModel.isRunning.observeForever { isRunning ->
            if (isRunning) {
                buttonStartStop.text = "STOP"

            } else {
                buttonStartStop.text = "START"
            }
        }

    }

    override fun onResume() {
        super.onResume()
        Log.i(TAG, "onResume")
        prepareBt()
    }

    private fun prepareBt() {
        if (!isBtCapable) {
            toast("BT is NOT supported");
            return
        }

        requestPermissions()

        if (!isBtEnabled) {
            enableBt();
        }
    }

    private fun requestPermissions(): Boolean {
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
                    toast("BT is disabled");
                    prepareBt()
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
            } else {
                toast("The permission is required for BT")
                prepareBt()
            }
        }
    }
}