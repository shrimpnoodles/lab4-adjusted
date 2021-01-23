/*	Author: hcier001
 *  Partner(s) Name: 
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
enum State{start, init, pound, y, wait, relock1, relock2, unlock} state;
void Tick(){
	switch (state) { //transitions
		case start:
			state = init;
			break;
		case init:
			if((PINA&0x07)==0x04){
				state = pound;
			}
			else if((PINA&0x80)==0x80){
				state = lock;
			}
			else{
				state = init;
			}
			break;
		case pound:
			state = wait;
			break;
		case wait:
			if((PINA&0x07)==0x02){
				state =y;
			}
			else if((PINA&0X80)==0X80){
				state = lock;
			}
			else{
				state = wait;
			}
			break; 
		case y:
			 if((PINA&0x80)==0x80){
				state=lock;
			}
			else if((PINA&0x07)==0x04){
				state = relock1;
			}
			else{
				state = y;
			}
			break;
		case relock1:
			if((PINA&0x07)==0x02){
				state=relock2;
			}
			else{
				state = relock1;
			}
			break;
		case relock2:
			if(PINA == 0x00){
				state = init;
			}
			else{
				state = relock2;
			}
			break;
		case lock:
			if((PINA&0x80)==0x80){
				state = lock;
			}
			else{
				state = init;
			}
		default:
			state = start;
			break;
		}
		switch(state) { //actions
			case init:
				PORTB = 0;
				PORTC = init;
				break;
			case pound:
				PORTB =0;
				PORTC = wait;
				break; 
			case y:
				PORTB = 1;
				PORTC = y;
				break;
			case relock1:
				PORTB =1;
				PORTC = relock1;
				break;
			case relock2:
				PORTB =1;
				PORTC = relock2;
				break;
			case lock:
				PORTB =0;
				PORTC = lock;
				break;
			default:
				break;
			}
	}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0XFF;
	DDRB = 0XFF; PORTB = 0X00;
	DDRC =0xff; PORTC =0x00;
	state = start;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
