/*
 * main.c
 *
 *  Created on: May 22, 2019
 *      Author: Mohamed osama
 */

#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "Delay.h"
#include "DIO_interface.h"
#define SREG   *((u8*)0x5f)
#include "I2C_private.h"
#include "I2C_interface.h"

u8 arr [5];

void callfn(void)
{
	DIO_u8SetPinValue (0,1);

}

void main ()
{

	DIO_u8SetPinDir (0 ,1);
	DIO_u8SetPinDir (1 ,1);
	DIO_u8SetPinValue (0,0);
	DIO_u8SetPinValue (1,0);
	SREG  |=0x80;
	inital_slave slv ={NORMALMODE, 0xfe,ENABLE_INTERRUPT};
	I2C_initialSlave ( &slv);
	callbkfn (callfn );

	I2C_slavereadAsynchsen ( arr ,5);
	while(1)
	{
        if ( arr[4]== 0x65)
        {

        	DIO_u8SetPinValue (1,1);
        }
       }

	}




