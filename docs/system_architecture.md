# System Architecture Diagram

## Linux Resource Monitor

```text
                 +-------------------------+
                 |   Linux Operating      |
                 |       System           |
                 +-----------+-------------+
                             |
                             v
                 +-------------------------+
                 |    System Monitor       |
                 |         (C++)           |
                 +-----------+-------------+
                             |
              +--------------+--------------+
              |              |              |
              v              v              v
        +-----------+  +-----------+  +-----------+
        |    CPU    |  |  Memory   |  |   Disk    |
        +-----------+  +-----------+  +-----------+
              |              |              |
              +--------------+--------------+
                             |
                             v
                 +-------------------------+
                 |   Process Monitoring    |
                 |        /proc            |
                 +-----------+-------------+
                             |
                             v
                 +-------------------------+
                 |   Threshold Checking    |
                 |   & Anomaly Detection   |
                 +-----------+-------------+
                             |
                             v
                 +-------------------------+
                 |     C++ Web Server      |
                 |      TCP Socket         |
                 |       Port 8080         |
                 +-----------+-------------+
                             |
                             v
                 +-------------------------+
                 |   Monitoring Dashboard  |
                 |      Web Browser        |
                 +-------------------------+

Data Flow-

Linux System
     |
     v
Resource Collection
     |
     v
SystemData
     |
     v
Threshold Checking
     |
     +-------> System Normal
     |
     +-------> Anomaly Detected
     |
     v
C++ Web Server
     |
     v
Web Browser Dashboard

