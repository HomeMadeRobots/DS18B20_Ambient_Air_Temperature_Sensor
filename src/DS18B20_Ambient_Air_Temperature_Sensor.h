#ifndef DS18B20_AMBIENT_AIR_TEMPERATURE_SENSOR_H
#define DS18B20_AMBIENT_AIR_TEMPERATURE_SENSOR_H


/* Attributes */
#include "T_AMBIENT_AIR_TEMPERATURE.h"
#include "T_One_Wire_Device_Address.h"

/* Realized interfaces */
#include "i_Ambient_Air_Temperature.h"

/* Needed interfaces */
#include "i_One_Wire_Protocol.h"

/* Events */


class DS18B20_Ambient_Air_Temperature_Sensor : i_Ambient_Air_Temperature {
public :
    /*--------------------------------------------------------------------------------------------*/
    /* Constructor */
	DS18B20_Ambient_Air_Temperature_Sensor( void ) {}
	DS18B20_Ambient_Air_Temperature_Sensor( const T_One_Wire_Device_Address* a_device_address );
    void Connect_Ports( i_One_Wire_Protocol* a_one_wire_protocol);

    /*--------------------------------------------------------------------------------------------*/
    /* Component_Type_Operations */
	void Cyclic( void );

    /*--------------------------------------------------------------------------------------------*/
    /* Event reception points accessors */

    /*--------------------------------------------------------------------------------------------*/
    /* Provided port accessors */
	i_Ambient_Air_Temperature* Get_Port__Ambient_Air_Temperature( void );
	
	/*--------------------------------------------------------------------------------------------*/
    /* Provided operations */
    /* Ambient_Air_Temperature:i_Ambient_Air_Temperature */
	void Get_Temperature( T_AMBIENT_AIR_TEMPERATURE* temperature ) override;
	
private :
    /*--------------------------------------------------------------------------------------------*/
    /* Private attributes */
	typedef enum T_DS18B20_ACTION { CONVERT_TEMPERATURE, READ_SCRATCHPAD} T_DS18B20_ACTION;
	const T_One_Wire_Device_Address* Device_Address;
	T_AMBIENT_AIR_TEMPERATURE Air_Temperature = 0;
	T_DS18B20_ACTION Last_Performed_Action = READ_SCRATCHPAD;

    /*--------------------------------------------------------------------------------------------*/
    /* Private methods */

    /*--------------------------------------------------------------------------------------------*/
    /* Requirer_Ports */
	i_One_Wire_Protocol* One_Wire_Comm;

    /*--------------------------------------------------------------------------------------------*/
    /* Provider ports */

    /*--------------------------------------------------------------------------------------------*/
    /* Sent events */

    /*--------------------------------------------------------------------------------------------*/
    /* Received events */
};

#endif