#include <jni.h>
#include <stdlib.h>
#include <string>
#include <string.h>

static jclass contextClass;
static jclass signatureClass;
static jclass packageNameClass;
static jclass packageInfoClass;

#include <android/log.h>

#include "MD5.h"
#ifndef LOG_TAG
#define LOG_TAG "HELLO_JNI"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) // 定义LOGF类型
#endif
const char * keyti = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA+erZj3EmG+FHdOcCGt1JJqpoz7ZPzDGB1ZvmMAMtbGF8RRRwNfglA6no/kF3ZYGmsP+ykT4LzbKdFX0xOUptuKaFm7eHRhYwSQbF7s+QrsD5g+hSmh/Ylpk4jJJvCd1vGGSxlr6tn50zHRZTX0QJt2zp0AymvjpMemwd70VWwpAOtX2tZ7rrLuwV+vgq+xuhMFe9KURedVKGflka8p7dDmhzHqa62EAr6McrGFtOhhYBIIMCafo53Mzp0Dv4DINSfDd6bfu9OJyu5U4ZswNgXyciro2fgK3/PnF7HRcMSGkl85B3kh1TPQI8TevY4f6jb+ovA+hCG/9MrE+T/CABbQIDAQAB";

const char * keycao = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvrJqCtVW/+hSP35w5oNej7UI/CEQiAteusp+5EkrE8qaNRsZ8ikx+UDzYwPM9Eo8IsZxxAHKiKqh6J925nCYoGOs3nZ4IJTk7KQm0gFk957CTRPBm8ofugdrp6XXJFPmz9pxhwYotPczSVCRkJ2n8P3BCAjBGq300WNRdHPHVG5Sc/MMZggFDMpbtZRT1MN7ve+Wq1vnXEpZoon0o3/XmQ8KuHufZgS6ZwnuOjrVDfe5qj0uFGQzIaAXaUm+fCgGKs7kAkd0HwWp7po7fcMr26g0GJWISLuVU6RXhi73oRTxqLS430gVLrxfz2+Fq3d8Du61gk59bE3VRMKrAHWKbQIDAQAB";
const char *app_signature = "308203753082025da003020102020429fb40f9300d06092a864886f70d01010b0500306a310b300906035504061302434e3110300e060355040813074265694a696e673110300e060355040713074265694a696e67310c300a060355040a1303636f6d31153013060355040b130c62696c6c696f6e737465636831123010060355040313096772617373626f6f6b3020170d3138303732373037303531335a180f32313138303730333037303531335a306a310b300906035504061302434e3110300e060355040813074265694a696e673110300e060355040713074265694a696e67310c300a060355040a1303636f6d31153013060355040b130c62696c6c696f6e737465636831123010060355040313096772617373626f6f6b30820122300d06092a864886f70d01010105000382010f003082010a028201010098110918143b5e796b66289c9e0bba05c6a18be7a12333ab9bf926f982f12d1b1d08d8898ed028ec00fdebc8c4a9c8aabf20c16f2c9e1861b97f5b2a6d286779580c12cbeb42ba1a41cd16869d8a6b4e93201fa68fe72f0a7473bc1bc7e47781d095efa41cc09dc9871f8073175c9b365d9fb2257eda4df7b3f61363c70f3fe802ba7d9986fee273e3dfbd448592ff5b92994142a32d4ea525dd30b2f7484be5dbe557de1e5d4377367d5fb43502cb9190d7b6ebef372662f550d2481234aa2771de5aba0c31f1631d1bb0330e79b5fd8dd732f7c98aff5d283150748a0371077092d19ecaa17d52f4ebc9d661a7882459a062c20def560712c3ec096a3873610203010001a321301f301d0603551d0e0416041469fc97ae3465b14f3a00901d48abf90943259c0f300d06092a864886f70d01010b0500038201010048dac48ac1c53cd09b0a79bb85bdff3e28b14adfa0a72f02218916cdc1b5074956e8ad0af707f0e7014f28d57f39dcbddd5a45b9181c437b7d6af6a9759ef168359c9a75cc370a791463dcbb1dc8d756b16c64e08b7c73d3a4622a2be747117bc3f50b177feb8b04a047dc532a6703ce3a6fcabdea54c759bbe5c59bf7ae131f084eed36d9bc42d59e7130ef37a211c2f3898cbc82d2496ccab67fa25c6b35d608295cce4c0c06a7de51a6f52934f2c0afb43775794a0abf5c315af9397df4359ae42d50dd923217ba9b813dd6ab886b98711261cf44860cabf72c91a02c734e0e71d27887d11634cd2ab4500c51931db3758ab4584fb36d3e13c92fffe63550";

static bool is_valid = false;

