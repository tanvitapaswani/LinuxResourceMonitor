# Linux Resource Monitor

## 1. Project Overview

Linux Resource Monitor is a C++ based Linux system monitoring application that collects and displays important system resource information in real time.

The application monitors:

- CPU usage
- Memory usage
- Disk usage
- Running processes
- Linux system information

It also performs threshold-based anomaly detection and identifies abnormal resource usage.

The collected information is presented through a locally hosted monitoring dashboard.

---

## 2. Problem Statement

High CPU, memory, or disk utilization can affect system performance and may indicate an abnormal process or system condition.

Linux provides several system interfaces for accessing system and resource information, but this information is normally available in different locations.

This project provides a simple monitoring application that collects important Linux resource information, analyzes it, detects abnormal usage, and presents the results in a single dashboard.

---

## 3. Objectives

The main objectives of the project are:

- Monitor CPU utilization.
- Monitor memory utilization.
- Monitor disk utilization.
- Count active Linux processes.
- Collect basic Linux system information.
- Detect abnormal resource usage using predefined thresholds.
- Display monitoring information through a local dashboard.
- Demonstrate Linux system programming concepts using C++.

---

## 4. Technologies Used

### Programming Language
- C++

### Operating System
- Linux / Ubuntu

### Linux Concepts
- `/proc` filesystem
- Linux system information
- Linux system calls
- TCP sockets
- File handling
- Directory handling
- `statvfs`
- `uname`

### Development Tools
- GCC / G++
- Visual Studio Code
- Git
- GitHub

---

## 5. System Architecture

The application follows a modular monitoring architecture.

```text
             Linux Operating System
                       |
                       v
              Resource Collector
                       |
        +--------------+--------------+
        |              |              |
        v              v              v
       CPU          Memory          Disk
        |              |              |
        +--------------+--------------+
                       |
                       v
               Process Monitor
                       |
                       v
                Resource Analyzer
                       |
                       v
               Anomaly Detector
                       |
                       v
                 C++ Web Server
                       |
                       v
             Monitoring Dashboard

             ---
```
## 6. Main Modules

### CPU Monitoring

Reads CPU statistics from the Linux `/proc/stat` interface and calculates CPU utilization.

### Memory Monitoring

Reads memory information from `/proc/meminfo` and calculates memory usage.

### Disk Monitoring

Uses the Linux `statvfs` interface to determine disk space utilization.

### Process Monitoring

Scans the Linux `/proc` filesystem and counts active process directories.

### Anomaly Detection

Compares resource utilization against predefined thresholds.

Current thresholds include:

- CPU: 80%
- Memory: 80%
- Disk: 90%

If a threshold is exceeded, the system reports an anomaly.

### Web Server

A lightweight TCP socket server written in C++ hosts the local monitoring dashboard.

---

## 7. Dashboard

The dashboard provides a visual representation of:

- CPU usage
- Memory usage
- Disk usage
- Running processes
- Overall system health
- Recent resource alerts
- Linux kernel information
- System architecture

The dashboard automatically refreshes periodically to display updated resource values.

---

## 8. Project Structure

```text
LinuxResourceMonitor/
│
├── src/
│   ├── main.cpp
│   ├── SystemMonitor.cpp
│   └── WebServer.cpp
│
├── include/
│   ├── SystemMonitor.h
│   └── WebServer.h
│
├── docs/
│   ├── architecture.md
│   └── testing.md
│
├── README.md
│
└── monitor
```
## 9. Requirements

The following software is required:

- Linux / Ubuntu
- G++ compiler
- Git
- Web browser

## 10. Compilation

Open a terminal inside the project directory.

```bash
g++ src/main.cpp src/SystemMonitor.cpp src/WebServer.cpp -o monitor

```
## 11. Execution

Run the application:

```bash
./monitor

The server starts at:

http://localhost:8080

Open the address in a web browser to view the monitoring dashboard.

```
## 12. Anomaly Detection

The system monitors CPU, memory, and disk usage and checks them against predefined threshold values.

### Thresholds

| Resource | Threshold |
|----------|-----------|
| CPU Usage | > 80% |
| Memory Usage | > 80% |
| Disk Usage | > 90% |

If any resource exceeds its threshold, the system reports:

**ANOMALY DETECTED**

Otherwise, the system reports:

**SYSTEM NORMAL**

This provides a simple rule-based method for identifying abnormal resource usage.

## 13. Linux System Programming Concepts

The project demonstrates the following Linux system programming concepts:

- Reading CPU information from `/proc/stat`
- Reading memory information from `/proc/meminfo`
- Monitoring running processes using the `/proc` directory
- Monitoring disk usage using Linux system calls
- Using TCP sockets for client-server communication
- Using C++ file streams for reading system information
- Using Linux directory handling APIs
- Using `uname()` to obtain Linux kernel and system architecture information
- Working with Linux kernel-provided interfaces from user space

These concepts allow the C++ application to collect and display real-time system resource information.

## 14. Future Enhancements

The project can be enhanced with the following features:

- Per-process CPU and memory monitoring
- Displaying process IDs and process names
- Historical resource usage graphs
- Configurable resource thresholds
- Alert logging and notification system
- Monitoring additional system resources
- Advanced anomaly detection techniques

## 15. Conclusion

The Linux Resource Monitor is a C++ based system monitoring application developed for Linux.

It demonstrates Linux system programming, resource monitoring, TCP socket communication, system information collection, and rule-based anomaly detection.

The project provides a simple web-based dashboard for viewing system resource usage and identifying abnormal resource conditions.
