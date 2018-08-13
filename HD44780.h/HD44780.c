/**********************************************************************\
* Kurzbeschreibung: Diese Headerdatei ist zum Betrieb vom HD44780
*
* Datum:       Autor:        Grund der Aenderung:
* 09.08.2018   Carmin Kern   Neuerstellung
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/

#include <stdio.h>
#include "HD44780.h"

/*--- #defines ------------------------------------------------------ */

/*--- typedef ------------------------------------------------------ */
einstellungen einstellung;

/*--- Funktionen -----------------------------------------------------*/

void HD44780_Initialise(int EN_pin, int RS_pin, int RW_pin, int D7_pin, int D6_pin, int D5_pin, int D4_pin, int D3_pin, int D2_pin, int D1_pin, int D0_pin) {

	// GPIO Initialisieren
	GPIO_INI();

	// GPIO Pin Einstellungen
	GPIO_SET_OUT("EN",EN_pin);         	// Freigabe- und Taktleitung
	GPIO_SET_OUT("RS",RS_pin);	        // Registerauswahl
	GPIO_SET_OUT("RW",RW_pin);   	    // Lese- oder Schreibzugriff

	GPIO_SET_OUT("D7",D7_pin);          // Datenleitung 7  4Bit/8Bit Modus
	GPIO_SET_OUT("D6",D6_pin);          // Datenleitung 6  4Bit/8Bit Modus
	GPIO_SET_OUT("D5",D5_pin);	        // Datenleitung 5  4Bit/8Bit Modus
	GPIO_SET_OUT("D4",D4_pin);   	    // Datenleitung 4  4Bit/8Bit Modus

	if (D3_pin == 0 && D2_pin == 0 && D1_pin == 0 && D0_pin == 0) {
		einstellung.bits = 0;			// Einstellung auf 4Bit Modus setzen
		if (einstellung.bits != 0) { PRINT_FAILED }else { PRINT_OK }; PRINT_HD44780_BITS(4);
	}
	else{
		einstellung.bits = 1;			// Einstellung auf 8Bit Modus setzen
		GPIO_SET_OUT("D3",D3_pin);	    // Datenleitung 3       8Bit Modus
		GPIO_SET_OUT("D2",D2_pin);	    // Datenleitung 2       8Bit Modus
		GPIO_SET_OUT("D1",D1_pin);	    // Datenleitung 1       8Bit Modus
		GPIO_SET_OUT("D0",D0_pin);	    // Datenleitung 0       8Bit Modus
		if (einstellung.bits != 1) { PRINT_FAILED }else { PRINT_OK }; PRINT_HD44780_BITS(8);
	}

	// HD44780
}

void HD44780_test() {
	printf("\n... %d ... %d ... %d ... ", einstellung.bits, einstellung.pixel, einstellung.zeilen);
}

int main(void) {
	HD44780_Initialise(17, 27, 22, 25, 8, 7, 1, 12, 16, 20, 21);
	HD44780_test();
	getchar();
}
