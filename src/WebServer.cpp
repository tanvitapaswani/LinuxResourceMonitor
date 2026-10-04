#include "../include/WebServer.h"
#include "../include/SystemMonitor.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sys/utsname.h>

using namespace std;

string getCurrentTime()
{
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    stringstream ss;
    ss << put_time(localTime, "%H:%M:%S");

    return ss.str();
}

string getStatus(double cpu, double memory, double disk)
{
    if (cpu > 80 || memory > 80 || disk > 90)
        return "ANOMALY DETECTED";

    return "SYSTEM NORMAL";
}

string getStatusClass(double cpu, double memory, double disk)
{
    if (cpu > 80 || memory > 80 || disk > 90)
        return "danger";

    return "normal";
}

string getBarClass(double value, double warning, double danger)
{
    if (value >= danger)
        return "bar-danger";

    if (value >= warning)
        return "bar-warning";

    return "bar-normal";
}

string createHTML(const SystemData &data,
                  const string &status,
                  const string &statusClass)
{
    utsname systemInfo;

    uname(&systemInfo);

    stringstream html;

    html << R"HTML(
<!DOCTYPE html>
<html>
<head>

<meta charset="UTF-8">

<meta http-equiv="refresh" content="5">

<meta name="viewport"
      content="width=device-width, initial-scale=1.0">

<title>Linux Resource Monitor</title>

<style>

* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}

