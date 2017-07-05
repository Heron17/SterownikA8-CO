#include <avr/io.h>
#include <util/delay.h>
#include "ds18b20_3.h"
unsigned char ds18b20_ConvertT_3(void)
{
	if (!OneWireReset_3()) return 0;
	OneWireWriteByte_3(0xcc);
	OneWireWriteByte_3(0x44);
	return 1;
}
int ds18b20_Read_3(unsigned char scratchpad[])
{
	unsigned char i;
	if (!OneWireReset_3()) return 0;
	OneWireWriteByte_3(0xcc); 
	OneWireWriteByte_3(0xbe);
	for(i=0; i<9; i++) scratchpad[i] = OneWireReadByte_3();
	return 1;
}
void OneWireStrong_3(char s)
{
	if (s)
	{
		SET_ONEWIRE_PORT;
		SET_OUT_ONEWIRE_DDR;
	}
	else
	{
		SET_IN_ONEWIRE_DDR;
	}
}
unsigned char OneWireReset_3()
{
	CLR_ONEWIRE_PORT;
	if (!(IS_SET_ONEWIRE_PIN)) return 0;
	SET_OUT_ONEWIRE_DDR;
	_delay_us(500);
	SET_IN_ONEWIRE_DDR;
	_delay_us(70);
	if(!(IS_SET_ONEWIRE_PIN))
	{
		_delay_us(500);
		return(1);
	}
	_delay_us(500);
	return(0);
}
void OneWireWriteByte_3(unsigned char byte)
{
	unsigned char i;
	CLR_ONEWIRE_PORT;
	for (i=0; i<8; i++)
	{
		SET_OUT_ONEWIRE_DDR;
		if (byte & 0x01)
		{
			_delay_us(7);
			SET_IN_ONEWIRE_DDR;
			_delay_us(70);
		}
		else
		{
			_delay_us(70);
			SET_IN_ONEWIRE_DDR;
			_delay_us(7);
		}
		byte >>= 1;
	}
}
unsigned char OneWireReadByte_3(void)
{
	unsigned char i, byte = 0;
	SET_IN_ONEWIRE_DDR;
	for (i=0; i<8; i++)
	{
		SET_OUT_ONEWIRE_DDR;
		_delay_us(7);
		SET_IN_ONEWIRE_DDR;
		_delay_us(7);
		byte >>= 1;
		if(IS_SET_ONEWIRE_PIN) byte |= 0x80;
		_delay_us(70);
	}
	return byte;
}