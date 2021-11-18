package cz.antecky.bthermo

import android.bluetooth.*
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.bluetooth.le.ScanSettings
import android.util.Log
import androidx.lifecycle.MutableLiveData
import cz.antecky.bthermo.Utils.toHexString
import cz.antecky.bthermo.Utils.toTemperature
import java.util.*

object ThermoRepository {
    private val TAG = "ThermoRepository"

    private lateinit var btAdapter: BluetoothAdapter

    private val DEVICE_NAME = "BThermo"

    private val TEMPERATURE_CHARACTERISTIC = UUID.fromString("00002a6e-0000-1000-8000-00805f9b34fb")
    private val TEMPERATURE_CCCD = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb")

    private val scanSettings = ScanSettings.Builder()
        .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
        .build()

    private var _isConnected = MutableLiveData<Boolean>(false)
    private var _isScanning = MutableLiveData<Boolean>(false)
    private var _temperature = MutableLiveData<Float>(Float.NaN)

    private val scanCallback = object : ScanCallback() {
        override fun onScanResult(callbackType: Int, result: ScanResult?) {
            super.onScanResult(callbackType, result)

            result?.let {
                val device = it.device
                val name = device.name

                if (name == DEVICE_NAME) {
                    stopScan()
                    connect(device)
                }

                Log.i(TAG, name)
            }
        }

        override fun onScanFailed(errorCode: Int) {
            super.onScanFailed(errorCode)
            stopScan()
        }
    }

    private val gattCallback = object : BluetoothGattCallback() {
        override fun onConnectionStateChange(gatt: BluetoothGatt?, status: Int, newState: Int) {
            super.onConnectionStateChange(gatt, status, newState)

            when (newState) {
                BluetoothProfile.STATE_CONNECTED -> {
                    _isConnected.postValue(true)
                    Log.i(TAG, "GATT STATE_CONNECTED")

                    gatt?.discoverServices().let { ok ->
                        Log.i(TAG, "discoverServices ok: $ok")
                    }

                }
                BluetoothProfile.STATE_DISCONNECTED -> {
                    _isConnected.postValue(false)
                    Log.i(TAG, "GATT STATE_DISCONNECTED")
                }
            }
        }

        override fun onCharacteristicChanged(
            gatt: BluetoothGatt?,
            characteristic: BluetoothGattCharacteristic?
        ) {
            super.onCharacteristicChanged(gatt, characteristic)

            characteristic?.let {
                with(it) {
                    val temperature = value.toTemperature()
                    _temperature.postValue(temperature)

                    Log.i(
                        TAG,
                        "Characteristic $uuid changed | value: $temperature (${value.toHexString()})"
                    )
                }
            }
        }

        override fun onServicesDiscovered(gatt: BluetoothGatt?, status: Int) {
            super.onServicesDiscovered(gatt, status)
            Log.i(TAG, "onServicesDiscovered")
            gatt?.let {
                enableNotification(it)
            }
        }
    }

    private fun enableNotification(gatt: BluetoothGatt) {
        for (service in gatt.services) {
            for (characteristic in service.characteristics) {
                val uuid = characteristic.uuid

                if (uuid == TEMPERATURE_CHARACTERISTIC) {
                    val okChar = gatt.setCharacteristicNotification(characteristic, true)
                    Log.i(TAG, "setCharacteristicNotification: $okChar")

                    if (okChar) {
                        val descriptor = characteristic.getDescriptor(TEMPERATURE_CCCD)
                        descriptor.value = BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE
                        val okDesc = gatt.writeDescriptor(descriptor)
                        Log.i(TAG, "writeDescriptor: $okDesc")

                        if (okDesc) {
                            return
                        }
                    }
                }
            }
        }

        Log.e(TAG, "enableNotification failed")
    }

    private val btScanner by lazy {
        btAdapter.bluetoothLeScanner
    }

    private fun connect(device: BluetoothDevice) {
        device.connectGatt(null, false, gattCallback)
    }

    private fun stopScan() {
        _isScanning.postValue(false)
        btScanner.stopScan(scanCallback)
    }

    fun start(btAdapter: BluetoothAdapter) {
        this.btAdapter = btAdapter

        if (!_isScanning.value!!) {
            _isScanning.value = true
            Log.i(TAG, "startScan")
            btScanner.startScan(null, scanSettings, scanCallback)
        }
    }

}