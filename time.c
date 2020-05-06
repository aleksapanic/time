/*
 * time.c
 *
 *  Created on: May 6, 2020
 *      Author: Paki
 */
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long sys_time = 0;

ISR(TIMER0_COMPA_vect) {
	sys_time ++;
}

void initTime() {
	TCCR0A = 0x02; //tajmer0 -> CTC mod

#if F_PCU > 20000000
#error "Frekvencija takta mora biti manja od 20MHz"
#endif

	unsigned long n = F_CPU / 1000;
	unsigned char clksel = 1; //podrazumevana vrednost bez preskaliranja

	/*znaci da ne mozemo da radimo sa 8-bitnim tajmerom
	 * automatsko podesavanje faktora preskaliranja*/
	while(n > 255){

		n /= 8;
		clksel++;
	}

	TCCR0B = clksel;
	OCR0A = (unsigned char)(n & 0xff) - 1;
	TIMSK0 = 0X02;

	sei();
}

unsigned long millis(){

	unsigned long tmp;
	/*osiguravamo da se javi prekid usled ocitavanja vrednosti sys_time*/
	cli();
	tmp = sys_time;
	sei();

	return tmp;
}


void delay(unsigned long d){

	unsigned long t0 = millis();

	while(millis() - t0 < d);
}
