#ifndef DS18B20_H
#define DS18B20_H
#define SET_ONEWIRE_PORT PORTC |= _BV(1)
#define CLR_ONEWIRE_PORT PORTC &= ~_BV(1)
#define IS_SET_ONEWIRE_PIN PINC  & _BV(1)
#define SET_OUT_ONEWIRE_DDR DDRC |= _BV(1)
#define SET_IN_ONEWIRE_DDR DDRC &= ~_BV(1)

unsigned char ds18b20_ConvertT_1(void);
int ds18b20_Read_1(unsigned char []);
void OneWireStrong_1(char);
unsigned char OneWireReset_1(void);
void OneWireWriteByte_1(unsigned char);
unsigned char OneWireReadByte_1(void);
#endif