
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Using the Temperature Indicator on PIC18F16Q41
In this example, the ADCC will be configured to sample the Temperature Indicator Module in order to measure the device temperature of a PIC18F16Q41 microcontroller.
## Related Documentation

* [PIC18F16Q41 Data sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F06-16Q41-DataSheet-40002214C.pdf)

* [PIC18F16Q41 Device Page](https://www.microchip.com/wwwproducts/en/PIC18F16Q41?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_pic18q41&utm_content=pic18f16q41-adcc-temp-sensor-mplab-mcc-github)

* [PIC18F16Q41 Curiosity Nano Users Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F16Q41-Curiosity-Nano-Hardware-User-Guide-DS50003048A.pdf)

## Software Used



- [MPLAB® X IDE v6.20.0 or newer](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_pic18q41&utm_content=pic18f16q41-adcc-temp-sensor-mplab-mcc-github)
- [MPLAB XC8 v3.0.0 or newer compiler](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xc-compilers?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_pic18q41&utm_content=pic18f16q41-adcc-temp-sensor-mplab-mcc-github)
- [MPLAB Code Configurator (MCC)](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-code-configurator?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_pic18q41&utm_content=pic18f16q41-adcc-temp-sensor-mplab-mcc-github)
  - Melody Library v5.1.4 or newer
- [MPLAB Data Visualizer Plugin](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-data-visualizer?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_pic18q41&utm_content=pic18f16q41-adcc-temp-sensor-mplab-mcc-github) or other serial terminal



## Hardware Used

* [PIC18F16Q41 Curiosity Nano](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EV26Q64A?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_pic18q41&utm_content=pic18f16q41-adcc-temp-sensor-mplab-mcc-github)

## Setup

**Step #1: Creating the Project**

+ On the tool bar, click New Project
+ Microchip Embedded; Standalone Project
+ Enter the Device
  + For this Project: PIC18F16Q41
+ Enter a name for this project, such as *adcc-temp-sensor*
  + Name: “adcc-temp-sensor”
  + **Note**: The project name cannot have any empty spaces

**Step #2: MPLAB Code Configurator (MCC)**

  +	Modify the Clock Control
    +	Set “Clock Source” to High Frequency Internal Oscillator (HFINTOSC)
    + Set “HF Internal Clock” to 64_MHz
    + Set “Clock Divider” to 1

![Clock Settings](images/Picture1.PNG)


+ Set Configuration Bits
  + Disable "External Oscillator Mode Selection" in CONFIG 1
  + Set "Power-up Default Value for COSC" in CONFIG 1 to "HFINTOSC with HFFRQ = 64MHz and CDIV = 1:1"
  + Ensure that "WDT Operating Mode" in CONFIG 5 is set to "WDT Disabled; SWDTEN is ignored"

![Configuration Bits](images/Picture2.PNG)


**Step #3: Adding ADCC, FVR, Memory, Timer, and UART Peripherals**

For this project to work properly, the application goes through a specific series of steps to minimize noise in the measurement.

 These steps are:
  1. Analog-to-Digital Converter with Computation (ADCC) is set up to run periodically from a hardware trigger
  2. The device is put to sleep
  3. The hardware trigger activates
  4. The temperature sensor is measured multiple times and averaged
  5. The microcontroller is woken up after the average is computed
  6. The result is converted to temperature
  7. The results are printed using UART

  + In Device Resources:
      + Drivers>ADCC>ADCC
      + Drivers>FVR>FVR
      + Drivers>Memory>MEMORY
      + Drivers>Timer>TMR2
      + Drivers>UART>UART1

  ![Project Resources](images/Picture3.PNG)


  Once the peripherals are added, change to following settings:

  Please refer to the Temperature Indicator Module on the [PIC18F16Q41 data sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F06-16Q41-DataSheet-40002214C.pdf) when configuring these peripherals.


  + TMR2
    + Hardware Settings
      + Control Mode: Roll over pulse
      + Start/Reset Option: Software control
    + Timer Clock
      + Clock Source: LFINTOSC
      + Prescaler: 1:8
      + Postscaler: 1:12
    + Timer Period(s)
      + Time Period (s): 0.5

<img src="images/Picture16.1.PNG" alt="TMR2 Config" width="450">


  + FVR
    + ***Custom Name:*** FVR
    + ***Enable FVR:*** Enabled
    + ***FVR_buffer 1 Gain (to ADC):*** 2x
    + ***Enable Temperature Sensor:*** Enabled
    + ***Voltage Range Selection***: Hi_Range


  ![FVR Config](images/Picture7.PNG)


  + ADCC
    + Hardware Settings
      + ***Operating Mode:*** Burst Average
      + ***Result Alignment:*** right
      + ***Positive Reference:*** FVR
      + ***Auto-conversion Trigger***: TMR2
      + ***Acquisition Count***: 8191
    + ADC Clock
      + ***Clock Source:*** ADCRC
    + Computation Feature
      + ***Error Calculation Mode:*** First derivative of Single measurement
      + ***Threshold Interrupt Mode:*** enabled
      + ***Repeat:*** 8
      + ***Accumulator Right Shift:*** 3
    + Interrupt settings
      + ***ADC Threshold is enabled***

  ![ADCC Config 1](images/Picture4.PNG)

  ![ADCC Config 2](images/Picture5.PNG)

  + UART1
    + Software Settings:
      +	Enable "Redirect STDIO to UART" in order to use the function (printf) for sending messages
    + Hardware Settings:
      +	Enable UART box must be checked
      + Enable transmit and Receive must be checked
      + Set the Baud Rate to 19200
      + Everything else can be left as default settings

![UART1 Config](images/Picture9.PNG)



  + In order for the temperature calculation to be made, gain and offset need to be read from the Device Information Area (DIA). By configuring the memory peripheral, this allows access to read those values.
  + Memory
      + Custom Name: FLASH
      + Add Data EE Routines: Enabled

  ![Memory Config](images/Picture6.PNG)


  **Step #4: Configure the Pins**
  + TX1 is connected to pin RB7
  + RX1 is connected to pin RB5

![Pin Manager](images/Picture10.PNG)

**Step #5: Generate the Project**
+ Click the **generate** button in MCC to create the appropriate header and source files for this configuration


**Step #6: Modifying main.c**
+ Once the project is generated, the new MCC generated header and source files will be in the project window. Select the `main.c` file and you will see an empty while(1) loop where you can add your application code.
+ Refer to section 39.2 on the  [PIC18F16Q41 data sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F06-16Q41-DataSheet-40002214C.pdf) to fully understand the temperature calculation

```
#include "mcc_generated_files/system/system.h"

#define SetAcquisitionChannel(X) do { ADPCH = X; } while (0)
//Sets sampling channel of ADCC without starting conversion


int main(void)
{
    SYSTEM_Initialize();

    int16_t gain;
    int16_t offset;

    gain = FLASH_ReadWord(DIA_TSHR1);  
    offset = FLASH_ReadWord(DIA_TSHR3);

    INTERRUPT_GlobalInterruptEnable();
    uint16_t ADC_MEAS = 0;
    int24_t temp_c = 0;
    SetAcquisitionChannel(channel_Temp);


   while(1)
    {    
        asm ("SLEEP");
        asm ("NOP");
        ADC_MEAS = ADCC_GetConversionResult();
        temp_c = (int24_t) (ADC_MEAS) * gain;
        temp_c = temp_c / 256;
        temp_c = temp_c + offset;
        temp_c = temp_c / 10;
        printf("Device Temperature: %dC \r\n", temp_c);
   }
}

```



+ Make and Program the Device


**Step #7: MPLAB Data Visualizer**
  + Open up the Data Visualizer on the host computer and select the COM port associated with the Curiosity Nano

    ![COM PORT Settings](images/Picture11.PNG)

  + Ensure that the **Terminal** tab is selected

  ![Terminal Tab](images/Picture12.PNG)

  + Once selected, configure the data visualizer to communicate at: 19200 baud, no parity, and 1 stop bit  

  ![COM PORT Configuration](images/Picture14.PNG)

  + If everything is set up correctly, then the Data Visualizer will start displaying the device temperature every half a second
  + If you cover or touch the DIE on the device, you will notice the temperature start to increase

  ![Terminal Emulator Results](images/Picture16.2.PNG)



  ## Summary

  This application demonstrates how to set up an ADCC and utilize the Temperature Indicator Module to measure the device temperature.
