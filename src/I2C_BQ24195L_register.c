/* 
 * File: read_write_BQ24195L_register.h
 * Author: Erik Sarkinen
 * 
 * Created on Jan. 5, 2026 12:11am
 * 
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "I2C_BQ24195L_register.h"

// Define the 7-bit I2C address of the BQ24195L
#define BQ24195L_ADDR_7BIT 0x6B
// The full 8-bit addresses for Write (0) and Read (1) operations
#define BQ24195L_ADDR_WRITE ((BQ24195L_ADDR_7BIT << 1) & 0xFE)      //0 = write
#define BQ24195L_ADDR_READ  ((BQ24195L_ADDR_7BIT << 1) | 0x01)      //1 = read

// Function to wait for the I2C module to be ready
void I2C_MasterWait(void) {
    // Wait until the I2C bus is idle and the module is not performing a command (Start, Stop, etc)
    while (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
    return;
}

// Function to send a Start condition
void I2C_Start(void) {
    I2C_MasterWait();
    I2C1CONbits.SEN = 1; // Initiate Start 
    //I2C_MasterWait();
    // while (I2C1CONbits.SEN); // Wait for Start condition to complete
    return;
}

// Function to send a Repeated Start condition
void I2C_RepeatedStart(void) {
    I2C_MasterWait();
    I2C1CONbits.RSEN = 1; // Initiate Repeated Start condition
    //I2C_MasterWait();
 //   while (I2C1CONbits.RSEN); // Wait for Repeated Start to complete
    return;
}

// Function to send a Stop condition
void I2C_Stop(void) {
    I2C_MasterWait();
    I2C1CONbits.PEN = 1; // Initiate Stop condition
    //I2C_MasterWait();
    //while (I2C1CONbits.PEN); // Wait for Stop condition to complete
    return;
}

// Function to transmit a byte and check for acknowledgment
char I2C_Tx(char data) {
    I2C_MasterWait();
    I2C1TRN = data; // Load data into the transmit register
    //I2C_MasterWait();
    while (I2C1STATbits.TRSTAT); // Wait for transmission to finish
    // Check for Acknowledge from the slave
//    if (I2C1STATbits.ACKSTAT) {
        // NACK received, handle error (e.g., return an error code)
  //      return 0;       //Was 0 
    //}
    return 1; // ACK received
}

// Function to receive a byte (master receives)
char I2C_Rx(char ack) {
    I2C_MasterWait();
    I2C1CONbits.RCEN = 1; // Enable receive mode
    while (!I2C1STATbits.RBF); // Wait for receive buffer to be full
    char data = I2C1RCV; // Read the received data
    // Send ACK or NACK after receiving the byte
    I2C1CONbits.ACKDT = 0; // 0 for ACK, 1 for NACK
  //  I2C1CONbits.ACKDT = (ack ? 0 : 1); // 0 for ACK, 1 for NACK
    I2C1CONbits.ACKEN = 1; // Send the Acknowledge signal
    while (I2C1CONbits.ACKEN); // Wait for the acknowledge sequence to complete
    return data;
}

/**
 * @brief Reads a single byte from a specified register of the BQ24195L
 * 
 * @param reg_address The internal register address (8-bit)
 * @return The 8-bit data from the register, or 0xFF on error (simple error handling)
 */
char BQ24195L_ReadRegister(char reg_address) {
    char data = 0x34; // Default error value
    // 1. Send Start condition
    I2C_Start();
    // 2. Send device address with Write bit (0)
    //if (!I2C_Tx(BQ24195L_ADDR_WRITE)) {
  //For PMIC, use:  if (!I2C_Tx(0xD6)) {
    //For PMIC use: if(!I2C_Tx(0xD7)) {
    
    // If using 0x6C and 0x6D shifted to the left one bit, 
    // write = 0xD8, read = oxDA
    //
    if (!I2C_Tx(BQ24195L_ADDR_WRITE)) {    //For fuel gauge, was 0xD8 then 0x6C       
        I2C_Stop();
        return data;
    }
    // 3. Send the internal register address
    if (!I2C_Tx(reg_address)) {
        I2C_Stop();
        return data;
    }
    
    // 4. Send Repeated Start condition
    I2C_RepeatedStart();
    // 5. Send device address with Read bit (1)
   // if (!I2C_Tx(BQ24195L_ADDR_READ)) {
    if(!I2C_Tx(BQ24195L_ADDR_READ)) {         //For fuel gauge, was 0xDA then 0x6D
        I2C_Stop();
        return data;
    }

    // 6. Read data byte from the slave
    // Send NACK after the single byte read to indicate end of transfer
    data = I2C_Rx(0); // 0 for NACK

    // 7. Send Stop condition
    I2C_Stop();

    return data;
}

// Note: I2C1 module must be initialized separately (setting I2C1CON and I2C1BRG registers).
