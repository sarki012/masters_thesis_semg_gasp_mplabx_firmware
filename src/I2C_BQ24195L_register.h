/* 
 * File: read_write_BQ24195L_register.h
 * Author: Erik Sarkinen
 * 
 * Created on Jan. 5, 2026 12:11am
 * 
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdio.h>
#include <p33fj12mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void I2C_MasterWait(void);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_Stop(void);
char I2C_Tx(char);
char I2C_Rx(char);
char BQ24195L_ReadRegister(char);

