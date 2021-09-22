package org.qtproject.qt5.android.bindings;

import android.content.BroadcastReceiver;
import android.util.Log;
import android.content.Context;
import android.content.Intent;
import android.os.PowerManager;
import android.os.BatteryManager;
import android.app.KeyguardManager;
import android.app.KeyguardManager.KeyguardLock;

public class StartService extends BroadcastReceiver {
    static final String action_boot="android.intent.action.BOOT_COMPLETED";
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d("izar", intent.getAction());
        if(intent.getAction().equals(action_boot)) {
            PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
            mWakeLock = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, "My Tag");
            mWakeLock.acquire();
            if(kl == null) {
                KeyguardManager km = (KeyguardManager) context.getSystemService(Context.KEYGUARD_SERVICE);
                kl = km.newKeyguardLock("unLock");
                kl.disableKeyguard();
            }

            hideTheBar(context);
            Intent qtApp = new Intent(context, QtActivity.class);
            qtApp.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(qtApp);
        }
    }

    public static void hideTheBar(Context context) {
        if (context == null) {
                return;
        }
        context.sendBroadcast(new Intent("hide_bar"));
    }

    private PowerManager.WakeLock mWakeLock = null;
    private KeyguardLock kl = null;

}
