# STM32 bare metal tutorial

This repository contains the source code for the Mutex Embedded Course on Udemy for bare metal or register level programming.


# Minimal project setup
- Create new CMake project with STM32CubeMX/STM32 VS Code extension
- Target should be STM32F103C8Tx
- Remove syscalls.c and sysmem.c
- Copy necessary STM32-header files to Inc folder (stm32fXxx.h, stm32fXXXxX.h, system_stm32fXxx.h) from the STM32Cube repository (/HOME/STM32Cube/Repository/STM32Cube_FW_FX_VX.X.X/Drivers/CMSIS/Device/ST/STM32FXxx/Include)
- Create Core folder and move Src and Inc folders to the Core folder
- Add CMSIS header files to CMSIS/Inc from the STM32Cube repository (/HOME/STM32Cube/Repository/STM32Cube_FW_FX_VX.X.X/Drivers/CMSIS/Include)
- Replace the auto generated startup file with the CMSIS startup file for the device (startup_stm32fXXXxX.s from /HOME/STM32Cube/Repository/STM32Cube_FW_FX_VX.X.X/Drivers/CMSIS/Device/ST/STM32FXxx/Source/Templates/gcc)
- Copy the system source file to the Core/Src folder (system_stm32fXxx.c from the STM32Cube repository (/HOME/STM32Cube/Repository/STM32Cube_FW_FX_VX.X.X/Drivers/CMSIS/Device/ST/STM32FXxx/Source/Templates))
- Adjust compiler settings in CMakeLists.txt and/or vscode_generated.cmake 
  - Paths and Symbols 
    - Inc -> ${ProjDirPath}/Core/Inc
    - ${ProjDirPath}/CMSIS/Inc
  - Source Location 
    - Core
    - CMSIS
  - Symbols 
    - Delete all but DEBUG
    - Add Type of STM-Series Symbol (e.g. STM32F103xB)
- Remove all in main.c and let only the loop
- Create a main.h file
```c
#include “stm32f1xx.h”
#include <stdbool.h>
#include <stdio.h>
```
- include “main.h” in main.c