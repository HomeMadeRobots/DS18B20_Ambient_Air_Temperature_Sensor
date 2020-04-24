#include "DS18B20_Ambient_Air_Temperature_Sensor.h"


/*============================================================================*/
/* Types, Macros */
/*============================================================================*/
#define READ_SCRATCHPAD_CMD 0xBE
#define CONVERT_TEMPERATURE_CMD 0x44


/*============================================================================*/
/* Attributes access */
/*============================================================================*/
#define My_Air_Temperature (Me->var_attr->Air_Temperature)
#define My_Last_Performed_Action (Me->var_attr->Last_Performed_Action)


/*============================================================================*/
/* Required interfaces access */
/*============================================================================*/
#define One_Wire_Comm__Send_Simple_Command( addr, cmd ) \
        Me->One_Wire_Comm->Send_Simple_Command( addr, cmd )
#define One_Wire_Comm__Send_Read_Command( addr, cmd, b, nb ) \
        Me->One_Wire_Comm->Send_Read_Command( addr, cmd, b, nb )
        

/*============================================================================*/
/* Component_Operations */
/*============================================================================*/
void DS18B20__Cyclic( const DS18B20_Ambient_Air_Temperature_Sensor* Me )
{
	/* Check Last_Performed_Action */
	if( DS18B20_ACTION_READ_SCRATCHPAD==My_Last_Performed_Action )
	{
		/* Request temperature conversion */
		One_Wire_Comm__Send_Simple_Command( 
            &(Me->Device_Address),
            CONVERT_TEMPERATURE_CMD );
		
		/* Update Last_Performed_Action */
		My_Last_Performed_Action = DS18B20_ACTION_CONVERT_TEMPERATURE;
		
	}
	else if( DS18B20_ACTION_CONVERT_TEMPERATURE==My_Last_Performed_Action )
	{
		/* Read scratchpad */
		uint8_t read_bytes[2] = {0};
		One_Wire_Comm__Send_Read_Command( 
			&(Me->Device_Address),
            READ_SCRATCHPAD_CMD,
            read_bytes,
            2 );
		
		/* Convert read bytes into temperature */
		My_Air_Temperature =     read_bytes[0] 
                            | ( (read_bytes[1] & 0b10000111 ) <<8 );
		
		/* Update Last_Performed_Action */
		My_Last_Performed_Action = DS18B20_ACTION_READ_SCRATCHPAD;
	}
    else
    { /* RAM corruption */
        /* Robustness */
        My_Last_Performed_Action = DS18B20_ACTION_CONVERT_TEMPERATURE;
    }
}


/*============================================================================*/
/* Realized interfaces */
/*============================================================================*/
void DS18B20__Ambient_Air_Temperature__Get_Temperature(
    const DS18B20_Ambient_Air_Temperature_Sensor* Me,
    T_Ambient_Air_Temperature* temperature )
{
    *temperature = My_Air_Temperature;
}