const void  getSignString(JNIEnv *env, jobject context_object) {

    jclass context_class = env->GetObjectClass(context_object);

    //context.getPackageManager()
    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager",
                                          "()Landroid/content/pm/PackageManager;");
    jobject package_manager_object = env->CallObjectMethod(context_object, methodId);
    if (package_manager_object == NULL) {
        LOGE("getPackageManager() Failed!");
        return ;
    }

    //context.getPackageName()
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name_string = (jstring) env->CallObjectMethod(context_object, methodId);
    if (package_name_string == NULL) {
        LOGE("getPackageName() Failed!");
        return ;
    }
    env->DeleteLocalRef(context_class);

    //PackageManager.getPackageInfo(Sting, int)
    //public static final int GET_SIGNATURES= 0x00000040;
    jclass pack_manager_class = env->GetObjectClass(package_manager_object);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo",
                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    env->DeleteLocalRef(pack_manager_class);
    jobject package_info_object = env->CallObjectMethod(package_manager_object, methodId,
                                                        package_name_string, 0x40);
    if (package_info_object == NULL) {
        LOGE("getPackageInfo() Failed!");
        return ;
    }
    env->DeleteLocalRef(package_manager_object);

    //PackageInfo.signatures[0]
    jclass package_info_class = env->GetObjectClass(package_info_object);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures",
                                       "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(package_info_class);
    jobjectArray signature_object_array = (jobjectArray) env->GetObjectField(package_info_object,
                                                                             fieldId);
    if (signature_object_array == NULL) {
        LOGE("PackageInfo.signatures[] is null");
        return ;
    }
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
    env->DeleteLocalRef(package_info_object);

    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toCharsString", "()Ljava/lang/String;");
    env->DeleteLocalRef(signature_class);
    jstring signature_jstirng = (jstring) env->CallObjectMethod(signature_object, methodId);

    const char *sign = env->GetStringUTFChars(signature_jstirng, NULL);

//    LOGD("sign = %s", sign);

    if (strcmp(sign, app_signature) == 0) {
//        LOGE("验证通过");
        is_valid = true;
    }

    return ;
}
/**
 * 生成 JAVA 的 HashCode 码
 *
 * @param value char[] ，字符串指针
 * @return
 */
int hashCode(const char* value) {
    int hash = 0;
    int h = hash;
    if (h == 0 && strlen(value) > 0) {
        for (int i = 0; i < strlen(value); ++i) {
            h = 31 * h + value[i];
        }
        hash = h;
    }
    return h;
}

/**
 * 获取字符串截取后的字符串
 *
 * @param value 原始字符串
 * @param is_front 标识是否从前、后截取
 * @param num 截取几位
 * @return
 */
char* substring(const std::string value, bool is_front, int num) {
    if (is_front) {
        return (char *) value.substr(0, num).c_str();
    } else {
        return (char *) value.substr(value.length() - num, value.length() - 1).c_str();
    }
}
void LOG(JNIEnv *env, const char *info) {
    jclass LogUtils = env->FindClass("com/billionstech/grassbook/util/LogUtils");
//    LOGD("LogUtils = %s", LogUtils);
    if (LogUtils == NULL) {
        LOGE("LogUtils is NULL!");
        return;
    }
    jmethodID logMethod = env->GetStaticMethodID(LogUtils, "debug", "(Ljava/lang/String;)V");
    if (logMethod == NULL) {
        LOGE("logMethod is NULL!");
        return;
    }
    env->CallStaticVoidMethod(LogUtils, logMethod, env->NewStringUTF(info));
}
jstring encryptByPubKey(JNIEnv *env, jstring info,const char *key) {
    jclass RSAUtils = env->FindClass("com/billionstech/grassbook/util/security/RSAUtils");
    if (RSAUtils == NULL) {
        LOGE("LogUtils is NULL!");
        return (jstring)"";
    }
    jmethodID encryptMethod = env->GetStaticMethodID(RSAUtils, "encryptByPubKey", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    if (encryptMethod == NULL) {
        LOGE("logMethod is NULL!");
        return (jstring)"";
    }
    jstring result = (jstring) env->CallStaticObjectMethod(RSAUtils, encryptMethod, info,env->NewStringUTF(key));
    env->DeleteLocalRef(RSAUtils);
    return result;
}

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jstring JNICALL
Java_com_billionstech_grassbook_util_EncryptUtil_getGrassEncryptStr(JNIEnv *env, jclass type,
                                                                    jobject context,jstring data_) {
    getSignString(env, context);
    jstring serct = env->NewStringUTF("");
    if(is_valid){
        serct = encryptByPubKey(env, data_,keycao);
    }

    return serct;

}
JNIEXPORT jstring JNICALL
Java_com_billionstech_grassbook_util_EncryptUtil_getithdrawEncryptStr(JNIEnv *env, jclass type,
                                                                      jobject context,jstring data_) {

    std::string str = "grape";
    MD5 md5 = MD5(str);
    std::string hashStr = md5.hexdigest();

    LOGD("encrypt = %s", hashStr.c_str());
    getSignString(env, context);
    jstring serct = env->NewStringUTF("");
    if(is_valid){
        serct = encryptByPubKey(env, data_,keyti);
    }
    return serct;
}
#ifdef __cplusplus
}
#endif

