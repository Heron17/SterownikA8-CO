#include <avr/io.h>
#include <util/delay.h>
#include "hd44780.h"
#include "ds18b20_1.h"
#include "ds18b20_2.h"
#include "ds18b20_3.h"

unsigned char cyfra (unsigned char a)
{
	int b=a;
	switch (a)
	{
		case 1:b=11; break;
		case 2:b=2;break;
		case 3:b=3;break;
		case 4:b=1;break;
		case 5:b=5;break;
		case 6:b=6;break;
		case 7:b=4;break;
		case 8:b=8;break;
		case 9:b=9;break;
		case 10:b=7;break;
		case 11:b=0;break;
		case 12:b=12;break;
	}return b;
}

char read_keypad(void)
{
	unsigned char row,col;
	
	int b=0;
	for(row=0x7e,b=1; row>=0x77; row=(row<<1|0x1)&0x7f)
	{
		PORTB = row;
		for(col=0x10; col< 0x80; col<<=1, b++)
		if(!(PINB & col))	return b;
	}
	return 0;
}

char read_keypad8(void)
{
	while(1)
	{
		unsigned char row,col;
		
		int b=0;
		for(row=0x7e,b=1; row>=0x77; row=(row<<1|0x1)&0x7f)
		{
			PORTB = row;
			for(col=0x10; col< 0x80; col<<=1, b++)
			if(!(PINB & col))	return b;
		}
	}
}

char strt[]="Sterownik do kotla C.O. na paliwa stale!";

char stru[]="  Ktora temperature regulowac?";
char strs[]="SALON";
char strk[]="KOCIOL";
char strb[]="BOILER";
char str[8];
char str1[16];
char str2[16];
char str3[16];

double  temp[3] ;
unsigned char ds18b20_pad[9];

