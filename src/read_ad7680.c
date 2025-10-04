/*
 * File:   read_ad7680.c
 * Author: Erik Sarkinen
 *
 * Created on Sept. 26, 2025 11:51am
 */

#include <xc.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//#define AD7680_CS_PIN PORTBbits.RB3
//#define AD7680_CS_TRIS TRISBbits.TRISB3

void delay_ms(int);

int read_ad7680(void)
{
    int received_data;
    
    // Pull /CS low to begin conversion
    //AD7680_CS_PIN = 0;
    PORTBbits.RB3 = 0;

    // A small delay might be needed here to ensure the ADC has
    // completed its track-and-hold acquisition. Refer to the datasheet.
  //  delay_ms(200);

    // Transmit a dummy 16-bit word to generate the clock and
    // receive the 16-bit data from the AD7680
    SPI1BUF = 0x0000; 

    // Wait until the receive buffer is full (transfer is complete)
    while (!SPI1STATbits.SPIRBF);

    // Read the received data
    received_data = SPI1BUF;

    // Pull /CS high to end the transaction
    //AD7680_CS_PIN = 1;
    PORTBbits.RB3 = 1;
    return received_data;
}
