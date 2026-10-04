#include "../include/SystemMonitor.h"

#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <dirent.h>
#include <sys/statvfs.h>
#include <unistd.h>

// ---------------- CPU USAGE ----------------

double readCpuUsage() {
    std::ifstream file("/proc/stat");

    if (!file.is_open())
        return 0.0;

    std::string cpu;
    long long user, nice, system, idle;
    long long iowait, irq, softirq, steal;

    file >> cpu
         >> user
         >> nice
         >> system
         >> idle
         >> iowait
         >> irq
         >> softirq
         >> steal;

    long long idleTime = idle + iowait;

    long long totalTime =
        user + nice + system + idle +
        iowait + irq + softirq + steal;

    static long long previousIdle = 0;
    static long long previousTotal = 0;

    if (previousTotal == 0) {
        previousIdle = idleTime;
        previousTotal = totalTime;

        usleep(100000);

        return readCpuUsage();
    }

    long long idleDifference =
        idleTime - previousIdle;

    long long totalDifference =
        totalTime - previousTotal;

    previousIdle = idleTime;
    previousTotal = totalTime;

    if (totalDifference <= 0)
        return 0.0;

    double usage =
        (1.0 -
         (double)idleDifference /
         totalDifference) * 100.0;

    if (usage < 0)
        usage = 0;

    if (usage > 100)
        usage = 100;

    return usage;
}


// ---------------- MEMORY USAGE ----------------

double getMemoryUsage() {

    std::ifstream file("/proc/meminfo");

    if (!file.is_open())
        return 0.0;

    std::string name;
    long long value;
    std::string unit;

    long long totalMemory = 0;
    long long availableMemory = 0;

    while (file >> name >> value >> unit) {

        if (name == "MemTotal:")
            totalMemory = value;

        if (name == "MemAvailable:")
            availableMemory = value;
    }

    if (totalMemory == 0)
        return 0.0;

    double usedMemory =
        totalMemory - availableMemory;

    return (usedMemory / totalMemory) * 100.0;
}


// ---------------- DISK USAGE ----------------

double getDiskUsage() {

    struct statvfs disk;

    if (statvfs("/", &disk) != 0)
        return 0.0;

    unsigned long long totalSpace =
        (unsigned long long)disk.f_blocks *
        disk.f_frsize;

    unsigned long long freeSpace =
        (unsigned long long)disk.f_bfree *
        disk.f_frsize;

    if (totalSpace == 0)
        return 0.0;

    unsigned long long usedSpace =
        totalSpace - freeSpace;

    return ((double)usedSpace /
            totalSpace) * 100.0;
}


// ---------------- PROCESS COUNT ----------------

int getProcessCount() {

    DIR* directory = opendir("/proc");

    if (directory == nullptr)
        return 0;

    int count = 0;

    struct dirent* entry;

    while ((entry = readdir(directory)) != nullptr) {

        std::string name = entry->d_name;

        if (!name.empty() &&
            std::all_of(
                name.begin(),
                name.end(),
                [](unsigned char character) {
                    return std::isdigit(character);
                })) {

            count++;
        }
    }

    closedir(directory);

    return count;
}


// ---------------- MAIN SYSTEM DATA ----------------

SystemData getSystemData() {

    SystemData data;

    data.cpuUsage = readCpuUsage();
    data.memoryUsage = getMemoryUsage();
    data.diskUsage = getDiskUsage();
    data.processCount = getProcessCount();

    return data;
}