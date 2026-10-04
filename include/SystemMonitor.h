#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

struct SystemData {
    double cpuUsage;
    double memoryUsage;
    double diskUsage;
    int processCount;
};

SystemData getSystemData();

#endif