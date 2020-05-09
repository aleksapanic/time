/**
 * @file time.h
 * @brief Biblioteka za vremenske funkcije mikrokontrolera ATmega328P
 * @author Aleksa Panic
 * @date 06-05-2020
 */

#ifndef TIME_H_
#define TIME_H_

/**
 * Funkcija inicijalizuje tajmer i
 * vrsi automatsko podesavanje faktora preskaliranja
 */
void initTime();

/**
 * Funkcija za ocitavanje vremenske promenljive koja
 * sadrzi zabranu pojave prekida u trenutku ocitavanja
 * @return trenutna vrednost vremenske promenljive
 */
unsigned long millis();

/**
 * Funkcija za formiranje kasnjenja sa zadatim trajanjem u milisekundama
 * @param d vremenska vrednost kasnjenja
 */
void delay(unsigned long d);

#endif /* TIME_H_ */
