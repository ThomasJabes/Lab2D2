/*Universidad del Valle de Guatemala 
 * main.c
 * IE3054 Electronica Digital 2
 *	Laboratorio 2 
 * Created: 20/07/2024 13:01:49
 *  Author: Thomas 21626
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "ADC/ADC.h"
#include "LCD/LCD.h"
#include "UART/UART.h"

volatile uint8_t POT1 = 0; 
volatile uint8_t POT2 = 0; 
volatile uint8_t Turno = 0;
volatile int8_t contador = 0; 

char lista1[7], lista2[7], contadorStr[4];

void setup(void);
void initTimer0(void);
void voltageToStr(char *str, uint8_t valor);
void contadorToStr(char *str, int8_t valor); 


int main(void)
{
    setup();
	initLCD8bit();
	initTimer0();
	SetupUART0(M9600);
	
	LCD_Set_Cursor(1,1);
	LCD_Write_String("S1:");
	
	
	LCD_Set_Cursor(6,1);
	LCD_Write_String("S2:");
	
	LCD_Set_Cursor(11, 1);
	LCD_Write_String("S3:");
	
    while (1) 
    {
		voltageToStr(lista1, POT1);
		voltageToStr(lista2, POT2);
		contadorToStr(contadorStr, contador); 
		
		LCD_Set_Cursor(1,2);
		LCD_Write_String(lista1);
		LCD_Set_Cursor(6, 2);
		LCD_Write_String(lista2);
		
		LCD_Set_Cursor(11, 2);
		LCD_Write_String(contadorStr);
		

    }
}

void setup(void){
	cli();
	SetupADC(PC5);
	SetupADC(PC6);
	sei();
}

void initTimer0(void){
	TCCR0B |= (1<<CS00)|(1<<CS02);
	TCNT0 = 220;
	TIMSK0 |= (1<<TOIE0);
}

void voltageToStr(char *str, uint8_t valor) {
	float voltage = valor * 5.0 / 255.0; // Conversión de ADC a voltaje
	int int_part = (int) voltage; // Parte entera
	int dec_part = (int)((voltage - int_part) * 100); // Parte decimal
	str[0] = '0' + int_part;
	str[1] = '.';
	str[2] = '0' + (dec_part / 10);
	str[3] = '0' + (dec_part % 10);
	str[4] = 'V';
	str[5] = '\0';
}

void contadorToStr(char *str, int8_t valor) {
	int is_negative = 0;
	if (valor < 0) {
		is_negative = 1;
		valor = -valor;
	}

	if (is_negative) {
		str[0] = '-';
		str[1] = '0' + (valor / 10);
		str[2] = '0' + (valor % 10);
		str[3] = '\0';
		} else {
		str[0] = '0' + (valor / 10);
		str[1] = '0' + (valor % 10);
		str[2] = '\0';
	}
}

ISR(ADC_vect){
	switch(Turno){
		case 0:
			POT1 = ADCH; 
			break;
		case 1:
			POT2 = ADCH; 
			break;
		default:
			break;
	}
	ADCSRA |= (1<<ADIF);
}

ISR(TIMER0_OVF_vect){
	switch(Turno){
		case 0:
			Turno = 1;
			ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)); //PC5
			ADMUX|=(1<<MUX2)|(1<<MUX0);
			break;
		case 1:
			Turno = 0; 
			ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
			ADMUX|=(1<<MUX2)|(1<<MUX1);
			break;		
	}
	ADCSRA |= (1<<ADSC);
	//TCNT0 = 250;
	TCNT0 = 220;
	TIFR0 |= (1 << TOV0);
}

ISR(USART_RX_vect){
	uint8_t dato = UDR0;  // Leer el dato recibido 
	if (dato == '+') {
		contador++;       // Incrementar el contador 
		} else if (dato == '-') {
		contador--;       // Decrementar el contador 
	}
}
