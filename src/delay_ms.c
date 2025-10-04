/*
 * File:   delay_ms.c
 * Author: eriks
 *
 * Created on July 1st 2025, 11:33 AM
 */

#include <xc.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void delay_ms(int num_ms) {
    long int num_loops;
    num_loops = 2*(num_ms/1000)*368500;
    for(long int i = 0; i < num_loops; i++);
    return;
}

/*
 All instructions execute in a single cycle,
with the exception of instructions that change the
program flow, the double-word move (MOV.D)
instruction and the table instructions pg. 13
 */