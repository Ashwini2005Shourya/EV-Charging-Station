# ⚡ IoT-Based Smart EV Charging Station (3-Bay System)
### 🛠️ Emertxe Internship Project

An advanced, IoT-enabled **Smart EV Charging Station System** designed for 3 parallel charging bays. The system utilizes an **ESP32 microcontroller** architecture to monitor local charging bay metrics, manage state transitions, and connect seamlessly to the **ThingsBoard IoT Cloud** platform over the **MQTT protocol**. Each bay supports bi-directional communication, allowing remote administrative management and over-the-air bay activation via **Remote Procedure Calls (RPC)**.

---

## 🏗️ Repository Directory Layout
The firmware project is organized using an object-oriented modular file structural pattern:

```text
├── include/                 # Header Files (.h)
│   ├── attributes.h         # Definitions for data attributes and device telemetry profiles
│   ├── config.h             # MQTT Credentials, Wi-Fi Configuration, and Cloud Tokens
│   ├── Edge_AI.h            # Framework parameters for local processing on the edge
│   ├── Network.h            # Low-level socket wrappers for Wi-Fi and MQTT client state machines
│   ├── Optimization.h       # Efficiency algorithms for charging cycle management
│   ├── Peripherals.h        # Pin maps, ADC configurations, and sensor/actuator hardware maps
│   ├── rpc.h                # Server-to-client cloud RPC callback method registrations
│   ├── State.h              # State-machine types and lifecycle enum configurations
│   └── Telementry.h         # Packet payloads formatting for cloud transmission data
├── src/                     # Source Files (.cpp)
│   ├── attributes.cpp       # Management of telemetry data structures
│   ├── Edge_AI.cpp          # Processing of basic localized data logic
│   ├── main.cpp             # Central setup loop thread execution framework
│   ├── model.h              # In-line state memory maps or structural arrays
│   ├── Network.cpp          # Implementation of automated reconnection loop wrappers
│   ├── Optimization.cpp     # Execution code for the internal power optimization routines
│   ├── Peripherals.cpp      # Low-level sensor reads and hardware driver abstractions
│   ├── rpc.cpp              # Processing routine mapping server command actions
│   ├── State.cpp            # State management system executions
│   └── Telementry.cpp       # Packaging and transmission loops of real-time strings
├── lib/                     # Private workspace library dependency modules
├── test/                    # Validation targets and execution sandboxes
└── README.md                # Comprehensive system project manual
```

### 🛠️ Hardware & Software Specifications
* **Core Microcontroller:** ESP32 Doit DevKit V1
* **Communication Protocol:** MQTT (Message Queuing Telemetry Transport)
* **IoT Cloud Platform:** ThingsBoard Cloud Console
* **Development Framework:** PlatformIO Engine inside VS Code / Core CLI
* **Primary Libraries:** `PubSubClient` (MQTT handling), `ArduinoJson` (JSON parsing)

---

## 💻 Local Setup & Deployment

### Prerequisites
1. Install [VS Code](https://visualstudio.com) along with the **PlatformIO IDE** extension.
2. Setup a **ThingsBoard** account (Cloud instance or local PE/CE server).
3. Create a device profile on ThingsBoard and provision access credentials for the station.

### Configuration
Update your private connectivity secrets inside `include/config.h`:
```cpp
#define WIFI_SSID       "Your_WiFi_Name"
#define WIFI_PASSWORD   "Your_WiFi_Password"
#define TOKEN           "THINGSBOARD_ACCESS_TOKEN"
#define THINGSBOARD_SERVER "thingsboard.cloud"
```

### Building and Flashing
1. Clone or copy the codebase to your local environment.
2. Navigate to your terminal or PlatformIO terminal workspace.
3. Compile the application binary:
   ```bash
   pio run
   ```
4. Upload the generated binary file to your physically connected target board:
   ```bash
   pio run --target upload
   ```

---

## 🤝 Acknowledgments
* **Emertxe Information Technologies, Bangalore** for the structured mentorship, excellent course curriculum, and guidance throughout this project.

***

# 🐙 Steps to Push this Project to GitHub
This section details how to push this exact folder setup to your remote GitHub profile.

### 1. Verification of the `.gitignore` Architecture
Before adding files to the git staging area, ensure your `.gitignore` file actively tracks and excludes local build artifacts so your remote storage footprint remains lightweight. The file should block the following elements from deployment:
```text
.pio/
.vscode/
*.bin
*.elf
*.map
```

### 2. Initializing Git & Committing Locally
Open your command terminal at the root path of the project folder (the folder containing `include/` and `src/`) and run these commands sequentially to register your files on a local version branch:

```bash
# Initialize an empty local Git tracking workspace
git init

# Stage all architectural directories, source files, and dependencies
git add .

# Commit tracked components with a descriptive deployment message
git commit -m "Initial commit: 3-Bay Smart EV Charging Station firmware with MQTT and ThingsBoard cloud RPC support"

# Standardize the root development branch name to main
git branch -M main
```

### 3. Deploying to the Remote Server Namespace
1. Log into your personal portal at [GitHub](https://github.com).
2. Select **New Repository**. Assign a directory safe title (e.g., `Smart-EV-Charging-Station-3Bay`). Keep remaining properties unchecked (do not instantiate default files as you are providing them locally). Click **Create Repository**.
3. Map your terminal thread to your customized cloud system link by running the following remote registration commands:

```bash
# Form an upstream connection hook toward your GitHub address profile
git remote add origin https://github.comYourUsername/YourRepositoryName.git

# Stream and synchronize local main structures directly to the remote repository
git push -u origin main
```
