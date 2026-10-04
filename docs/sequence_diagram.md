# Sequence Diagram

## Linux Resource Monitor

The sequence below shows how the application collects system information and displays it on the monitoring dashboard.

```text
User
 |
 | 1. Open localhost:8080
 v
Web Browser
 |
 | 2. Send HTTP Request
 v
C++ Web Server
 |
 | 3. Request system data
 v
System Monitor
 |
 | 4. Read Linux system interfaces
 v
Linux Operating System
 |
 | 5. Return CPU, Memory, Disk
 |    and Process information
 v
System Monitor
 |
 | 6. Return SystemData
 v
C++ Web Server
 |
 | 7. Check resource thresholds
 v
Anomaly Detection
 |
 | 8. Generate monitoring response
 v
C++ Web Server
 |
 | 9. Send HTTP Response
 v
Web Browser
 |
 | 10. Display updated values
 v
Monitoring Dashboard

Sequence Description
The user opens http://localhost:8080 in a web browser.
The browser sends an HTTP request to the C++ web server.
The web server requests current system information.
The System Monitor reads information from Linux system interfaces.
CPU, memory, disk, and process information is collected.
The collected values are stored in the SystemData structure.
The application checks the values against predefined thresholds.
The C++ web server generates the monitoring dashboard response.
The response is sent back to the web browser.
The browser displays the updated monitoring information and system status.