package cz.antecky.bthermo

import android.bluetooth.*
import android.bluetooth.BluetoothGatt.GATT_SUCCESS
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.bluetooth.le.ScanSettings
import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import cz.antecky.bthermo.Utils.toHexString
import cz.antecky.bthermo.Utils.toTemperature
import java.util.*
import java.util.concurrent.atomic.AtomicBoolean

object ThermoRepository {
    private val TAG = "ThermoRepository"

    private lateinit var btAdapter: BluetoothAdapter

    private val DEVICE_NAME = "BThermo"

    private val TEMPERATURE_CHARACTERISTIC = UUID.fromString("00002a6e-0000-1000-8000-00805f9b34fb")
    private val TEMPERATURE_CCCD = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb")

    private val scanSettings = ScanSettings.Builder()
        .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
        .build()

    private val _isRunning = MutableLiveData<Boolean>(false)
    private val _rssi = MutableLiveData<Int>(0)
    private val _temperature = MutableLiveData<Float>(Float.NaN)

    private val closeRequested = AtomicBoolean(false)

    val isRunning: LiveData<Boolean>
        get() = _isRunning

    val rssi: LiveData<Int>
        get() = _rssi

    val temperature: LiveData<Float>
        get() = _temperature

    private val scanCallback = object : ScanCallback() {
        override fun onScanResult(callbackType: Int, result: ScanResult?) {
            super.onScanResult(callbackType, result)

            if (closeRequested.get()) {
                _isRunning.postValue(false)
                stopScan()
                return
            }

            result?.let {
                val device = it.device
                val name = device?.name ?: "null"

                if (name == DEVICE_NAME) {
                    stopScan()
                    connect(device)
                }

                Log.i(TAG, name)
            }
        }

        override fun onScanFailed(errorCode: Int) {
            super.onScanFailed(errorCode)
            _isRunning.postValue(false)
            stopScan()
        }
    }

    private val gattCallback = object : BluetoothGattCallback() {
        override fun onConnectionStateChange(gatt: BluetoothGatt?, status: Int, newState: Int) {
            super.onConnectionStateChange(gatt, status, newState)

            when (newState) {
                BluetoothProfile.STATE_CONNECTED -> {
                    Log.i(TAG, "GATT STATE_CONNECTED")

                    gatt?.readRemoteRssi()
                    gatt?.discoverServices().let { ok ->
                        Log.i(TAG, "discoverServices ok: $ok")
                    }

                }
                BluetoothProfile.STATE_DISCONNECTED -> {
                    _isRunning.postValue(false)
                    Log.i(TAG, "GATT STATE_DISCONNECTED")
                }
            }
        }

        override fun onReadRemoteRssi(gatt: BluetoothGatt?, rssi: Int, status: Int) {
            super.onReadRemoteRssi(gatt, rssi, status)

            if (status == GATT_SUCCESS) {
                _rssi.postValue(rssi)
            }
        }

        override fun onCharacteristicChanged(
            gatt: BluetoothGatt?,
            characteristic: BluetoothGattCharacteristic?
        ) {
            super.onCharacteristicChanged(gatt, characteristic)

            if (closeRequested.get()) {
                Log.i(TAG, "gatt?.close()")
                gatt?.close()
                return
            }

            gatt?.readRemoteRssi()

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
        Log.i(TAG, "stopScan()")
        btScanner.stopScan(scanCallback)
    }

    fun start(btAdapter: BluetoothAdapter) {
        this.btAdapter = btAdapter

        closeRequested.set(false)

        _isRunning.postValue(true)
        Log.i(TAG, "startScan")
        btScanner.startScan(null, scanSettings, scanCallback)
    }

    fun stop() {
        closeRequested.set(true)
        _isRunning.postValue(false)
    }
}