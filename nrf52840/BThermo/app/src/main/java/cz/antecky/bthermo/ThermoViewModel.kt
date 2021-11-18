package cz.antecky.bthermo

import android.bluetooth.BluetoothAdapter
import android.util.Log
import androidx.lifecycle.ViewModel


class ThermoViewModel : ViewModel() {
    private val TAG = "ThermoViewModel"

    fun onStartClicked(btAdapter: BluetoothAdapter) {
        Log.i(TAG, btAdapter.toString())
        ThermoRepository.start(btAdapter)
    }
}