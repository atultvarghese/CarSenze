
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

#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/sysinfo.h>


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
Java_com_randstad_carsenze_CarSenzeService_getNetworkStats(JNIEnv *env, jclass clazz,jstring interfaceName) {
   // _jstring *interfaceName = (_jstring *) "wlan0";
    const char *interface = env->GetStringUTFChars(interfaceName, nullptr);
    std::ifstream rxFile, txFile;
    std::string rxPath = "/sys/class/net/" + std::string(interface) + "/statistics/rx_bytes";
    std::string txPath = "/sys/class/net/" + std::string(interface) + "/statistics/tx_bytes";
    long long rxBytesStart = 0, txBytesStart = 0;
    long long rxBytesEnd = 0, txBytesEnd = 0;

    //  function to read bytes from a file
    auto readBytes = [&](const std::string &path, long long &bytes) -> bool {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error opening " << path << std::endl;
            return false;
        }
        file >> bytes;
        file.close();
        return true;
    };

    // Get initial byte counts
    if (!readBytes(rxPath, rxBytesStart) || !readBytes(txPath, txBytesStart)) {
        std::string error = "Error reading initial network bytes for interface " + std::string(interface);
        env->ReleaseStringUTFChars(interfaceName, interface);
        return env->NewStringUTF(error.c_str());
    }

    // Wait for 1 second
    sleep(1);

    // Get byte counts after 1 second
    if (!readBytes(rxPath, rxBytesEnd) || !readBytes(txPath, txBytesEnd)) {
        std::string error = "Error reading final network bytes for interface " + std::string(interface);
        env->ReleaseStringUTFChars(interfaceName, interface);
        return env->NewStringUTF(error.c_str());
    }

    // Calculate speed in bytes per second
    long long rxSpeed = rxBytesEnd - rxBytesStart;
    long long txSpeed = txBytesEnd - txBytesStart;

    // Construct the output string with network speed information
    std::ostringstream output;
    output << "RX Speed: " << rxSpeed << " bytes/sec\n"
           << "TX Speed: " << txSpeed << " bytes/sec";
    std::string networkSpeed = output.str();

    env->ReleaseStringUTFChars(interfaceName, interface);
    return env->NewStringUTF(networkSpeed.c_str());
}


