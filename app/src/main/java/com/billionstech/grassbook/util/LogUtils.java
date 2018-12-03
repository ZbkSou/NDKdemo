package com.billionstech.grassbook.util;

import android.util.Log;

/**
 * <p>Title: LogUtils</p>
 * <p>Description: TODO</p>
 * <p>Company: ihaveu</p>
 *
 * @author DJ
 * @date 2018/12/1
 */
public class LogUtils {

    public static final String TAG = "TAG => ";

    public static void debug(String info) {
        System.out.println("========= " + info);
        Log.d(TAG, info);
    }

    public static void info(String info) {
        Log.i(TAG, info);
    }

    public static void warn(String info) {
        Log.w(TAG, info);
    }

    public static void error(String info) {
        Log.e(TAG, info);
    }
}
