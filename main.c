/*	Author: hcier001
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
<<<<<<< HEAD

enum State{start, led0, led1, buttonWait} state;
void Tick(){
	switch (state) { // transitions
		case start:
			state = led0;
			break;
		case led0:
			if(PINA == 0x01){
				state = led1;
			}
			else{
				state = led0;
			}
			break;
		case led1:
			state = buttonWait;
			break;
		case buttonWait:
			if(PINA == 0x01){
				state = led0;
			}
			else{
				state = buttonWait;
			}
			break;
=======
enum States {start, init, p0push, p1push, reset} state;
unsigned portcCount;
void Tick(){
	switch(state) { //transitions
		case start:
			state = init;
			break;
		case init:
			if(PINA == 0X00){
				state =init;
			}
			else if(PINA == 0x01){
				state = p0push;
			}
			else if(PINA== 0x02){
				state = p1push;
			}
			else if(PINA== 0x03){
				state = reset;
			}
			break;
		case p0push:
		//	if(PINA !=0x01){
				state = init;
		//	}
			break;
		case p1push:
		//	if(PINA !=0x02){
				state = init;
		//	}
			break;
		case reset:
		//	if(PINA != 0x03){
				state = init;
		//	}
			break;
>>>>>>> 90c746160a6dd657438e35456c316a60576ec826
		default:
			state = start;
			break;
		}
<<<<<<< HEAD
	switch (state) { //actions
		case led0:
			PORTB = 0x01;
			break;
		case led1:
			PORTB = 0x02;
			break;
		case buttonWait:
			PORTB = 0x02;
=======
	switch(state){ //actions
		case init:
			break;
		case p0push:
			if(portcCount < 9){
				portcCount++;
			}
			break;
		case p1push: 
			if(portcCount > 0){
				portcCount--;
			}
			break;
		case reset:
			portcCount =0;
>>>>>>> 90c746160a6dd657438e35456c316a60576ec826
			break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0XFF;
	DDRB = 0XFF; PORTB = 0X00;
<<<<<<< HEAD
	state = start;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
=======
	DDRC = 0xFF; PORTC = 0X00;
	state = start;
	portcCount = 7;
    /* Insert your solution below */
    while (1) {
	Tick();
	PORTC = portcCount;
    }

>>>>>>> 90c746160a6dd657438e35456c316a60576ec826
    return 1;
}
