/*
 * File:   send_char.c
 * Author: eriks
 *
 * Created on Jan 27, 2021, 9:14 AM
 */

#include <xc.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void send_char(char letter)
{
    int j = 0;
    U1TXREG = letter;
    while(!U1STAbits.TRMT);
    for(j = 0; j < 100; j++);

    return;
}