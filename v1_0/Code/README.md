# Code

## Folder Structure

> **LowLevelDriver**
>
> The master core of low level driver is stm32f407vet6. It is responsible for controlling all kinds of motors including BLDCs, stepper motor, pump. Besides, remote receiver "MC7RE-V2" is mounted. the receiver received signal from remote controller "Micro6C" and send data to master core. For this version, it is the only way to control BigZ. In conclude, ***LowLevelDriver is responsible for basically driving and controlling all necessary devices. This driver doesn't do anything "intelligent" for BigZ.***
>
> **ConpanionDriver**
>
> The vice core of companion driver is esp32-wroom-32. Assisting master core is its job. So it drives devices including TFT screen, MicroSD, led and buzzer. It also needs to do wireless connection such as wifi and ble. In conclude, ***CompanionDriver is responsible for additional features and convenience for updating.***