#include "DS18B20_Ambient_Air_Temperature_Sensor.h"

#include "string.h"

#define READ_SCRATCHPAD_CMD 0xBE
#define CONVERT_TEMPERATURE_CMD 0x44

/**************************************************************************************************/
/* Constructor */
DS18B20_Ambient_Air_Temperature_Sensor::DS18B20_Ambient_Air_Temperature_Sensor( 
	i_One_Wire_Protocol* a_one_wire_protocol,
	const T_One_Wire_Device_Address* a_device_address )
{
	this->One_Wire_Comm = a_one_wire_protocol;
	this->Device_Address = a_device_address;
}
/**************************************************************************************************/


/**************************************************************************************************/
/* Component_Type_Operations */
/**************************************************************************************************/
void DS18B20_Ambient_Air_Temperature_Sensor::Cyclic( void )
{
	/* Check Last_Performed_Action */
	if( this->Last_Performed_Action == READ_SCRATCHPAD )
	{
		/* Request temperature conversion */
		this->One_Wire_Comm->Send_Simple_Command( this->Device_Address, CONVERT_TEMPERATURE_CMD );
		
		/* Update Last_Performed_Action */
		this->Last_Performed_Action = CONVERT_TEMPERATURE;
		
	}
	else if( this->Last_Performed_Action == CONVERT_TEMPERATURE )
	{
		/* Read scratchpad */
		uint8_t read_bytes[2] = {0};
		this->One_Wire_Comm->Send_Read_Command( 
			this->Device_Address, READ_SCRATCHPAD_CMD, read_bytes, 2 );
		
		/* Convert read bytes into temperature */
		this->Air_Temperature = read_bytes[0] | ( (read_bytes[1] & 0b10000111 ) <<8 );
		
		/* Update Last_Performed_Action */
		this->Last_Performed_Action = READ_SCRATCHPAD;
	}
}
/**************************************************************************************************/


/**************************************************************************************************/
/* Event reception points accessors */
/**************************************************************************************************/


/**************************************************************************************************/
/* Prodided port accessors */
/**************************************************************************************************/
i_Ambient_Air_Temperature* DS18B20_Ambient_Air_Temperature_Sensor::
	Get_Port__Ambient_Air_Temperature( void )
{
    return (i_Ambient_Air_Temperature*)(this);
}
/**************************************************************************************************/


/**************************************************************************************************/
/* Private methods */
/**************************************************************************************************/


/**************************************************************************************************/
/* Provided operations */
/**************************************************************************************************/
void DS18B20_Ambient_Air_Temperature_Sensor::Get_Temperature(
	T_AMBIENT_AIR_TEMPERATURE* temperature )
{
	*temperature = this->Air_Temperature;
}
/**************************************************************************************************/


/**************************************************************************************************/
/* Received events */
/**************************************************************************************************/