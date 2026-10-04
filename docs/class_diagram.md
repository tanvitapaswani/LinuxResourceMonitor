# Class and Module Diagram

## Linux Resource Monitor

The project uses a modular structure where each source file has a specific responsibility.

```text
+---------------------------+
|          main.cpp         |
+-------------+-------------+
              |
              | calls
              v
+---------------------------+
|      WebServer.h/.cpp     |
+-------------+-------------+
              |
              | calls
              v
+---------------------------+
|    SystemMonitor.h/.cpp   |
+-------------+-------------+
              |
              | returns
              v
+---------------------------+
|       SystemData          |
+---------------------------+
| - cpuUsage                |
| - memoryUsage             |
| - diskUsage               |
| - processCount            |
+---------------------------+

SystemData Structure

The SystemData structure stores the resource information collected from the Linux operating system.

+--------------------------------+
|          SystemData            |
+--------------------------------+
| double cpuUsage                |
| double memoryUsage             |
| double diskUsage               |
| int processCount               |
+--------------------------------+

Module Responsibilities
-----------------------

main.cpp -> Starts the web server

WebServer.cpp -> Handles TCP connections, HTTP responses, threshold checking, and dashboard generation

SystemMonitor.cpp -> Collects CPU, memory, disk, and process information

SystemMonitor.h -> Defines the SystemData structure and monitoring function

WebServer.h -> Declares the web server function

Relationship Between Modules
----------------------------

main.cpp
    |
    v
startWebServer()
    |
    v
WebServer.cpp
    |
    +------> getSystemData()
    |              |
    |              v
    |       SystemMonitor.cpp
    |              |
    |              v
    |         SystemData
    |
    +------> Threshold Checking
    |
    +------> Dashboard Response

Conclusion

The modular structure separates application startup, system monitoring, and web server functionality.

This makes the project easier to understand, maintain, and demonstrate.