body {
    font-family: Arial, Helvetica, sans-serif;
    background:
        radial-gradient(circle at 20% 10%, #332052 0%, transparent 30%),
        radial-gradient(circle at 90% 80%, #251342 0%, transparent 30%),
        #0b0712;

    color: #f5f0ff;
    min-height: 100vh;
    padding: 35px;
}

.container {
    max-width: 1250px;
    margin: auto;
}

/* ---------------- HEADER ---------------- */

.header {
    display: flex;
    justify-content: space-between;
    align-items: flex-end;
    margin-bottom: 30px;
}

.header-left small {
    color: #a98bc9;
    letter-spacing: 3px;
    font-size: 11px;
    text-transform: uppercase;
}

.header-left h1 {
    font-size: 34px;
    margin-top: 8px;
    font-weight: 700;
    letter-spacing: -1px;
}

.header-left p {
    margin-top: 8px;
    color: #9f91ad;
    font-size: 14px;
}

.active {
    padding: 10px 17px;
    border-radius: 30px;

    background: rgba(163, 91, 255, 0.10);

    border: 1px solid rgba(190, 120, 255, 0.35);

    color: #d7b7ff;

    font-size: 11px;
    letter-spacing: 1.5px;

    box-shadow:
        0 0 20px rgba(150, 70, 255, 0.12);
}

.dot {
    display: inline-block;

    width: 7px;
    height: 7px;

    border-radius: 50%;

    background: #c58cff;

    box-shadow:
        0 0 10px #c58cff;

    margin-right: 7px;
}

/* ---------------- MAIN RESOURCE CARDS ---------------- */

.resource-grid {
    display: grid;

    grid-template-columns:
        repeat(4, 1fr);

    gap: 16px;

    margin-bottom: 18px;
}

.card {
    background:
        linear-gradient(
            145deg,
            rgba(42, 27, 61, 0.95),
            rgba(19, 13, 28, 0.95)
        );

    border: 1px solid rgba(178, 123, 226, 0.18);

    border-radius: 18px;

    padding: 22px;

    box-shadow:
        0 15px 45px rgba(0, 0, 0, 0.25),
        inset 0 1px rgba(255,255,255,0.03);
}

.card:hover {
    border-color: rgba(192, 132, 255, 0.35);
}

.card-top {
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.card-label {
    color: #a997b7;
    font-size: 11px;
    letter-spacing: 2px;
    text-transform: uppercase;
}

.icon {
    width: 35px;
    height: 35px;

    display: flex;
    align-items: center;
    justify-content: center;

    border-radius: 10px;

    background: rgba(177, 102, 255, 0.10);

    color: #ce9cff;

    font-size: 16px;
}

.value {
    font-size: 31px;
    font-weight: 700;

    margin-top: 20px;
}

.unit {
    color: #8f829c;}

.progress {
    width: 100%;
    height: 5px;

    background: #21182b;

    border-radius: 10px;

    overflow: hidden;

    margin-top: 17px;
}

.progress-bar {
    height: 100%;

    border-radius: 10px;

    background: linear-gradient(
        90deg,
        #7c3fb2,
        #d39aff
    );

    box-shadow:
        0 0 12px rgba(190, 105, 255, 0.55);
}

.bar-warning {
    background: linear-gradient(
        90deg,
        #a76b39,
        #e5b06c
    );

    box-shadow:
        0 0 12px rgba(229, 176, 108, 0.45);
}

.bar-danger {
    background: linear-gradient(
        90deg,
        #9d3c68,
        #ff79b0
    );

    box-shadow:
        0 0 12px rgba(255, 90, 170, 0.55);
}

/* ---------------- STATUS SECTION ---------------- */

.status-panel {
    background:
        linear-gradient(
            135deg,
            rgba(39, 25, 57, 0.96),
            rgba(17, 11, 25, 0.96)
        );

    border: 1px solid rgba(181, 124, 232, 0.20);

    border-radius: 20px;

    padding: 28px;

    margin-bottom: 18px;

    position: relative;

    overflow: hidden;
}

.status-panel::after {
    content: "";

    position: absolute;

    width: 180px;
    height: 180px;

    right: -60px;
    bottom: -80px;

    border-radius: 50%;

    background:
        radial-gradient(
            circle,
            rgba(190, 108, 255, 0.20),
            transparent 70%
        );
}

.section-title {
    color: #9f8cae;

    font-size: 10px;

    letter-spacing: 2.5px;

    text-transform: uppercase;

    margin-bottom: 16px;
}

.status-row {
    display: flex;

    justify-content: space-between;

    align-items: center;

    margin-bottom: 27px;
}

.status-row h2 {
    font-size: 25px;
}

.normal-text {
    color: #d5a8ff;

    text-shadow:
        0 0 15px rgba(190, 120, 255, 0.35);
}

.danger-text {
    color: #ff8fbd;

    text-shadow:
        0 0 15px rgba(255, 80, 150, 0.35);
}

.status-time {
    color: #82758d;
    font-size: 12px;
}

/* ---------------- RESOURCE BARS ---------------- */

.resource-row {
    margin-bottom: 18px;
}

.resource-info {
    display: flex;
    justify-content: space-between;

    font-size: 12px;

    margin-bottom: 7px;

    color: #a99ab2;
}

.resource-info span:last-child {
    color: #ddd0e6;
}

.large-progress {
    height: 7px;
}

/* ---------------- LOWER GRID ---------------- */

.lower-grid {
    display: grid;

    grid-template-columns: 1fr 1fr;

    gap: 18px;

    margin-bottom: 18px;
}

.panel {
    background:
        linear-gradient(
            145deg,
            rgba(35, 23, 50, 0.95),
            rgba(16, 11, 23, 0.96)
        );

    border: 1px solid rgba(178, 123, 226, 0.17);

    border-radius: 18px;

    padding: 24px;
}

.panel-header {
    display: flex;
    justify-content: space-between;

    align-items: center;

    margin-bottom: 22px;
}

.panel-header h3 {
    font-size: 16px;
}

.panel-header span {
    color: #77687e;
    font-size: 10px;
    letter-spacing: 1px;
}

/* ---------------- ALERT ---------------- */

.alert {
    display: flex;

    align-items: center;

    gap: 13px;

    padding: 14px;

    background: rgba(255,255,255,0.025);

    border: 1px solid rgba(255,255,255,0.04);

    border-radius: 12px;

    margin-bottom: 9px;
}

.alert-icon {
    width: 31px;
    height: 31px;

    border-radius: 9px;

    display: flex;
    align-items: center;
    justify-content: center;

    background: rgba(179, 103, 255, 0.10);

    color: #cb94ff;
}

.alert-text strong {
    display: block;

    font-size: 12px;

    margin-bottom: 4px;
}

.alert-text small {
    color: #786b80;

    font-size: 10px;
}

/* ---------------- SYSTEM INFO ---------------- */

.info-row {
    display: flex;

    justify-content: space-between;

    padding: 13px 0;

    border-bottom:
        1px solid rgba(255,255,255,0.045);

    font-size: 12px;
}

.info-row:last-child {
    border-bottom: none;
}

.info-label {
    color: #796d82;
}

.info-value {
    color: #d5c8dc;
}

/* ---------------- FOOTER ---------------- */

.footer {
    text-align: center;

    padding-top: 12px;

    color: #5f5267;

    font-size: 10px;

    letter-spacing: 1px;
}

/* ---------------- RESPONSIVE ---------------- */

@media (max-width: 900px) {

    .resource-grid {
        grid-template-columns: repeat(2, 1fr);
    }

    .lower-grid {
        grid-template-columns: 1fr;
    }

}

@media (max-width: 600px) {

    body {
        padding: 18px;
    }

    .header {
        flex-direction: column;
        align-items: flex-start;
        gap: 18px;
    }

    .header-left h1 {
        font-size: 27px;
    }

    .resource-grid {
        grid-template-columns: 1fr;
    }

}

</style>

</head>

<body>

<div class="container">

<!-- HEADER -->

<div class="header">

    <div class="header-left">

        <small>Linux System Monitoring</small>

        <h1>Linux Resource Monitor</h1>

        <p>
            Real-time system health & anomaly detection
        </p>

    </div>

    <div class="active">
        <span class="dot"></span>
        MONITORING ACTIVE
    </div>

</div>


<!-- RESOURCE CARDS -->

<div class="resource-grid">

    <div class="card">

        <div class="card-top">

            <span class="card-label">
                CPU Usage
            </span>

            <div class="icon">
                ◉
            </div>

        </div>

        <div class="value">
)HTML";

    html << fixed << setprecision(1) << data.cpuUsage;

    html << R"HTML(
            <span class="unit">%</span>
        </div>

        <div class="progress">

            <div class="progress-bar )HTML";

    html << getBarClass(data.cpuUsage, 70, 80);

    html << R"HTML(" style="width:)HTML";

    html << data.cpuUsage;

    html << R"HTML(%"></div>

        </div>

    </div>


    <div class="card">

        <div class="card-top">

            <span class="card-label">
                Memory Usage
            </span>

            <div class="icon">
                ◈
            </div>

        </div>

        <div class="value">
)HTML";

    html << fixed << setprecision(1) << data.memoryUsage;

    html << R"HTML(
            <span class="unit">%</span>
        </div>

        <div class="progress">

            <div class="progress-bar )HTML";

    html << getBarClass(data.memoryUsage, 70, 80);

    html << R"HTML(" style="width:)HTML";

    html << data.memoryUsage;

    html << R"HTML(%"></div>

        </div>

    </div>


    <div class="card">

        <div class="card-top">

            <span class="card-label">
                Disk Usage
            </span>

            <div class="icon">
                ◇
            </div>

        </div>

        <div class="value">
)HTML";

    html << fixed << setprecision(1) << data.diskUsage;

    html << R"HTML(
            <span class="unit">%</span>
        </div>

        <div class="progress">

            <div class="progress-bar )HTML";

    html << getBarClass(data.diskUsage, 80, 90);

    html << R"HTML(" style="width:)HTML";

    html << data.diskUsage;

    html << R"HTML(%"></div>

        </div>

    </div>


    <div class="card">

        <div class="card-top">

            <span class="card-label">
                Processes
            </span>

            <div class="icon">
                ⬡
            </div>

        </div>

        <div class="value">
)HTML";

    html << data.processCount;

    html << R"HTML(
            <span class="unit"> running</span>
        </div>

        <div class="progress">

            <div class="progress-bar"
                 style="width:45%">
            </div>

        </div>

    </div>

