/*
 * File:   main.c
 * Author: eriks
 *
 * Created on May 16, 2025, 9:00 AM
 */


// DSPIC33FJ12MC202 Configuration Bit Settings

// 'C' source line config statements

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (Watchdog timer always enabled)  //Was on 12-30-25

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// Define the register address to be modified
#define REG_ADDR_07 0x07

#include <xc.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "I2C_BQ24195L_register.h"

void init(void);
int i = 1, j = 0;
long int val0 = 0, val1 = 0, val2 = 0, val3 = 0, val4 = 0, val5 = 0, val6 = 0, val7 = 0;
void send(char*);
void int_to_char(int);
void send_char(char);
int read_ad7680(void);
void delay_ms(int);
int buf0 = 0;

void __attribute__((__interrupt__, auto_psv)) _ISR _DefaultInterrupt(void)
{   
    if(IFS0bits.AD1IF)
    {
        IFS0bits.AD1IF = 0;
        return;
    }
    else
        return;
}
/*
void __attribute__((__interrupt__, auto_psv )) _ISR _ReceiveInterrupt (void)
{ 
    /*
    if(IFS0bits.AD1IF)
    {
        IFS0bits.AD1IF = 0;
        buf0 = ADC1BUF8;
        int_to_char(buf0);
    }
    else
        return; 
     
    return;
}*/

/******************************************************************************
 * Function:  void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This serves the I2C Master Interrupt Service Routine.
 *****************************************************************************/
void __attribute__ ( (interrupt, no_auto_psv) ) _MI2C1Interrupt( void )
{
    IFS1bits.MI2C1IF = 0;   //Clear the Master I2C Interrupt Flag;
}

void main(void) {
    init();
    int adc_value = 0;
    char reg0 = 0;
    
 //   char newValue = 0x35; // Example value
 //   write_BQ24195L_register(REG_ADDR_07, newValue);
    
    while(1)
    { 
   //     adc_value = read_ad7680();
     //   if(adc_value > 0){
       //     int_to_char(adc_value);
        //}
     //   ack = I2C_Tx(BQ24195L_ADDR_WRITE);
      //  ack = I2C_Tx(reg0);
  //      send_char('a');
             //Pg 10 in max17048 datasheet. ADC Measurement of VCell
        reg0 = BQ24195L_ReadRegister(0x00);
        delay_ms(100);
        send_char(reg0);
        delay_ms(100);
      //  send_char(' ');
      //  delay_ms(100);
      //  send_char(' ');
      //  delay_ms(100);

    }
    return;
}