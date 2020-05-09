/*
 * time.c
 *
 *  Created on: May 6, 2020
 *      Author: Paki
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "time.h"

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

	TCCR0B = clksel; //faktor preskaliranja
	OCR0A = (unsigned char)(n & 0xff) - 1; //kastovanje prom. n i maskiranje 8 nizih bita
	TIMSK0 = 0X02;

	sei(); //dozvola prekida
}

unsigned long millis(){

	unsigned long tmp;
	/*osiguravamo da se ne javi prekid usled ocitavanja vrednosti sys_time*/
	cli(); //zabrana prekida
	tmp = sys_time;
	sei(); //dozvola prekida

	return tmp;
}


void delay(unsigned long d){

	unsigned long t0 = millis(); //trenutak kada je pozvana delay() fja

	while(millis() - t0 < d);
}
