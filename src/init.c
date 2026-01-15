/*
 * File:   init.c
 * Author: Erik Sarkinen
 *
 * Created on Dec. 24, 2020 10:42am
 */

#include <xc.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void delay_ms(int);

void init(void)
{
    RPOR1 = 0b0000100100001000;     //SCK1OUT = RP2, CS = RP3
    RPINR20 = 0b0001111100000100;     //SCKIN = VSS, SDI1 = RP4
    RPINR18 = 0b0001111100001100;       //UART1 CTS = VSS, UART1 RX = RP 12
    RPOR7 = 0b0000001100000000;         //UART1 TX = RP15, RP14 TIED TO DEFAULT PORT PIN
    RPINR0 = 0b0000110100000000;       //INT1 = RP13
    
    TRISBbits.TRISB2 = 0;       //SPI SCK1OUT
    TRISBbits.TRISB3 = 0;       //SPI CS
    TRISBbits.TRISB4 = 1;       //SPI SDI
    TRISBbits.TRISB5 = 0;       //Bluetooth Wakeup
    TRISBbits.TRISB6 = 0;       //Bluetooth Reset
    TRISBbits.TRISB7 = 1;       //INT0
    TRISBbits.TRISB8 = 1;       //I2C SCL1
    TRISBbits.TRISB9 = 1;       //I2C SDA1
    TRISBbits.TRISB10 = 0;      //Bluetooth SW Button
    TRISBbits.TRISB11 = 0;      //Bluetooth P2_0
    TRISBbits.TRISB12 = 1;      //UART1 RX
    TRISBbits.TRISB13 = 1;      //INT1
    TRISBbits.TRISB14 = 0;      //Bluetooth EAN
    TRISBbits.TRISB15 = 0;      //UART1 TX
    
  //  TRISAbits.TRISA0 = 0;       //Gain Relay Control
    TRISAbits.TRISA1 = 1;       //Gain Resistor ADC
    TRISAbits.TRISA2 = 0;       //Bluetooth P2_4
    TRISAbits.TRISA3 = 0;       //PMIC Charge Enable (Active Low)
  //  TRISAbits.TRISA4 = 0;       //Relay 3V3
    
    ODCBbits.ODCB8 = 1;         //I2C SCL1 Open Drain Config.
    ODCBbits.ODCB9 = 1;         //I2C SDA1 Open Drain Config.
    
   // LATAbits.LATA0 = 0;         //Gain Relay Control Normal mode
    LATAbits.LATA3 = 0;         //PMIC Charge Enable (Active Low)
    
    LATBbits.LATB10 = 0;        //SW Button
    LATBbits.LATB6 = 0;        //Reset
    
    //Set up Bluetooth  EEPROM programming   Normal
    LATBbits.LATB14 = 1;     //EAN  1           1
    LATAbits.LATA2 = 1;     //P2_4 1           1 
    LATBbits.LATB11 = 1;    //P2_0 0           1
 
    
    LATBbits.LATB6 = 1;
    delay_ms(1);
    LATBbits.LATB6 = 0;     //Reset (active low)
    delay_ms(1);
    LATBbits.LATB6 = 1;
   
    
    LATBbits.LATB10 = 1;        //SW Button
    delay_ms(40);
    LATBbits.LATB6 = 1;        //Reset
//    delay_ms(500);
    delay_ms(500);
   // LATBbits.LATB10 = 1;        //SW Button
      
    U1MODEbits.UARTEN = 1;      //UART1 is enabled
    U1MODEbits.USIDL = 0;       //Continue module operation in Idle mode
    U1MODEbits.IREN = 0;        //IrDA encoder and decoder disabled
    U1MODEbits.RTSMD = 0;       //U1RTS pin in flow control mode
    U1MODEbits.UEN1 = 1;    
    U1MODEbits.UEN0 = 1;        //TX RX and BCLK pins are enabled and used, /CTS pin controlled by port latches *****DOUBLE CHECK
    U1MODEbits.WAKE = 1;
    U1MODEbits.LPBACK = 0;
    U1MODEbits.ABAUD = 0;
    U1MODEbits.URXINV = 0;      //Idle state is '0'
    U1MODEbits.BRGH = 1;        //High Speed
    U1MODEbits.PDSEL1 = 0;
    U1MODEbits.PDSEL0 = 0;      //8-bit data, no parity
    U1MODEbits.STSEL = 0;       //One stop bit
    
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXISEL0 = 1;     //Interrupt when the last character is shifted out of the Transmit Shift Register ****Double Check
    U1STAbits.UTXINV = 0;       //Idle State is 0
    U1STAbits.UTXBRK = 0;       //Sync Break transmission disabled or completed
    U1STAbits.UTXEN = 1;        //Transmit enabled
    U1STAbits.URXISEL1 = 0;
    U1STAbits.URXISEL0 = 0;     //Interrupt is set on when one char is in the buffer
    U1STAbits.ADDEN = 0;          //Address detect mode disabled
    U1STAbits.RIDLE = 0;        //Receiver is active
    U1STAbits.PERR = 0;         //Parity Error
    
    OSCCON = 0b0000000011000000;    //FRC 7.37 MHz
    U1BRG = 7;                      //BAUD RATE 115,200
 //   U1BRG = 95;                      //BAUD RATE 9,600
    
    IEC0bits.U1TXIE = 0;        //No transmit interrupt (We poll TRMT)
   
    LATBbits.LATB10 = 1;        //SW Button
    LATBbits.LATB5 = 0;         //Wakeup
    
    ///////////////// SPI Config ///////////////////////////////////////////
    SPI1STATbits.SPIEN = 0;     //Disable SPI
    SPI1STATbits.SPISIDL = 0;   //Continue module operation in idle mode
    SPI1CON1bits.DISSCK = 0;    //Internal SPI clock is enabled
    SPI1CON1bits.DISSDO = 1;    //SDO1 pin is not used by module; pin functions as I/O
    SPI1CON1bits.MODE16 = 1;    //Communication is word-wide (16 bits)
    SPI1CON1bits.SMP = 1;       //Input data sampled at end of data output time ***try both ways
    SPI1CON1bits.CKP = 0;       //Idle state for clock is a low level; active state is a high level ***try both ways
    SPI1CON1bits.MSTEN = 1;     //Master mode
    SPI1CON1bits.SPRE = 010;    //Secondary prescale 6:1
    SPI1CON1bits.PPRE = 00;     //Primary prescale 64:1
    
    SPI1CON2 = 0x0000; // Standard buffer mode, no framed SPI
    
    PORTBbits.RB3 = 1;        //De-select the AD7680 (active low)
    
    SPI1STATbits.SPIEN = 1;     //Enable SPI
    //////////////// End of SPI Config /////////////////////////////////////
    
    
  //  IEC0bits.U1RXIE = 1;        //UART receive interrupt enabled
   // IPC2bits.U1RXIP2 = 1;
   // IPC2bits.U1RXIP1 = 1;
   // IPC2bits.U1RXIP0 = 1;       //Highest priority
    
    /*
    //A -> D Setup
    AD1CON1bits.ADON = 0;   //ADC is disabled
    AD1CON1bits.ADSIDL = 0; //Continue operation in idle mode
    AD1CON1bits.AD12B = 0;  //10 bit
    AD1CON1bits.FORM0 = 0;
    AD1CON1bits.FORM1 = 0;  //Integer
    AD1CON1bits.SSRC0 = 1;
    AD1CON1bits.SSRC1 = 1;
    AD1CON1bits.SSRC2 = 1;  //Internal counter ends sampling and starts conversion (auto-convert)
    AD1CON1bits.ASAM = 1;   //Sampling begins immediately after last conversion
    AD1CON1bits.SAMP = 1;   //ADC sample enable bit
    
    AD1CON2bits.VCFG0 = 0;
    AD1CON2bits.VCFG1 = 0;
    AD1CON2bits.VCFG2 = 0;      //Voltage reference AVDD and AVSS
   // AD1CON2bits.CSCNA = 1;      //Scan inputs
    AD1CON2bits.CHPS0 = 0;
    AD1CON2bits.CHPS1 = 0;      //Converts CH0
    AD1CON2bits.BUFM = 0;       //Always starts filling buffer from beginning
    AD1CON2bits.SMPI0 = 1;
    AD1CON2bits.SMPI1 = 1;
    AD1CON2bits.SMPI2 = 1;
    AD1CON2bits.SMPI3 = 1;      //Interrupts at the completion of 16th conversion
    AD1CON2bits.ALTS = 0;       //Always uses channel input selects for sample A
    
    TRISAbits.TRISA0 = 1;       //Input
    AD1PCFGL = 0x0000;
    AD1CON3bits.ADRC = 1;       //ADC internal RC clock
    
 //   AD1CON3bits.SAMC = 0b00000;
  //  AD1CON3bits.ADCS = 0b000000;
    
    AD1CHS0bits.CH0SB0 = 0;
    AD1CHS0bits.CH0SB1 = 0;
    AD1CHS0bits.CH0SB2 = 0;
    AD1CHS0bits.CH0SB3 = 0;
    AD1CHS0bits.CH0SB4 = 0;
    
    AD1CHS0bits.CH0SA0 = 0;
    AD1CHS0bits.CH0SA1 = 0;
    AD1CHS0bits.CH0SA2 = 0;
    AD1CHS0bits.CH0SA3 = 0;
    AD1CHS0bits.CH0SA4 = 0;
    
    IEC0bits.AD1IE = 1;         //Interrupt request enabled
    IPC3bits.AD1IP0 = 0;
    IPC3bits.AD1IP1 = 1;
    IPC3bits.AD1IP2 = 1;        //Priority = 6   
    
    AD1CON1bits.ADON = 1;   //ADC is enabled
    
     */ 
    return;
}