# Testing Documentation

## 1. Testing Overview

The Linux Resource Monitor was tested to verify that the application compiles correctly, starts successfully, collects system information, and displays the monitoring dashboard.

## 2. Test Environment

- Operating System: Ubuntu Linux
- Programming Language: C++
- Compiler: G++
- Server Port: 8080
- Browser: Web Browser
- Development Environment: Visual Studio Code

## 3. Test Cases

| Test Case | Test Description | Expected Result |
|-----------|------------------|-----------------|
| TC01 | Compile the C++ source files | Application compiles successfully |
| TC02 | Start the monitoring application | Server starts on port 8080 |
| TC03 | Open `localhost:8080` | Monitoring dashboard is displayed |
| TC04 | Check CPU usage | Current CPU usage is displayed |
| TC05 | Check memory usage | Current memory usage is displayed |
| TC06 | Check disk usage | Current disk usage is displayed |
| TC07 | Check process count | Number of running processes is displayed |
| TC08 | Check system health | System status is displayed |
| TC09 | Check anomaly detection | Alert is displayed when a threshold is exceeded |
| TC10 | Refresh the dashboard | Updated resource values are displayed |

## 4. Compilation Test

The application is compiled using:

```bash
g++ src/main.cpp src/SystemMonitor.cpp src/WebServer.cpp -o monitor

## 5. Server Test

The application is started using:

```bash
./monitor

The server listens on:

http://localhost:8080

The monitoring dashboard can be accessed by opening the above address in a web browser.

A successful server start confirms that the C++ TCP socket server is running correctly.

## 6. Resource Monitoring Test

The monitoring dashboard was checked to verify that it correctly displays the current system resource information.

The following resources are monitored:

- CPU usage
- Memory usage
- Disk usage
- Process count
- Linux kernel information
- System architecture information

The displayed values are collected from the Linux operating system using C++ system interfaces.

## 7. Anomaly Detection Test

The application checks CPU, memory, and disk usage against predefined thresholds.

| Resource | Threshold |
|----------|-----------|
| CPU | > 80% |
| Memory | > 80% |
| Disk | > 90% |

If a resource exceeds its threshold, the dashboard displays an anomaly alert.

If all monitored resources remain below their thresholds, the system displays a normal status.

## 8. Dashboard Refresh Test

The dashboard automatically refreshes every 5 seconds.

This allows updated CPU, memory, disk, and process information to be displayed without manually refreshing the browser.

The refresh mechanism helps provide up-to-date monitoring information to the user.

## 9. Conclusion

The testing process verifies that the Linux Resource Monitor can compile and run successfully on Linux.

The application collects system resource information, performs threshold-based anomaly detection, and displays the results through the monitoring dashboard.

The tests confirm the basic functionality and expected behavior of the project.