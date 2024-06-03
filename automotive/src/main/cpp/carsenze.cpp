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
#include <fstream>
#include <sstream>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <iostream>

void readCpuTimes(long long int &idleTime, long long int &totalTime) {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);

    std::istringstream iss(line);
    std::string cpu;
    long long int user, nice, system, idle, iowait, irq, softirq, steal;
    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    idleTime = idle + iowait;
    totalTime = user + nice + system + idle + iowait + irq + softirq + steal;
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_CarSenzeService_memoryInfo(JNIEnv *env, jclass clazz) {
    struct sysinfo memInfo;
    sysinfo(&memInfo);

    // Calculate total physical memory in bytes
    long long int totalPhysMem = memInfo.totalram;
    totalPhysMem *= memInfo.mem_unit;

    // Calculate free physical memory in bytes
    long long int freePhysMem = memInfo.freeram;
    freePhysMem *= memInfo.mem_unit;

    // Calculate used physical memory in bytes
    long long int usedPhysMem = totalPhysMem - freePhysMem;

    // Convert memory values to megabytes and format the output string
    std::ostringstream oss;
    oss << "Total RAM: " << (totalPhysMem / (1024 * 1024)) << " MB\n"
        << "Free RAM: " << (freePhysMem / (1024 * 1024)) << " MB\n"
        << "Used RAM: " << (usedPhysMem / (1024 * 1024)) << " MB";
    return env->NewStringUTF(oss.str().c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_CarSenzeService_cpuInfo(JNIEnv *env, jclass clazz) {

    long long int idleTime1, totalTime1;
    readCpuTimes(idleTime1, totalTime1);

    // Sleep for a more precise interval (consider using clock_gettime)
    usleep(100000);

    long long int idleTime2, totalTime2;
    readCpuTimes(idleTime2, totalTime2);

    long long int deltaIdle = idleTime2 - idleTime1;
    long long int deltaTotal = totalTime2 - totalTime1;
    double cpuUsage = (100.0 * (deltaTotal - deltaIdle)) / deltaTotal;

    std::ostringstream oss;
    oss << "CPU " << cpuUsage << "%";
   // std::cout<<oss.str();
    return env->NewStringUTF(oss.str().c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_randstad_carsenze_CarSenzeService_networkStat(JNIEnv *env, jclass clazz) {
    std::string hello = "N/W 20mbps";
    return env->NewStringUTF(hello.c_str());
}


