/*Universidad del Valle de Guatemala 
 * UART.h
 * IE3054 Electronica Digital 2
 * Created: 20/07/2024 13:01:49
 *  Author: Thomas 21626
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include <stddef.h>

/*
	DEFINICIONES DE VARIABLES
*/
#define M9600 1


//Modo 9600
void SetupUART0(uint8_t MODO);
void writeTextUART(char * Texto);
void writeUART(char Caracter);
void procesarCadena(char *cadena_mc);
void recibir(char dato); 


#endif 