</div>


<!-- SYSTEM HEALTH -->

<div class="status-panel">

    <div class="section-title">
        System Health
    </div>

    <div class="status-row">

        <h2 class=")HTML";

    html << statusClass;

    html << R"HTML(-text">
)HTML";

    html << status;

    html << R"HTML(
        </h2>

        <span class="status-time">
            Last updated: )HTML";

    html << getCurrentTime();

    html << R"HTML(
        </span>

    </div>


    <div class="resource-row">

        <div class="resource-info">

            <span>CPU</span>

            <span>)HTML";

    html << fixed << setprecision(1) << data.cpuUsage << "%</span>";

    html << R"HTML(

        </div>

        <div class="progress large-progress">

            <div class="progress-bar )HTML";

    html << getBarClass(data.cpuUsage, 70, 80);

    html << R"HTML("
                 style="width:)HTML";

    html << data.cpuUsage;

    html << R"HTML(%">
            </div>

        </div>

    </div>


    <div class="resource-row">

        <div class="resource-info">

            <span>Memory</span>

            <span>)HTML";

    html << fixed << setprecision(1) << data.memoryUsage << "%</span>";

    html << R"HTML(

        </div>

        <div class="progress large-progress">

            <div class="progress-bar )HTML";

    html << getBarClass(data.memoryUsage, 70, 80);

    html << R"HTML("
                 style="width:)HTML";

    html << data.memoryUsage;

    html << R"HTML(%">
            </div>

        </div>

    </div>


    <div class="resource-row">

        <div class="resource-info">

            <span>Disk</span>

            <span>)HTML";

    html << fixed << setprecision(1) << data.diskUsage << "%</span>";

    html << R"HTML(

        </div>

        <div class="progress large-progress">

            <div class="progress-bar )HTML";

    html << getBarClass(data.diskUsage, 80, 90);

    html << R"HTML("
                 style="width:)HTML";

    html << data.diskUsage;

    html << R"HTML(%">
            </div>

        </div>

    </div>

</div>


<!-- LOWER PANELS -->

<div class="lower-grid">


<!-- ALERTS -->

