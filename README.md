# Water Spraying Robot: BigZ

## Introduce
- **What is this project** 

  She is a robot named **BigZ**. From a physical instance, she is a robot that looks like a car, but more than that,she is a ***platform for implementing and validating electronic related technologies***.

- **Why is this project created** 

  Like I said, she is a ***platform*** that reflects what I have learned. I want to implement different technologies to make BigZ become more clever from "just a car".

## Development Environment
- **Software**  
  - **SOLIDWORKS 2024** for mechanical structure
  - **jlc EDA(EasyEDA)** for PCB design
  - **Keil uvision 5+STM32CubeMX** for coding lowest level driver
  - **vscode+ESP-IDF** for coding addtional level driver
- **Hardware**
  - **STM32F407** as lowest level
  - **ESP32-WROOM-32** as additional level

## Folder Structure
>~~v1.0 (aborted version, mainly debug)~~ 
>
>**v1_0** 
>
>Current version.  
>
>> **Code** 
>>
>> This folder contains the robot from the lowest level driver control source code to the simplest "intelligent" source code at the upper level. 
>>
>> **MechanicalStructure** 
>>
>> This folder contains 3D design drawings of various components of the robot, all of which are designed in SolidWorks. all mechanical parts are very simple. 
>>
>> **PCBdesign** 
>>
>> This folder contains PCB design files and corresponding PCB fabrication files of each device. In function, such as *power management*, different kinds of *motor drivers*, *master control* peripheral circuit and so on. I use jic EDA design to do PCBA. 
>>
>> **ReferenceManual** 
>>
>> Various reference manuals required during the development process. 
>>
>> **DevFrame** 
>>
>> Framework of hardware, software. They guide the development direction of robot software and hardware. 
>>
>> **RevisionLog** 
>>
>> Summarize the correction of errors, update a certain section, or add any new features.