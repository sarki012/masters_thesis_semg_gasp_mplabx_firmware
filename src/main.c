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
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog timer always enabled)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

#include <xc.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void init(void);
int i = 1, j = 0;
long int val0 = 0, val1 = 0, val2 = 0, val3 = 0, val4 = 0, val5 = 0, val6 = 0, val7 = 0;
void send(char*);
void int_to_char(int);
void send_char(char);
int read_ad7680(void);
int buf0 = 0;
char received_data = 0;

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

// UART1 Receive Interrupt Service Routine (ISR)
void __attribute__((__interrupt__, auto_psv)) _ISR _U1RXInterrupt(void) {
    // Check for errors (optional, but good practice)
    if (U1STAbits.OERR) {    // Check for Overrun Error
        U1STAbits.OERR = 0;  // Clear the OERR bit to reset the receive buffer
    }
    // Read the received data from the buffer
    // Reading U1RXREG automatically clears the URXDA flag
    received_data = U1RXREG;

    // Process the received data here (e.g., store in a buffer, respond)
    // ... your code ...

    // Clear the UART receive interrupt flag
    IFS0bits.U1RXIF = 0;     // MUST clear the interrupt flag, or the ISR will fire again immediately
}

void main(void) {
    init();
    int adc_value = 0;
    
    while(1)
    { 
        adc_value = read_ad7680();
        if(adc_value > 0){
            int_to_char(adc_value);
        }
        //delay_ms(200);
    }
    return;
}