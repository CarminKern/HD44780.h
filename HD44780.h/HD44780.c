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

/*--- typedef und Variablen------------------------------------------ */
typedefstruct_funktionset funktionset;

/*--- getVar ---------------------------------------------------------*/



/*--- Funktionen -----------------------------------------------------*/

void HD44780_initialise(char EN_pin, char RS_pin, char RW_pin, char D7_pin, char D6_pin, char D5_pin, char D4_pin, char D3_pin, char D2_pin, char D1_pin, char D0_pin, char numberoflines) {

	// GPIO Initialisieren
		GPIO_INI();

	// GPIO Pin Einstellungen

		if (EN_pin == RS_pin || EN_pin == RW_pin || EN_pin == D7_pin || EN_pin == D6_pin || EN_pin == D5_pin || EN_pin == D4_pin || EN_pin == D3_pin || EN_pin == D2_pin || EN_pin == D1_pin || EN_pin == D0_pin ||
			RS_pin == RW_pin || RS_pin == D7_pin || RS_pin == D6_pin || RS_pin == D5_pin || RS_pin == D4_pin || RS_pin == D3_pin || RS_pin == D2_pin || RS_pin == D1_pin || RS_pin == D0_pin ||
			RW_pin == D7_pin || RW_pin == D6_pin || RW_pin == D5_pin || RW_pin == D4_pin || RW_pin == D3_pin || RW_pin == D2_pin || RW_pin == D1_pin || RW_pin == D0_pin ||
			D7_pin == D6_pin || D7_pin == D5_pin || D7_pin == D4_pin || D7_pin == D3_pin || D7_pin == D2_pin || D7_pin == D1_pin || D7_pin == D0_pin ||
			D6_pin == D5_pin || D6_pin == D4_pin || D6_pin == D3_pin || D6_pin == D2_pin || D6_pin == D1_pin || D6_pin == D0_pin ||
			D5_pin == D4_pin || D5_pin == D3_pin || D5_pin == D2_pin || D5_pin == D1_pin || D5_pin == D0_pin ||
			D4_pin == D3_pin || D4_pin == D2_pin || D4_pin == D1_pin || D4_pin == D0_pin ||
			D3_pin == D2_pin || D3_pin == D1_pin || D3_pin == D0_pin ||
			D2_pin == D1_pin || D2_pin == D0_pin ||
			D1_pin == D0_pin) {
			printf("\nEingang wurde doppelt belegt...");
		}

		GPIO_SET_OUT("EN",EN_pin);         											// Freigabe- und Taktleitung
		GPIO_SET_OUT("RS",RS_pin);													// Registerauswahl
		GPIO_SET_OUT("RW",RW_pin);   												// Lese- oder Schreibzugriff

		GPIO_SET_OUT("D7",D7_pin);													// Datenleitung 7  4Bit/8Bit Modus
		GPIO_SET_OUT("D6",D6_pin);													// Datenleitung 6  4Bit/8Bit Modus
		GPIO_SET_OUT("D5",D5_pin);													// Datenleitung 5  4Bit/8Bit Modus
		GPIO_SET_OUT("D4",D4_pin);   												// Datenleitung 4  4Bit/8Bit Modus

		if (!(D3_pin == 0 && D2_pin == 0 && D1_pin == 0 && D0_pin == 0)) {
			GPIO_SET_OUT("D3",D3_pin);												// Datenleitung 3       8Bit Modus
			GPIO_SET_OUT("D2",D2_pin);												// Datenleitung 2       8Bit Modus
			GPIO_SET_OUT("D1",D1_pin);												// Datenleitung 1       8Bit Modus
			GPIO_SET_OUT("D0",D0_pin);												// Datenleitung 0       8Bit Modus
		}
	

}

typedefstruct_funktionset HD44780_funktionset(char DL_neu, char N_neu, char F_neu) {
	switch (DL_neu){
		case 0:
			funktionset.DL = 0;
			break;
		case 1:
			funktionset.DL = 1;
			break;
		default:
			if (funktionset.DL != 0 || funktionset.DL != 1) {
				printf("\nNEUInitialisierung funktionset DL");
				funktionset.DL = DEFAULT_FUNKTIONSET_DL;
			}
			else {
				printf("\n Keine Änderung!");
			}
			break;
	}
	switch (N_neu){
		case 0:
			funktionset.N = 0;
			break;
		case 1:
			funktionset.N = 1;
			break;
		default:
			if (funktionset.N != 0 || funktionset.N != 1) {
				printf("\nNEUInitialisierung funktionset N");
				funktionset.N = DEFAULT_FUNKTIONSET_N;
			}
			else {
				printf("\n Keine Änderung!");
			}
			break;
	}
	switch (F_neu){
		case 0:
			funktionset.F = 0;
			break;
		case 1:
			funktionset.F = 1;
			break;
		default:
			if (funktionset.F != 0 || funktionset.F != 1) {
				printf("\nNEUInitialisierung funktionset F");
				funktionset.F = DEFAULT_FUNKTIONSET_F;
			}
			else {
				printf("\n Keine Änderung!");
			}
			break;
	}

	// SET
	return funktionset;
}

void HD44780_test() {

}

int main(void) {
	HD44780_initialise(17, 27, 22, 25, 8, 7, 1, 12, 16, 20, 21, 8);
	HD44780_funktionset(9,1,2);

	getchar();
}