<div class="panel">

    <div class="panel-header">

        <h3>Recent Alerts</h3>

        <span>LIVE</span>

    </div>
)HTML";

    bool hasAlert = false;

    if (data.cpuUsage > 80)
    {
        hasAlert = true;

        html << R"HTML(
        <div class="alert">

            <div class="alert-icon">!</div>

            <div class="alert-text">

                <strong>High CPU usage detected</strong>

                <small>CPU usage exceeded 80%</small>

            </div>

        </div>
)HTML";
    }

    if (data.memoryUsage > 80)
    {
        hasAlert = true;

        html << R"HTML(
        <div class="alert">

            <div class="alert-icon">!</div>

            <div class="alert-text">

                <strong>High memory usage detected</strong>

                <small>Memory usage exceeded 80%</small>

            </div>

        </div>
)HTML";
    }

    if (data.diskUsage > 90)
    {
        hasAlert = true;

        html << R"HTML(
        <div class="alert">

            <div class="alert-icon">!</div>

            <div class="alert-text">

                <strong>High disk usage detected</strong>

                <small>Disk usage exceeded 90%</small>

            </div>

        </div>
)HTML";
    }

    if (!hasAlert)
    {
        html << R"HTML(
        <div class="alert">

            <div class="alert-icon">✓</div>

            <div class="alert-text">

                <strong>No active anomalies</strong>

                <small>All monitored resources are within limits</small>

            </div>

        </div>
)HTML";
    }


    html << R"HTML(

</div>


<!-- SYSTEM INFORMATION -->

<div class="panel">

    <div class="panel-header">

        <h3>Linux System Information</h3>

        <span>SYSTEM</span>

    </div>

    <div class="info-row">

        <span class="info-label">
            Operating System
        </span>

        <span class="info-value">
            Linux
        </span>

    </div>

    <div class="info-row">

        <span class="info-label">
            Kernel
        </span>

        <span class="info-value">
)HTML";

    html << systemInfo.release;

    html << R"HTML(
        </span>

    </div>

    <div class="info-row">

        <span class="info-label">
            Architecture
        </span>

        <span class="info-value">
)HTML";

    html << systemInfo.machine;

    html << R"HTML(
        </span>

    </div>

    <div class="info-row">

        <span class="info-label">
            Running Processes
        </span>

        <span class="info-value">
)HTML";

    html << data.processCount;

    html << R"HTML(
        </span>

    </div>

    <div class="info-row">

        <span class="info-label">
            Monitoring
        </span>

        <span class="info-value">
            Active
        </span>

    </div>

</div>

</div>


<div class="footer">

    LINUX RESOURCE MONITOR &nbsp; • &nbsp;
    C++ SYSTEM PROGRAMMING &nbsp; • &nbsp;
    AUTO REFRESH 5 SEC

</div>

</div>

</body>
</html>

)HTML";

    return html.str();
}


void startWebServer()
{
    int serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (serverSocket < 0)
    {
        cerr << "Failed to create socket." << endl;
        return;
    }


    int option = 1;

    setsockopt(
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &option,
        sizeof(option)
    );


    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;

    serverAddress.sin_addr.s_addr =
        INADDR_ANY;

    serverAddress.sin_port =
        htons(8080);


    if (bind(
            serverSocket,
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress)) < 0)
    {
        cerr << "Failed to bind port 8080." << endl;

        close(serverSocket);

        return;
    }


    if (listen(serverSocket, 10) < 0)
    {
        cerr << "Failed to listen on port 8080."
             << endl;

        close(serverSocket);

        return;
    }


    cout << "Linux Resource Monitor running at "
         << "http://localhost:8080"
         << endl;


    while (true)
    {
        sockaddr_in clientAddress{};

        socklen_t clientLength =
            sizeof(clientAddress);


        int clientSocket = accept(
            serverSocket,
            (struct sockaddr*)&clientAddress,
            &clientLength
        );


        if (clientSocket < 0)
            continue;


        char buffer[4096];

        memset(buffer, 0, sizeof(buffer));


        read(
            clientSocket,
            buffer,
            sizeof(buffer) - 1
        );


        SystemData data =
            getSystemData();


        string status =
            getStatus(
                data.cpuUsage,
                data.memoryUsage,
                data.diskUsage
            );


        string statusClass =
            getStatusClass(
                data.cpuUsage,
                data.memoryUsage,
                data.diskUsage
            );


        string html =
            createHTML(
                data,
                status,
                statusClass
            );


        string response;

        response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: "
            + to_string(html.size())
            + "\r\n"
            "Connection: close\r\n"
            "\r\n"
            + html;


        send(
            clientSocket,
            response.c_str(),
            response.size(),
            0
        );


        close(clientSocket);
    }


    close(serverSocket);
}