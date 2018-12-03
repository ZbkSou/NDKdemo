package com.billionstech.grassbook.util;

import android.content.Context;

/**
 * User: bkzhou
 * Date: 2018/12/2
 * Description:encryptByPubKey
 */
public class EncryptUtil {
    public static  native String getGrassEncryptStr(Context context,String data);

    public static  native String getithdrawEncryptStr(Context context,String data);
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}
