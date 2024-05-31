// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("carsenze");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("carsenze")
//      }
//    }
#include <jni.h>
#include <string>

extern "C" {
    JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_MainActivity_memoryInfo(JNIEnv* env,jobject /* this */) {
    std::string hello = "MEM 54GB";
    return env->NewStringUTF(hello.c_str());
}
 JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_MainActivity_cpuInfo(JNIEnv* env,jobject /* this */) {
    std::string hello = "CPU 92%";
    return env->NewStringUTF(hello.c_str());
}
 JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_MainActivity_networkStat(JNIEnv* env,jobject /* this */) {
    std::string hello = "10 Mb/s";
    return env->NewStringUTF(hello.c_str());
}
}