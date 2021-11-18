package cz.antecky.bthermo

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.widget.Toast
import androidx.core.content.ContextCompat

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
}