int main(void)
{
	DDRC |= (1<<PC5);
	DDRC |= (1<<PC4);
	DDRC |= (1<<PC3);
	
	char str[]="1";//KLAWI

	DDRB  = 0x0f;
	PORTB = 0x7f;//KLAWIA
	lcd_init();
	lcd_cls();
	
	unsigned char ds18b20_pad_1[9];
	unsigned char ds18b20_pad_2[9];
	unsigned char ds18b20_pad_3[9];
	int temp_int1_1, temp_int1_2, temp_int1_3;
	int8_t i, k, p, m, n;
	int nastawa, nastawad, nastawaj, a1=0, a2=0;
	p=0;
	k= strlen(strt);
	m= strlen(stru);
	i=0;
	if (read_keypad()==12) {goto b;} //poczatek wstepu
	lcd_locate(0,0);
	lcd_str("  Sterownik do  ");
	lcd_locate(1,0);
	lcd_str("   kotla C.O.   ");
	lcd_locate(2,0);
	lcd_str("       na       ");
	lcd_locate(3,0);
	lcd_str("  paliwa stale. ");
	_delay_ms(5000);
	lcd_cls();
	lcd_locate(0,0);
	lcd_str("wykonal:        ");
	lcd_locate(1,0);
	lcd_str("     Michal     ");
	lcd_locate(2,0);
	lcd_str("   Czaplewski   ");
	lcd_locate(3,0);
	lcd_str("     styczen '15");
	_delay_ms(5000);	//koniec wstepu

	b:
	lcd_cls();						//wybor regulowanej tepmeratury (poczatek)
	lcd_locate(1,0);
	lcd_str("SALON      (1)");
	lcd_locate(2,0);
	lcd_str("BOILER     (2)");
	lcd_locate(3,0);
	lcd_str("KOCIOL     (3)");
	
	while (1)
	{
		_delay_ms(500);
		lcd_locate(0,0);
		lcd_str("                ");
		lcd_locate(0,i--);
		lcd_str(stru);
		if( i<=8-m )
		{
			lcd_locate(0,16-p);
			lcd_str(stru);
			if (p==15)
			{
				i=0;
				p=0;
			}
			p++;
		}
		if (read_keypad()==4)
		{
			lcd_cls();
			n=1;
			lcd_locate(0,0);
			lcd_str("     SALON      ");
			while (1)
			{
				if (read_keypad()==4){}
				else {goto n;}
			}
		}
		if (read_keypad()==2)
		{
			lcd_cls();
			n=2; lcd_locate(0,0); lcd_str("     BOILER     ");
			while (1)
			{
				if (read_keypad()==2){}
				else {goto n;}
			}
		}
		if (read_keypad()==3)
		{
			lcd_cls();
			n=3; lcd_locate(0,0); lcd_str("     KOCIOL     ");
			while (1)
			{
				if (read_keypad()==3){}
				else {goto n;}
			}
		}
	}				//wybor regulowanej tepmeratury (koniec)
	
	n:			//okreslenie nastawy (poczatek)
	lcd_locate(1,0);
	lcd_str("    Nastawa:    ");

	nastawad=read_keypad8();
	if (read_keypad()==12) {goto b;}
	if (read_keypad()==11) {goto b;}
	while (1)
	{
		if (read_keypad()==nastawad) {}
		else
		{
			sprintf(str,"%d \xdf""C",cyfra(nastawad));
			lcd_locate(2,6);
			lcd_str(str);
			nastawaj=read_keypad8();
			if (read_keypad()==12) {goto b;}
			while (1)
			{
				if (read_keypad()==nastawaj) {}
				else
				{
					nastawa=10*cyfra(nastawad)+cyfra(nastawaj);
					lcd_locate(2,6);
					if (cyfra(nastawa)==121) {goto b;}	
					if (cyfra(nastawa)==0) {goto b;}	
					sprintf(str,"%d\xdf""C",cyfra(nastawa));
					lcd_str(str);
					lcd_locate(3,0);
					lcd_str("Dalej *  Ponow #");
					while(1)
					{
						if (read_keypad()==1) {lcd_cls();goto a;}
						if (read_keypad()==12) {goto b;}
					}
				}
			}
		}
	}			//okreslenie nastawy (koniec)
	a:

	i=0; p=0;
	while(1)
	{				
		
			
		if(ds18b20_ConvertT_1() &&  ds18b20_ConvertT_2() && ds18b20_ConvertT_3())
		{
			_delay_ms(750);
			ds18b20_Read_1(ds18b20_pad_1);
			temp_int1_1 = ((ds18b20_pad_1[1] << 8) + ds18b20_pad_1[0])/16; // obliczanie czescie calkowitej (mala roznica z oryginalem)
			sprintf(str1,"%d\xdf""C", temp_int1_1);
			ds18b20_Read_2(ds18b20_pad_2);
			temp_int1_2 = ((ds18b20_pad_2[1] << 8) + ds18b20_pad_2[0])/16; // obliczanie czescie calkowitej (mala roznica z oryginalem)
			sprintf(str2,"%d\xdf""C", temp_int1_2);
			ds18b20_Read_3(ds18b20_pad_3);
			temp_int1_3 = ((ds18b20_pad_3[1] << 8) + ds18b20_pad_3[0])/16; // obliczanie czescie calkowitej (mala roznica z oryginalem)
			sprintf(str3,"%d\xdf""C", temp_int1_3);
		}
		
		lcd_locate(0,0);		//tekst w pierwszej linii
		lcd_str("                ");
		lcd_locate(0,i--);
		lcd_str(strt);
		if( i<=8-k )
		{
			lcd_locate(0,16-p);
			lcd_str(strt);
			if (p==15)
			{i=0; p=0;}p++;}
			switch (n)
			{
				case 1:
				{
					lcd_locate(1,0);
					lcd_str(strs);
					lcd_str("  ");
					lcd_str(str1);
					lcd_str(" (");
					sprintf(str,"%d", nastawa);
					lcd_str(str);
					lcd_str(")");
					
					lcd_locate(2,0);
					lcd_str(" boiler  kociol ");
					lcd_locate(3,0);
					lcd_str("  ");
					lcd_str(str2);
					lcd_str("    ");
					lcd_str(str3);
					
					if (temp_int1_1<nastawa)  //przekaznik
					{
						PORTC |= (1<<PC4);
						PORTC |= (1<<PC3);
					}
					else
					{
						PORTC &= ~(1<<PC4);
						PORTC &= ~(1<<PC3);
					}
					break;
				}
				case 2:{
					lcd_locate(1,0);
					lcd_str(strb);
					lcd_str(" ");
					lcd_str(str2);
					lcd_str(" (");
					sprintf(str,"%d", nastawa);
					lcd_str(str);
					lcd_str(")");
					
					lcd_locate(2,0);
					lcd_str(" kociol   salon ");
					lcd_locate(3,0);
					lcd_str("  ");
					lcd_str(str3);
					lcd_str("    ");
					lcd_str(str1);
					
					if (temp_int1_2<nastawa)  //przekaznik
					{
						PORTC |= (1<<PC4);
						PORTC |= (1<<PC3);
					}
					else
					{
						PORTC &= ~(1<<PC4);
						PORTC &= ~(1<<PC3);
					}
					break;
				}
				case 3:{
					lcd_locate(1,0);
					lcd_str(strk);
					lcd_str(" ");
					lcd_str(str3);
					lcd_str(" (");
					sprintf(str,"%d", nastawa);
					lcd_str(str);
					lcd_str(")");
					
					lcd_locate(2,0);
					lcd_str(" salon   boiler ");
					lcd_locate(3,0);
					lcd_str("  ");
					lcd_str(str1);
					lcd_str("    ");
					lcd_str(str2);
					if (temp_int1_3<nastawa)  //przekaznik
					{
						PORTC |= (1<<PC4);
						PORTC |= (1<<PC3);
					}
					else
					{
						PORTC &= ~(1<<PC4);
						PORTC &= ~(1<<PC3);
					}
					break;
				}
			}
			if (temp_int1_2>=24|temp_int1_3>=24)  //alarm
			{
				if (a1==0)
				{
					lcd_locate(0,0);
					lcd_str("     ALARM!     ");
					a1=1;
					PORTC |= (1<<PC5);
				}
				else
				{
					lcd_locate(0,0);
					lcd_str("  PRZEGRZANIE!  ");
					a1=0;
					PORTC &= ~(1<<PC5);
				}
			}
			else
			{
				PORTC &= ~(1<<PC5);
			}
			if (read_keypad()==12) {_delay_ms(1000);i=0;p=0; goto b;}
		}
		return 0;
	}
