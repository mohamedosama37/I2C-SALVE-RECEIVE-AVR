#ifndef I2C_interface_h
#define I2C_interface_h

#define NORMALMODE  0
#define FASTMODE    1
#define FASTMODEPLUS 2
#define HIGH_SPEED   3

#define ENABLE_INTERRUPT 1






void I2C_initialSlave ( inital_slave * I2Cx);
u8 I2C_slaveWriteAsynchsen ( u8 * Copy_data ,u8 Copy_length );

u8 I2C_slavereadAsynchsen ( u8 * Copy_data ,u8 Copy_length );
void callbkfn ( void (*p) (void));




#endif
