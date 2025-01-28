 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

#define SetAcquisitionChannel(X) do { ADPCH = X; } while (0)
//Sets sampling channel of ADCC without starting conversion


int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    int16_t gain;
    int16_t offset;

    gain = FLASH_Read(DIA_TSHR1);  
    offset = FLASH_Read(DIA_TSHR3);

    INTERRUPT_GlobalInterruptEnable();
    uint16_t ADC_MEAS = 0;
    int24_t temp_c = 0;
    SetAcquisitionChannel(channel_Temp);
    
    while(1)
    {
        asm ("SLEEP");
        asm ("NOP");
        ADC_MEAS = ADC_ConversionResultGet();
        temp_c = (int24_t) (ADC_MEAS) * gain;
        temp_c = temp_c / 256;
        temp_c = temp_c + offset;
        temp_c = temp_c / 10;
        printf("Device Temperature: %dC \r\n", temp_c); 
        
    }    
}