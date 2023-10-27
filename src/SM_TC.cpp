extern "C" {
#include <inttypes.h>
}

#include "Arduino.h"
#include "Wire.h"
#include "SM_TC.h"

SM_TC::SM_TC(uint8_t stack)
{
	if (stack > 7)
		stack = 7;
	_hwAdd = SLAVE_OWN_ADDRESS_BASE + stack;
	_detected = false;
}

bool SM_TC::begin()
{
	uint8_t value = 0;
	Wire.begin();
	if (0 == readByte(REVISION_MAJOR_MEM_ADD, &value))
	{
		_detected = true;
	}
	return _detected;
}

bool SM_TC::isAlive()
{
	return _detected;
}

bool SM_TC::setType(uint8_t channel, uint8_t type)
{
	if (channel > TC_CHANNEL_NR_MAX || channel == 0)
	{
		return false;
	}
	if(type > TC_TYPE_T)
	{
		return false;
	}
	if(OK != writeByte(TCP_TYPE1 + channel -1, type))
	{
		return false;
	}
	return true;
}

float SM_TC::readTemp(uint8_t channel)
{
	int16_t val = 0;
	
	if (channel > TC_CHANNEL_NR_MAX || channel == 0)
	{
		return (float)-1000;
	}

	if (OK != readInt16(TCP_VAL1_ADD + TEMP_DATA_SIZE * (channel -1), &val))
	{
		return (float)-1001;
	}
	return (float)val / TEMP_SCALE_FACTOR;
}


float SM_TC::readVolt(uint8_t channel)
{
	int16_t val = 0;
	
	if (channel > TC_CHANNEL_NR_MAX || channel == 0)
	{
		return (float)-1000;
	}

	if (OK != readInt16(TCP_MV1_ADD + MV_DATA_SIZE * (channel -1), &val))
	{
		return (float)-1002;
	}
	return (float)val / MV_SCALE_FACTOR;
}


/*
 ***************** RTD_I2C access functions ****************************
 **********************************************************************
 */
int SM_TC::writeByte(uint8_t add, uint8_t value)
{
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(value);
	return Wire.endTransmission();
}


int SM_TC::readByte(uint8_t add, uint8_t *value)
{
	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)1);
	if (1 <= Wire.available())
	{
		*value = Wire.read();
	}
	else
	{
		return -1;
	}
	return 0;
}


int SM_TC::readInt16(uint8_t add, int16_t *value)
{
	uint8_t buff[2];
	int i = 0;

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (2 <= Wire.available())
	{
		for (i = 0; i < 2; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 2);
	return 0;
}