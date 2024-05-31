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


extern "C"
JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_CarSenzeService_memoryInfo(JNIEnv *env, jclass clazz) {
    std::string hello = "MEM 54GB";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_CarSenzeService_cpuInfo(JNIEnv *env, jclass clazz) {
    std::string hello = "CPU 50%";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_CarSenzeService_networkStat(JNIEnv *env, jclass clazz) {
    std::string hello = "N/W 20mbps";
    return env->NewStringUTF(hello.c_str());
}