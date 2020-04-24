#ifndef DS18B20_AMBIENT_AIR_TEMPERATURE_SENSOR_H
#define DS18B20_AMBIENT_AIR_TEMPERATURE_SENSOR_H


/*============================================================================*/
/* Inclusions */
/*============================================================================*/
/* Attributes */
#include "T_Ambient_Air_Temperature.h"
#include "T_One_Wire_Device_Address.h"


/* Realized interfaces */
#include "Ambient_Air_Temperature.h"


/* Required interfaces */
#include "One_Wire_Protocol.h"


/*============================================================================*/
/* Types, interfaces and macros */
/*============================================================================*/
#define DS18B20_ACTION_CONVERT_TEMPERATURE  0
#define DS18B20_ACTION_READ_SCRATCHPAD      1


/*============================================================================*/
/* Component_Type */
/*============================================================================*/
typedef struct {
    T_Ambient_Air_Temperature Air_Temperature;
    uint8_t Last_Performed_Action;
} DS18B20_Ambient_Air_Temperature_Sensor_Var;

typedef struct {

    /* Variable attributes */
    DS18B20_Ambient_Air_Temperature_Sensor_Var* var_attr;

    /* Required interfaces */
    const One_Wire_Protocol* One_Wire_Comm;
    
    /* Configuration_Parameters */
    T_One_Wire_Device_Address Device_Address;
    
} DS18B20_Ambient_Air_Temperature_Sensor;


/*============================================================================*/
/* Component_Operations */
/*============================================================================*/
void DS18B20__Cyclic( const DS18B20_Ambient_Air_Temperature_Sensor* Me );


/*============================================================================*/
/* Realized interfaces */
/*============================================================================*/
void DS18B20__Ambient_Air_Temperature__Get_Temperature(
    const DS18B20_Ambient_Air_Temperature_Sensor* Me,
    T_Ambient_Air_Temperature* temperature );

#endif