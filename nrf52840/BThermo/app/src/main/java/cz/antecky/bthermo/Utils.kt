package cz.antecky.bthermo

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.widget.Toast
import androidx.core.content.ContextCompat
import java.nio.ByteBuffer
import java.nio.ByteOrder

object Utils {
    fun Context.toast(text: CharSequence) {
        Toast.makeText(this, text, Toast.LENGTH_LONG).show();
    }

    fun Context.gotPermission(permission: String): Boolean {
        return ContextCompat.checkSelfPermission(
            this,
            permission
        ) == PackageManager.PERMISSION_GRANTED
    }

    fun ByteArray.toHexString(): String =
        joinToString(separator = " ") { String.format("%02X", it) }

    fun ByteArray.toTemperature(): Float {
        if (this.count() != 4) {
            throw IllegalArgumentException("4 bytes required")
        }

        return ByteBuffer.wrap(this).order(ByteOrder.LITTLE_ENDIAN).int / 100.0f
    }
}