/*
 * File:   int_to_char.c
 * Author: eriks
 *
 * Created on Jan 27, 2021, 8:48 AM
 */

#include <xc.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void send_char(char);

void int_to_char(int number)
{
    char d0 = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0;
    switch(number%10) {
        case 0 :
          d0 = '0';
          break;
        case 1 :
          d0 = '1';
          break;
        case 2 :
          d0 = '2';
          break;
        case 3 :
          d0 = '3';
          break;
        case 4 :
          d0 = '4';
          break;
        case 5 :
          d0 = '5';
          break;
        case 6 :
          d0 = '6';
          break;
        case 7 :
          d0 = '7';
          break;
        case 8 :
          d0 = '8';
          break;
        case 9 :
          d0 = '9';
          break;
        case 'x' :
          d0 = 'x';
          break;
        default : 
            d0 = '-';
    }
    number /= 10;
    switch(number%10) {
        case 0 :
          d1 = '0';
          break;
        case 1 :
          d1 = '1';
          break;
        case 2 :
          d1 = '2';
          break;
        case 3 :
          d1 = '3';
          break;
        case 4 :
          d1 = '4';
          break;
        case 5 :
          d1 = '5';
          break;
        case 6 :
          d1 = '6';
          break;
        case 7 :
          d1 = '7';
          break;
        case 8 :
          d1 = '8';
          break;
        case 9 :
          d1 = '9';
          break;
        case 'x' :
          d1 = 'x';
          break;
        default : 
            d1 = '-';
    }
    number /= 10;
    switch(number%10) {
        case 0 :
          d2 = '0';
          break;
        case 1 :
          d2 = '1';
          break;
        case 2 :
          d2 = '2';
          break;
        case 3 :
          d2 = '3';
          break;
        case 4 :
          d2 = '4';
          break;
        case 5 :
          d2 = '5';
          break;
        case 6 :
          d2 = '6';
          break;
        case 7 :
          d2 = '7';
          break;
        case 8 :
          d2 = '8';
          break;
        case 9 :
          d2 = '9';
          break;
        case 'x' :
          d2 = 'x';
          break;
        default : 
            d2 = '-';
    }
    number /= 10;
    switch(number%10) {
        case 0 :
          d3 = '0';
          break;
        case 1 :
          d3 = '1';
          break;
        case 2 :
          d3 = '2';
          break;
        case 3 :
          d3 = '3';
          break;
        case 4 :
          d3 = '4';
          break;
        case 5 :
          d3 = '5';
          break;
        case 6 :
          d3 = '6';
          break;
        case 7 :
          d3 = '7';
          break;
        case 8 :
          d3 = '8';
          break;
        case 9 :
          d3 = '9';
          break;
        case 'x' :
          d3 = 'x';
          break;
        default : 
            d3 = '-';
    }   
    number /= 10;
    switch(number) {
        case 0 :
          d4 = '0';
          break;
        case 1 :
          d4 = '1';
          break;
        case 2 :
          d4 = '2';
          break;
        case 3 :
          d4 = '3';
          break;
        case 4 :
          d4 = '4';
          break;
        case 5 :
          d4 = '5';
          break;
        case 6 :
          d4 = '6';
          break;
        case 7 :
          d4 = '7';
          break;
        case 8 :
          d4 = '8';
          break;
        case 9 :
          d4 = '9';
          break;
        case 'x' :
          d4 = 'x';
          break;
        default : 
            d4 = '-';
    }
        
    send_char('a');
    send_char(d4);
    send_char(d3);
    send_char(d2);
    send_char(d1);
    send_char(d0);

 //   delay_ms(100);

    return;
}