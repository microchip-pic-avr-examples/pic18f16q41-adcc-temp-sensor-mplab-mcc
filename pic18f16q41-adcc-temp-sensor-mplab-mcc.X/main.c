/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/
#include "mcc_generated_files/system/system.h"
//Sets sampling channel of ADCC without starting conversion
#define SetAcquisitionChannel(X) do { ADPCH = X; } while (0)

int16_t gain;
int16_t offset;

//int24_t getTemperature(void)
//{
    
//}

int main(void)
{
    SYSTEM_Initialize();
    
    gain = FLASH_ReadWord(DIA_TSHR1);  
    offset = FLASH_ReadWord(DIA_TSHR3);
    
   INTERRUPT_GlobalInterruptEnable();
   
   uint16_t ADC_MEAS = 0;
   int24_t temp_c = 0;
   SetAcquisitionChannel(channel_Temp);
  
   while(1)
    {       
ADC_MEAS = ADCC_GetConversionResult(); 
temp_c = (int24_t) (ADC_MEAS) * gain;
temp_c = temp_c / 256;
temp_c = temp_c + offset;
temp_c = temp_c / 10;
printf("gain: %d \r\n " , gain);
printf("offset: %d \r\n " , offset);
printf("Temp Sensor Result %d \r\n", temp_c);
asm ("SLEEP"); 
asm ("NOP");
   }
}