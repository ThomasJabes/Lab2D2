/*Universidad del Valle de Guatemala 
 * LCD.h
 * IE3054 Electronica Digital 2
 * Created: 20/07/2024 13:01:49
 *  Author: Thomas 21626
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>


//Funcion para setear LCD en modo 8Bit
void initLCD8bit(void);

//Funci?n para colocar en el puerto un valor
void LCD_Port(char a); 

//Funci?n para mandar un comando
void LCD_CMD(char a);

//Funci?n para enviar un caracter 
void LCD_Write_CHAR(char c); 

//Funci?n para enviar una cadena
void LCD_Write_String(char *a);

//Desplazamiento hacia la derecha
void Lcd_Shift_Right(void);

//Desplazamiento hacia la izquierda
void Lcd_Shift_Left(void);

//Establecer el cursor 
void LCD_Set_Cursor(char c, char f);

#endif /* LCD8_H_ */