/**********************************************************************\
* Kurzbeschreibung:
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

typedef struct variablen
{

}variablen;

/*--- Funktionsdefinitionen ------------------------------------------*/

void HD44780getVar() {

}

void HD44780Initialise(int EN_pin, int RS_pin, int RW_pin, int D7_pin, int D6_pin, int D5_pin, int D4_pin, int D3_pin, int D2_pin, int D1_pin, int D0_pin) {

	// GPIO Initialisieren
	GPIO_INI();

	// GPIO Pin Einstellungen
	GPIO_SET_OUT(EN_pin);         	// Freigabe- und Taktleitung
	GPIO_SET_OUT(RS_pin);	        // Registerauswahl
	GPIO_SET_OUT(RW_pin);   	    // Lese- oder Schreibzugriff

	GPIO_SET_OUT(D7_pin);           // Datenleitung 7  4Bit/8Bit Modus
	GPIO_SET_OUT(D6_pin);           // Datenleitung 6  4Bit/8Bit Modus
	GPIO_SET_OUT(D5_pin);	        // Datenleitung 5  4Bit/8Bit Modus
	GPIO_SET_OUT(D4_pin);   	    // Datenleitung 4  4Bit/8Bit Modus

	if (D3_pin != 0 && D2_pin != 0 && D1_pin != 0 && D0_pin == 0) {
		GPIO_SET_OUT(D3_pin);	    // Datenleitung 3       8Bit Modus
		GPIO_SET_OUT(D2_pin);	    // Datenleitung 2       8Bit Modus
		GPIO_SET_OUT(D1_pin);	    // Datenleitung 1       8Bit Modus
		GPIO_SET_OUT(D0_pin);	    // Datenleitung 0       8Bit Modus

									// 8 Bit Modus aktiv
	}
	else {
		// 4 Bit Modus aktiv
	}

}


int main(void) {
	HD44780Initialise(17, 27, 22, 25, 8, 7, 1, 12, 16, 20, 21);
}
