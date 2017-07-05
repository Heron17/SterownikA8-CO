#ifndef DS18B20_H
#define DS18B20_H
#define SET_ONEWIRE_PORT PORTC |= _BV(0)
#define CLR_ONEWIRE_PORT PORTC &= ~_BV(0)
#define IS_SET_ONEWIRE_PIN PINC  & _BV(0)
#define SET_OUT_ONEWIRE_DDR DDRC |= _BV(0)
#define SET_IN_ONEWIRE_DDR DDRC &= ~_BV(0)

unsigned char ds18b20_ConvertT_2(void);
int ds18b20_Read_2(unsigned char []);
void OneWireStrong_2(char);
unsigned char OneWireReset_2(void);
void OneWireWriteByte_2(unsigned char);
unsigned char OneWireReadByte_2(void);
#endif