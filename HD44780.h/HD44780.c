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
typedefstruct_pinset pinset = { 0,0,0,0,0,0,0,0,0,0,0 };

typedefstruct_funktionset funktionset;

/*--- getVar ---------------------------------------------------------*/



/*--- Funktionen -----------------------------------------------------*/

int main(void) {
	printf("\n Starte test...\n\n");

	HD44780_initialize(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 4,0,1);

	getchar();
}

void HD44780_pinset(typedefstruct_pinset setpinto) {
	
	if (setpinto.EN_pin != 88) {
		GPIO_SET_OUT("EN", setpinto.EN_pin);
	}
	if (setpinto.RS_pin != 88) {
		GPIO_SET_OUT("RS", setpinto.RS_pin);
	}
	if (setpinto.RW_pin != 88) {
		GPIO_SET_OUT("RW", setpinto.RW_pin);
	}
	if (setpinto.D7_pin != 88) {
		GPIO_SET_OUT("D7", setpinto.D7_pin);
	}
	if (setpinto.D6_pin != 88) {
		GPIO_SET_OUT("D6", setpinto.D6_pin);
	}
	if (setpinto.D5_pin != 88) {
		GPIO_SET_OUT("D5", setpinto.D5_pin);
	}
	if (setpinto.D4_pin != 88) {
		GPIO_SET_OUT("D4", setpinto.D4_pin);
	}
	if (setpinto.D3_pin != 88) {
		GPIO_SET_OUT("D3", setpinto.D3_pin);
	}
	if (setpinto.D2_pin != 88) {
		GPIO_SET_OUT("D2", setpinto.D2_pin);
	}
	if (setpinto.D1_pin != 88) {
		GPIO_SET_OUT("D1", setpinto.D1_pin);
	}
	if (setpinto.D0_pin != 88) {
		GPIO_SET_OUT("D0", setpinto.D0_pin);
	}
}

int HD44780_initialize(char EN_pin, char RS_pin, char RW_pin, char D7_pin, char D6_pin, char D5_pin, char D4_pin, char D3_pin, char D2_pin, char D1_pin, char D0_pin, char funktionset_DL, char funktionset_N, char funktionset_F) {
	
	// GPIO Initialisieren
		GPIO_INI();	

	// Pin einstellungen für 4 Bit Modus
		if (funktionset_DL == 4) {
			// Pin überprüfen
				if (EN_pin == RS_pin || EN_pin == RW_pin || EN_pin == D7_pin || EN_pin == D6_pin || EN_pin == D5_pin || EN_pin == D4_pin ||
					RS_pin == RW_pin || RS_pin == D7_pin || RS_pin == D6_pin || RS_pin == D5_pin || RS_pin == D4_pin ||
					RW_pin == D7_pin || RW_pin == D6_pin || RW_pin == D5_pin || RW_pin == D4_pin ||
					D7_pin == D6_pin || D7_pin == D5_pin || D7_pin == D4_pin ||
					D6_pin == D5_pin || D6_pin == D4_pin ||
					D5_pin == D4_pin) {
					return 0;												// Funktionsabbruch wegen mehrfach Belegung
				}
			// Pins auf Output setzen
				typedefstruct_pinset setpinto = { EN_pin, RS_pin, RW_pin, D7_pin, D6_pin, D5_pin, D4_pin, 88, 88, 88, 88 };
				HD44780_pinset(setpinto);
		}
	// Pin einstellungen für 8 Bit Modus
		else if (funktionset_DL == 8) {
			// Pins überprüfen
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
					return 0;												// Funktionsabbruch wegen mehrfach Belegung
				}
				else {
			// Pins auf Output setzen
					typedefstruct_pinset setpinto = { EN_pin, RS_pin, RW_pin, D7_pin, D6_pin, D5_pin, D4_pin, D3_pin, D2_pin, D1_pin, D0_pin };
					HD44780_pinset(setpinto);
				}
		}
	// Pin einstellungen nicht möglich
		else {														

		}

	// Funktionset einstellungen
		// DL - Data length
		/*	
			Legt die Schnittstellendatenlänge fest. 
			0 = 4 Bit Modus (DB7 - DB4)
			1 = 8 Bit Modus (DB7 - DB0) 
		*/
			if (funktionset_DL == 4) {
				funktionset.DL = 0;
			}
			else if (funktionset_DL == 8) {
				funktionset.DL = 1;
			}
			else {
				return 0;													// Funktionsabbruch wegen falscher Eingabe
			}
		// N - Numbers of Display Lines
		/*
			Legt die Anzahl der Displayzeilen fest.
			0 = 1 Zeile
			1 = 2 oder 4 Zeilen
		*/
			if (funktionset_N == 1) {
				funktionset.N = 0;
			}
			else if (funktionset_N == 2 || funktionset_N == 4) {
				funktionset.N = 1;
			}
			else {
				return 0;													// Funktionsabbruch wegen falscher Eingabe
			}
		// F - Fonts
		/*
			Legt die Pixelgröße fest.
			0 = 5x8  Pixel
			1 = 5x10 Pixel
		*/
			if (funktionset_F == 8) {
				funktionset.F = 0;
			}
			else if (funktionset_F == 10) {
				funktionset.F = 1;
			}
			else {
				return 0;													// Funktionsabbruch wegen falscher Eingabe
			}
		
	return 0;
}