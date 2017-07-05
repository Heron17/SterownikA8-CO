#ifndef DS18B20_H
#define DS18B20_H
#define SET_ONEWIRE_PORT PORTD |= _BV(7)
#define CLR_ONEWIRE_PORT PORTD &= ~_BV(7)
#define IS_SET_ONEWIRE_PIN PIND  & _BV(7)
#define SET_OUT_ONEWIRE_DDR DDRD |= _BV(7)
#define SET_IN_ONEWIRE_DDR DDRD &= ~_BV(7)

unsigned char ds18b20_ConvertT_3(void);
int ds18b20_Read_3(unsigned char []);
void OneWireStrong_3(char);
unsigned char OneWireReset_3(void);
void OneWireWriteByte_3(unsigned char);
unsigned char OneWireReadByte_3(void);
#endif