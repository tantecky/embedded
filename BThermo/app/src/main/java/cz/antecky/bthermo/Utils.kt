package cz.antecky.bthermo

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.widget.Toast
import androidx.core.content.ContextCompat

object Utils {
    fun toast(context: Context, text: CharSequence) {
        Toast.makeText(context, text, Toast.LENGTH_LONG).show();
    }

    fun gotPermission(context: Context, permission: String): Boolean {
        return ContextCompat.checkSelfPermission(
            context,
            permission
        ) == PackageManager.PERMISSION_GRANTED
    }
}