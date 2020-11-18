#include "STD_TYPES.h"

#include "I2C_private.h"
#include "I2C_config.h"
#include "I2C_interface.h"


#define NULL 0


static slave_states state ;
static u8 Transmitt_BusyFlag=0;
static u8 slave_writemode =0;
static u8 slave_readmode =0;

static u8 i=0;
static void (*ptr0CallBack)(void)=NULL;


static struct t
{
	
	u8* Buffer;
	u8 size ;

	
	

}slave_buffer;


void I2C_initialSlave ( inital_slave *I2Cx)
{
	
	/*switch ( I2Cx -> Prescale)
	{

    case NORMALMODE : TWBR = 0x20;
	                  TWSR &=0xfc;break;
	case FASTMODE :   TWBR = 0x02;
                      TWSR &=0xfc;break;
    }*/
	
	
	if (I2Cx -> Interrupt == ENABLE_INTERRUPT)
	{
		  TWCR |=    0x01;
	}

	TWAR = I2Cx->Address;
	/* enable ack */
	TWCR |=0x40;

   /* enable operation */
     TWCR |=    0x04;

	                   
   }	
   
   
   u8 I2C_slaveWriteAsynchsen ( u8 * Copy_data ,u8 Copy_length )

	{
		u8 Local_status=0;
		if (Transmitt_BusyFlag ==0)
		{
			if ( Copy_data !=NULL && Copy_length !=0)
			{
			Transmitt_BusyFlag = 1;
			slave_writemode =  1;
		    slave_buffer.Buffer= Copy_data ;
		    slave_buffer.size  = Copy_length;
			state = add_receive;

			}else
			{
				Local_status=1;
			}
			
			
			
			
		}else
		{
		Local_status=1;
		}
		return Local_status;
		
			
	}
	
	
	  u8 I2C_slavereadAsynchsen ( u8 * Copy_data ,u8 Copy_length )

	{
		u8 Local_status=0;
		if (Transmitt_BusyFlag ==0)
		{
			if ( Copy_data !=NULL && Copy_length !=0)
			{
			Transmitt_BusyFlag = 1;
			slave_readmode =  1;
		    slave_buffer.Buffer= Copy_data ;
		    slave_buffer.size  = Copy_length;
			state = add_receive;

			}else
			{
				Local_status=1;
			}
			
			
			
			
		}else
		{
		Local_status=1;
		}
		return Local_status;
		
			
	}
	
	
void __vector_19 (void)__attribute__((signal));
void __vector_19 (void)
{


    
	 if ( slave_writemode ==1)
	 {
		  switch (state)
	{
		 case add_receive:
		 
		 state =ack_receive;

		  /*send data */
		  TWDR = slave_buffer.Buffer[i++];
		 /* enable twi operation */
		  TWCR |= 0x84;
	      break ;
		  
		  case  ack_receive:
		  if ( slave_buffer.size == i)
		  {
			  
			 i=0;
			Transmitt_BusyFlag = 0;
			slave_writemode=  0;
		    slave_buffer.Buffer= NULL;
		    ptr0CallBack();
		  }else
		  {
			  
			TWDR = slave_buffer.Buffer[i++];

		 /* enable twi operation */
		  TWCR |= 0x84;
			  
			  
		  }
		  break;
	}
 }
		 
		 else if ( slave_readmode ==1 )
		 {
			 
			 switch(state)
			 {
				case add_receive:
		 
					state =data_receive;


					/* enable twi operation */
					TWCR |= 0x84;
				break ;
		  
				case data_receive:
		  
				if ( slave_buffer.size == i)
				{
			  
					i=0;
				Transmitt_BusyFlag = 0;
				slave_readmode =  0;
				slave_buffer.Buffer= NULL;
				ptr0CallBack();
				}else
				{
				slave_buffer.Buffer[i++]= TWDR ;

				/* enable twi operation */
				TWCR |= 0x84;
				}
				break;
			 	 
			 
		 }
		 
}
		 
		 else
		 {

		 }
 
}
	
	
	
	
void callbkfn ( void (*p) (void))
{
	
	ptr0CallBack =p;
	
}
