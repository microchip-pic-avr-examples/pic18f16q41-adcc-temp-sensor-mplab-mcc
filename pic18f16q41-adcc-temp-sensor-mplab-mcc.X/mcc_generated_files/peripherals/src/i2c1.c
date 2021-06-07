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

#include <xc.h>
#include "../i2c1.h"

// Set the I2C1 module to the options selected in the user interface.
void I2C1_Initialize(void) {
    // TXB 0x0; 
    I2C1TXB = 0x0;
    // CNT 0x0; 
    I2C1CNTL = 0x0;
    // CNT 0x0; 
    I2C1CNTH = 0x0;
    // ADB 0x0; 
    I2C1ADB0 = 0x0;
    // ADB 0x0; 
    I2C1ADB1 = 0x0;
    // ADR 0x0; 
    I2C1ADR0 = 0x0;
    // ADR 0x0; 
    I2C1ADR1 = 0x0;
    // ADR 0x0; 
    I2C1ADR2 = 0x0;
    // ADR 0x0; 
    I2C1ADR3 = 0x0;
    // EN disabled; RSEN disabled; S Cleared by hardware after Start; CSTR Enable clocking; MODE four 7-bit address; 
    I2C1CON0 = 0x0;
    // ACKCNT Acknowledge; ACKDT Acknowledge; RXO No overflow; TXU No underflow; CSD Clock Stretching enabled; 
    I2C1CON1 = 0x0;
    // ACNT disabled; GCEN disabled; FME disabled; ABD enabled; SDAHT 300 ns hold time; BFRET 8 I2C Clock pulses; 
    I2C1CON2 = 0x0;
    // BTOIF No bus timeout; BCLIF No bus collision detected; NACKIF No NACK/Error detected; BTOIE disabled; BCLIE disabled; NACKIE disabled; 
    I2C1ERR = 0x0;
    // TXWE No error; RXRE No overflow; CLRBF Does not clear TX and RX Buffers; 
    I2C1STAT1 = 0x0;
    // CNTIF Byte count is not zero; ACKTIF Acknowledge sequence not detected; WRIF Data byte not detected; ADRIF Address not detected; PCIF Stop condition not detected; RSCIF Restart condition not detected; SCIF Start condition not detected; 
    I2C1PIR = 0x0;
    // CNTIE disabled; ACKTIE disabled; WRIE disabled; ADRIE disabled; PCIE disabled; RSCIE disabled; SCIE disabled; 
    I2C1PIE = 0x0;
    // CLK Fosc/4; 
    I2C1CLK = 0x0;
    // TOREC BTO event does not reset the I2C module; TOBY32 TOTIME*TBTOCLK*32; TOTIME 0x0; 
    I2C1BTO = 0x0;
    // BTOC TMR2 post scaled output; 
    I2C1BTOC = 0x1;
}
