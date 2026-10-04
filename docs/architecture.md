# System Architecture

## 1. Architecture Overview

The Linux Resource Monitor follows a modular software architecture.

The application runs on Linux and uses C++ to collect system resource information. The collected information is analyzed using predefined thresholds and displayed through a local web dashboard.

## 2. High-Level Architecture

```text
+---------------------------+
|    Linux Operating System |
+-------------+-------------+
              |
              v
+---------------------------+
|   System Resource Monitor |
|           (C++)           |
+-------------+-------------+
              |
       +------+------+
       |      |      |
       v      v      v
     CPU    Memory   Disk
       |      |      |
       +------+------+
              |
              v
+---------------------------+
|    Process Monitoring     |
|          /proc            |
+-------------+-------------+
              |
              v
+---------------------------+
|   Resource Analysis       |
|   & Threshold Checking    |
+-------------+-------------+
              |
              v
+---------------------------+
|       C++ Web Server      |
|       TCP Socket          |
+-------------+-------------+
              |
              v
+---------------------------+
|    Monitoring Dashboard   |
|       Web Browser         |
+---------------------------+

## 3. Main Components

### 3.1 Main Application

The `main.cpp` file is the entry point of the application.

It starts the web server by calling the `startWebServer()` function.

### 3.2 System Monitor

The System Monitor collects system resource information.

It collects:

- CPU usage
- Memory usage
- Disk usage
- Number of running processes

The collected values are stored in the `SystemData` structure.

### 3.3 Linux System Interfaces

The application uses Linux-provided interfaces to obtain system information.

| Interface | Purpose |
|-----------|---------|
| `/proc/stat` | CPU information |
| `/proc/meminfo` | Memory information |
| `/proc/` | Process information |
| `statvfs()` | Disk usage |
| `uname()` | Kernel and architecture information |

## 4. Data Flow

The data flows through the system in the following sequence:

```text
Linux System
     |
     v
System Information
     |
     v
SystemMonitor
     |
     v
SystemData
     |
     v
Threshold Checking
     |
     +----------> System Normal
     |
     +----------> Anomaly Detected
     |
     v
C++ Web Server
     |
     v
Web Browser
     |
     v
Monitoring Dashboard

## 5. Module Structure

The project is divided into multiple source and header files. Each file has a specific responsibility.

```text
LinuxResourceMonitor
|
+-- src/
|   |
|   +-- main.cpp
|   |     |
|   |     +-- Starts Web Server
|   |
|   +-- SystemMonitor.cpp
|   |     |
|   |     +-- CPU Monitoring
|   |     +-- Memory Monitoring
|   |     +-- Disk Monitoring
|   |     +-- Process Monitoring
|   |
|   +-- WebServer.cpp
|         |
|         +-- TCP Socket Server
|         +-- HTTP Response
|         +-- Threshold Checking
|         +-- Dashboard Generation
|
+-- include/
    |
    +-- SystemMonitor.h
    |     |
    |     +-- SystemData Structure
    |
    +-- WebServer.h
          |
          +-- Web Server Declaration

## 6. Runtime Architecture

The application runs completely on a Linux operating system.

```text
+----------------------+
|   Linux Environment  |
+----------+-----------+
           |
           v
+----------------------+
|   C++ Application    |
|      monitor         |
+----------+-----------+
           |
           v
+----------------------+
|     TCP Port 8080    |
+----------+-----------+
           |
           v
+----------------------+
|     Web Browser      |
|    localhost:8080    |
+----------------------+

## 7. Design Approach

The project follows a modular design approach where different functionalities are divided into separate source and header files.

The design focuses on:

- Simple and clear implementation
- Separation of system monitoring and web server functionality
- Easy maintenance and modification
- Linux-based system interaction
- Real-time resource monitoring
- Rule-based anomaly detection
- Efficient communication using TCP sockets

This modular approach makes the project easier to understand, test, and demonstrate.

## 8. Linux Architecture Concepts

The project works as a user-space application running on top of the Linux operating system.

```text
+--------------------------------+
|       Monitoring Dashboard     |
+--------------------------------+
|        C++ Web Server          |
+--------------------------------+
|        System Monitor          |
+--------------------------------+
| Linux Kernel Interfaces / APIs |
+--------------------------------+
|       Linux Operating System   |
+--------------------------------+
|            Hardware            |
+--------------------------------+

## 9. Device Driver Relevance

The project does not implement a custom Linux kernel device driver.

Instead, it uses Linux kernel-provided interfaces such as the `/proc` filesystem and system APIs from user space to obtain system information.

This demonstrates how a user-space C++ application can interact with information provided by the Linux operating system.

The project can be extended in the future to include a custom device driver for collecting additional system-level information.

## 10. Sequence of Operation

The application follows the following sequence when a user accesses the monitoring dashboard.

```text
User
 |
 | Opens localhost:8080
 v
Web Browser
 |
 | HTTP Request
 v
C++ Web Server
 |
 | Request System Data
 v
System Monitor
 |
 | Read Linux Interfaces
 v
Linux Operating System
 |
 | CPU / Memory / Disk / Process Data
 v
System Monitor
 |
 | Return SystemData
 v
C++ Web Server
 |
 | Check Thresholds
 v
Generate Dashboard
 |
 | HTTP Response
 v
Web Browser
 |
 v
Display Monitoring Dashboard

## 11. Conclusion

The architecture combines Linux system programming, C++ resource monitoring, TCP socket communication, and rule-based anomaly detection.

The modular structure separates system monitoring from web server functionality, making the project easier to understand, maintain, and demonstrate.

The project provides a simple way to monitor Linux system resources and identify abnormal resource usage through a local monitoring dashboard.