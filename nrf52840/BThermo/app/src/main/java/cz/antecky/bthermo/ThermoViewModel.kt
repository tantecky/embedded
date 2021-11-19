package cz.antecky.bthermo

import android.bluetooth.BluetoothAdapter
import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.ViewModel


class ThermoViewModel : ViewModel() {
    private val TAG = "ThermoViewModel"

    val temperature: LiveData<Float>
        get() = ThermoRepository.temperature

    val isRunning: LiveData<Boolean>
        get() = ThermoRepository.isRunning


    fun onStartClicked(btAdapter: BluetoothAdapter) {
        ThermoRepository.start(btAdapter)
    }

    fun onStopClicked() {
        ThermoRepository.stop()
    }
}