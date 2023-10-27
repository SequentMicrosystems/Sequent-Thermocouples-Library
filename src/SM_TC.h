/*!
 * @file SM_TC.h
 * 
 * Designed specifically to work with the Sequent Microsysatems 
 * TC Data Acquisition 8-Layer Stackable HAT for Raspberry Pi
 * 
 * ----> https://sequentmicrosystems.com/products/eight-thermocouples-daq-8-layer-stackable-hat-for-raspberry-pi
 * 
 *   This card use I2C to communicate.
 *   
 *   Written by Alexandru Burcea for Sequent Microsystems
 * 
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2023, Sequent Microsystems 
 *  
 */
#ifndef __SM_TC__
#define __SM_TC__

#define TC_CHANNEL_NR_MIN		1
#define TC_CHANNEL_NR_MAX		8

#define TEMP_DATA_SIZE 2
#define MV_DATA_SIZE 2
#define TEMP_SCALE_FACTOR ((float)10)
#define MV_SCALE_FACTOR ((float)100)

#define OK 0

#define SLAVE_OWN_ADDRESS_BASE 0x16

enum
{
	TCP_VAL1_ADD = 0,
	TCP_VAL2_ADD = TCP_VAL1_ADD + TEMP_DATA_SIZE,
	TCP_VAL3_ADD = TCP_VAL2_ADD + TEMP_DATA_SIZE,
	TCP_VAL4_ADD = TCP_VAL3_ADD + TEMP_DATA_SIZE,
	TCP_VAL5_ADD = TCP_VAL4_ADD + TEMP_DATA_SIZE,
	TCP_VAL6_ADD = TCP_VAL5_ADD + TEMP_DATA_SIZE,
	TCP_VAL7_ADD = TCP_VAL6_ADD + TEMP_DATA_SIZE,
	TCP_VAL8_ADD = TCP_VAL7_ADD + TEMP_DATA_SIZE,
	TCP_TYPE1 = TCP_VAL8_ADD + TEMP_DATA_SIZE,
	TCP_TYPE2,
	TCP_TYPE3,
	TCP_TYPE4,
	TCP_TYPE5,
	TCP_TYPE6,
	TCP_TYPE7,
	TCP_TYPE8,
	DIAG_TEMPERATURE_MEM_ADD,
	DIAG_5V_MEM_ADD,
	I2C_MEM_WDT_RESET_ADD = DIAG_5V_MEM_ADD + 2,
	I2C_MEM_WDT_INTERVAL_SET_ADD,
	I2C_MEM_WDT_INTERVAL_GET_ADD = I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = I2C_MEM_WDT_INIT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_RESET_COUNT_ADD = I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = I2C_MEM_WDT_RESET_COUNT_ADD + 2,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD + 4,
	REVISION_HW_MAJOR_MEM_ADD  = I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD + 4,
	REVISION_HW_MINOR_MEM_ADD,
	REVISION_MAJOR_MEM_ADD,
	REVISION_MINOR_MEM_ADD,

	TCP_MV1_ADD,
	TCP_MV2_ADD = TCP_MV1_ADD + MV_DATA_SIZE,
	TCP_MV3_ADD = TCP_MV2_ADD + MV_DATA_SIZE,
	TCP_MV4_ADD = TCP_MV3_ADD + MV_DATA_SIZE,
	TCP_MV5_ADD = TCP_MV4_ADD + MV_DATA_SIZE,
	TCP_MV6_ADD = TCP_MV5_ADD + MV_DATA_SIZE,
	TCP_MV7_ADD = TCP_MV6_ADD + MV_DATA_SIZE,
	TCP_MV8_ADD = TCP_MV7_ADD + MV_DATA_SIZE,
	TCP_REINIT_COUNT = TCP_MV8_ADD + MV_DATA_SIZE,
	TCP_SPS1_ADD = TCP_REINIT_COUNT + 4,
	TCP_SPS2_ADD = TCP_SPS1_ADD + 2,
	TCP_CARD_TYPE = TCP_SPS2_ADD+2,
	TCP_RASP_VOLT,
	I2C_MODBUS_SETINGS_ADD = TCP_RASP_VOLT + 2, //5 bytes
	TCP_LEDS_FUNC = I2C_MODBUS_SETINGS_ADD + 5, //2 bytes
	TCP_LED_THRESHOLD1 = TCP_LEDS_FUNC + 2,
	TCP_LED_THRESHOLD2 = TCP_LED_THRESHOLD1 + 2,
	TCP_LED_THRESHOLD3 = TCP_LED_THRESHOLD2 + 2,
	TCP_LED_THRESHOLD4 = TCP_LED_THRESHOLD3 + 2,
	TCP_LED_THRESHOLD5 = TCP_LED_THRESHOLD4 + 2,
	TCP_LED_THRESHOLD6 = TCP_LED_THRESHOLD5 + 2,
	TCP_LED_THRESHOLD7 = TCP_LED_THRESHOLD6 + 2,
	TCP_LED_THRESHOLD8 = TCP_LED_THRESHOLD7 + 2,
	I2C_CALIB_RES = TCP_LED_THRESHOLD8 + 2,//float
	I2C_CALIB_CH = I2C_CALIB_RES + 4,//u8
	I2C_SENSORS_TYPE,
	I2C_MEM_ADS_SAMPLE_SWITCH,//u16

	I2C_THERMISTOR1_ADD = I2C_MEM_ADS_SAMPLE_SWITCH + 2,

	I2C_THERMISTOR_END_ADD = I2C_THERMISTOR1_ADD + 20,

	SLAVE_BUFF_SIZE = 0xff

};

typedef enum {
	TC_TYPE_B = 0,
	TC_TYPE_E,
	TC_TYPE_J,
	TC_TYPE_K,
	TC_TYPE_N,
	TC_TYPE_R,
	TC_TYPE_S,
	TC_TYPE_T,
}ThermocoupleType;


/*!
 * @brief SM_TC class
 */
class SM_TC
{
public:
	/*!
	 * @brief Class constructor.
	 */
	SM_TC(uint8_t stack = 0);

	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existance status
	 * @return Returns true if card is present
	 */
	bool isAlive();

	
	/*!
	 * @brief Get one TC channel temperature in deg Celsious
	 * @param channel - the desired channel 1..8
	 * @return Returns the temperature
	 */
	float readTemp(uint8_t channel);
	
	
	/*!
	 * @brief Get one TC channel sensor voltage
	 * @param channel - the desired channel 1..8
	 * @return Returns the voltage in mV
	 */
	float readVolt(uint8_t channel);
	
	
	/*!
	 * @brief Set one TC channel sensor type
	 * @param channel - the desired channel 1..8
	 * @param type - thermocouple type B=0; E=1; J=2; K=3; N=4; R=5; S=6; T=7;
	 * @return Returns true is successful
	 */
	bool setType(uint8_t channel, uint8_t type);

private:
	uint8_t _hwAdd;
	bool _detected;
	int writeByte(uint8_t add, uint8_t value);
	int readByte(uint8_t add, uint8_t* value);
	int readInt16(uint8_t add, int16_t *value);
};

#endif //__SM_TC__
