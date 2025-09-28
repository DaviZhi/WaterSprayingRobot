# Water Spraying Robot: BigZ

![picture](https://github.com/DaviZhi/picx-images-hosting/raw/master/image.1lc73aek0t.webp "BigZ")

## Introduce
- **What is this project about**

  She is a robot named **BigZ**. From a physical instance, she is a robot that looks like a car, but more than that,she is a ***platform for implementing and validating electronic related technologies***.

- **Why is this project created** 

  Like I said, she is a ***platform*** that reflects what I have learned. I want to implement different technologies to make BigZ become more clever from "just a car".

## Development Environment
- **Software**  
  - [**SOLIDWORKS 2024**](https://www.solidworks.com/support/free-downloads/ "download link") for mechanical structure
  - [**jlc EDA**](https://lceda.cn/page/download "download link")(EasyEDA) for PCB design
  - [**Keil uVision 5**](https://www.keil.com/download/product/ "download link") + [**STM32CubeMX**](https://www.st.com/en/development-tools/stm32cubemx.html "download link") for coding lowest level driver
  - [**vscode**](https://code.visualstudio.com/Download "download link") + [**ESP-IDF**](https://docs.espressif.com/projects/esp-idf/en/v5.5.1/esp32/get-started/index.html# "get started") for coding addtional level driver
- **Hardware**
  - **STM32F407** as lowest level
  - **ESP32-WROOM-32** as additional level

## Project Structure

````
v1_0	// Current version.
├── Code	// Source code here spans from hardware drivers to simple intelligence modules.
│   ├── LowLevelDriver
│   ├── CompanionDriver
│   └── README.md
├── DevFrame	// A framework defining and guiding the development of robotic hardware and software.
│   └── HardwareFramework.mm
├── MechanicalStructure	// This folder contains simple SolidWorks 3D models of all robotic components.
│   ├── Battery
│   ├── BLDC
│   ├── Body
│   ├── Chassis
│   ├── Connection
│   ├── PCBModel
│   ├── Wheel
│   ├── README.md
│   └── WholeStructure.SLDASM
├── PCBdesign	// This directory contains all device PCB design and fabrication files, designed in jlcEDA.
│   ├── ChassisMotor
│   ├── CircuitSupply
│   ├── Gerber
│   ├── MasterCore
│   ├── StepperMotor
│   ├── WaterPump
│   └── README.md
├── ReferenceManual	// Various reference manuals required during the development process.
│   ├── ExternalFlash
│   ├── LevelConversion
│   ├── MasterCore
│   ├── MotorCtrl
│   ├── PowerManagement
│   ├── Remote
│   ├── TFTScreen
│   └── ViceCore
└── RevisionLog	// Summarize the correction of errors, update a certain section, or add any new features.
    └── UpdateLog.txt
````

## License

This project is under [MIT License](https://github.com/DaviZhi/WaterSprayingRobot?tab=MIT-1-ov-file).
