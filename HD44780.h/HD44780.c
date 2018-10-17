

/*--- #include ------------------------------------------------------- */
#include <stdio.h>
#include "HD44780.h"

/*--- #define ------------------------------------------------------- */

#define DEFAULT_PINSET_EN 13
#define DEFAULT_PINSET_RS 19
#define DEFAULT_PINSET_RW 26
#define DEFAULT_PINSET_D7 25
#define DEFAULT_PINSET_D6 8
#define DEFAULT_PINSET_D5 7
#define DEFAULT_PINSET_D4 1
#define DEFAULT_PINSET_D3 12
#define DEFAULT_PINSET_D2 16
#define DEFAULT_PINSET_D1 20
#define DEFAULT_PINSET_D0 21

#define DEFAULT_FUNCTIONSET_DL 1
#define DEFAULT_FUNCTIONSET_N 1
#define DEFAULT_FUNCTIONSET_F 0

/*--- Globale Struktur Variablen initialisieren ----------------------------- */

typdefstruct_datasend lastdata = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
typedefstruct_pinset pinset = { DEFAULT_PINSET_EN , DEFAULT_PINSET_RS , DEFAULT_PINSET_RW , DEFAULT_PINSET_D7 , DEFAULT_PINSET_D6 , DEFAULT_PINSET_D5 , DEFAULT_PINSET_D4 , DEFAULT_PINSET_D3 , DEFAULT_PINSET_D2 , DEFAULT_PINSET_D1 , DEFAULT_PINSET_D0 };
typedefstruct_functionset functionset = { DEFAULT_FUNCTIONSET_DL , DEFAULT_FUNCTIONSET_N , DEFAULT_FUNCTIONSET_F };

/*--- Funktionen ---------------------------------------------------- */


extern void HD44780_enable() {

	/* Funktionsbeschreibung
		Die Funktion sendet einen Impuls auf die HD44780 um Daten zu empfangen.
		
		Wartezeit GPIO:
			Wartezeit 
		Wartezeit HD44780:
			Wartezeit
	*/

	// Wartezeit GPIO
		DELAY_GPIO;
	// Einstellen von EN
		GPIO_SET("EN", pinset.EN, 1);
	// Wartezeit HD44780
		DELAY_ENABLE;
	// Einstellen von EN
		GPIO_SET("EN", pinset.EN, 0);
}

int HD44780_datasend_4bit(char RS, char RW, char D7, char D6, char D5, char D4, char D3, char D2, char D1, char D0) {

	/* Funktionsbeschreibung
		Diese Funktion sendet die Daten RS, RW, D7, D6, D5, D4, D3, D2, D1 und D0, mittels GPIO an die HD44780.
		
		Argumente prüfen:
			Die eingehenden Argumente werden überpüft,
			wenn diese nicht 0, 1 oder 'X' entsprechen wird die Funktion abgebrochen und der Wert 1 zurückgegeben.

		Daten versenden:
			Die Pins werden in zwei Phasen, eingestellt und die Daten an die HD44780 gesendet.
			Diese werden nicht verstellt wenn der jeweilige Parameter 'X' ist oder 
			der Pin bereits den einzustellenden Parameter entspricht.
	*/

	// Interne Variablen Initialisieren
		typdefstruct_datasend datasend = { RS , RW , D7 , D6 , D5 , D4 , D3 , D2 , D1 , D0 };
		int datasend_error = 0;

	// Argumente prüfen
		if ((RS != 0 && RS != 1 && RS != 88) || (RW != 0 && RW != 1 && RW != 88) || (D7 != 0 && D7 != 1 && D7 != 88) || (D6 != 0 && D6 != 1 && D6 != 88) || (D5 != 0 && D5 != 1 && D5 != 88) || (D4 != 0 && D4 != 1 && D4 != 88) || (D3 != 0 && D3 != 1 && D3 != 88) || (D2 != 0 && D2 != 1 && D2 != 88) || (D1 != 0 && D1 != 1 && D1 != 88) || (D0 != 0 && D0 != 1 && D0 != 88)) {
			// Abbruch wenn die Argumente nicht 0, 1 oder 'X' sind
			return datasend_error = 1;
		}

	// Daten versenden
		// Phase 1
			// Einstellen von RS 
				if (datasend.RS != lastdata.RS && datasend.RS != 88) {
					GPIO_SET("RS", pinset.RS, datasend.RS);
					lastdata.RS = datasend.RS;
				}
			// Einstellen von RW 
				if (datasend.RW != lastdata.RW && datasend.RW != 88) {
					GPIO_SET("RW", pinset.RW, datasend.RW);
					lastdata.RW = datasend.RW;
				}
			// Einstellen von D7 
				if (datasend.D7 != lastdata.D7 && datasend.D7 != 88) {
					GPIO_SET("D7", pinset.D7, datasend.D7);
					lastdata.D7 = datasend.D7;
				}
			// Einstellen von D6 
				if (datasend.D6 != lastdata.D6 && datasend.D6 != 88) {
					GPIO_SET("D6", pinset.D6, datasend.D6);
					lastdata.D6 = datasend.D6;
				}
			// Einstellen von D5 
				if (datasend.D5 != lastdata.D5 && datasend.D5 != 88) {
					GPIO_SET("D5", pinset.D5, datasend.D5);
					lastdata.D5 = datasend.D5;
				}
			// Einstellen von D4 
				if (datasend.D4 != lastdata.D4 && datasend.D4 != 88) {
					GPIO_SET("D4", pinset.D4, datasend.D4);
					lastdata.D4 = datasend.D4;
				}
			// Senden der Daten
				HD44780_enable();

		// Phase 2
			// Einstellen von D3 auf D7
				if (datasend.D3 != lastdata.D7 && datasend.D3 != 88) {
					GPIO_SET("D7", pinset.D7, datasend.D3);
					lastdata.D7 = datasend.D3;
				}
			// Einstellen von D2 auf D6
				if (datasend.D2 != lastdata.D6 && datasend.D2 != 88) {
					GPIO_SET("D6", pinset.D6, datasend.D2);
					lastdata.D6 = datasend.D2;
				}
			// Einstellen von D1 auf D5
				if (datasend.D1 != lastdata.D5 && datasend.D1 != 88) {
					GPIO_SET("D5", pinset.D5, datasend.D1);
					lastdata.D5 = datasend.D1;
				}
			// Einstellen von D0 auf D4
				if (datasend.D0 != lastdata.D4 && datasend.D0 != 88) {
					GPIO_SET("D4", pinset.D4, datasend.D0);
					lastdata.D4 = datasend.D0;
				}
			// Senden der Daten
				HD44780_enable();

	return datasend_error;
}

int HD44780_datasend_8bit(char RS, char RW, char D7, char D6, char D5, char D4, char D3, char D2, char D1, char D0) {

	/* Funktionsbeschreibung
		Diese Funktion sendet die Daten RS, RW, D7, D6, D5, D4, D3, D2, D1 und D0, mittels GPIO an die HD44780.

		Argumente prüfen:
			Die eingehenden Argumente werden überpüft,
			wenn diese nicht 0, 1 oder 'X' entsprechen wird die Funktion abgebrochen und der Wert 1 zurückgegeben.

		Daten versenden:
			Die Pins werden jeweils eingestellt und an die HD44780 gesendet.
			Diese werden nicht verstellt wenn der jeweilige Parameter 'X' ist oder
			der Pin bereits den einzustellenden Parameter entspricht.
	*/

	// Interne Variablen Initialisieren
		typdefstruct_datasend datasend = { RS , RW , D7 , D6 , D5 , D4 , D3 , D2 , D1 , D0 };
		int datasend_error = 0;

	// Argumente prüfen
		if ((RS != 0 && RS != 1 && RS != 88) || (RW != 0 && RW != 1 && RW != 88) || (D7 != 0 && D7 != 1 && D7 != 88) || (D6 != 0 && D6 != 1 && D6 != 88) || (D5 != 0 && D5 != 1 && D5 != 88) || (D4 != 0 && D4 != 1 && D4 != 88) || (D3 != 0 && D3 != 1 && D3 != 88) || (D2 != 0 && D2 != 1 && D2 != 88) || (D1 != 0 && D1 != 1 && D1 != 88) || (D0 != 0 && D0 != 1 && D0 != 88)) {
			// Abbruch wenn die Argumente nicht 0, 1 oder 'X' sind
			return datasend_error = 1;
		}

	// Daten versenden

		// Einstellen von RS 
			if (datasend.RS != lastdata.RS && datasend.RS != 88) {
				GPIO_SET("RS", pinset.RS, datasend.RS);
				lastdata.RS = datasend.RS;
			}
		// Einstellen von RW 
			if (datasend.RW != lastdata.RW && datasend.RW != 88) {
				GPIO_SET("RW", pinset.RW, datasend.RW);
				lastdata.RW = datasend.RW;
			}
		// Einstellen von D7 
			if (datasend.D7 != lastdata.D7 && datasend.D7 != 88) {
				GPIO_SET("D7", pinset.D7, datasend.D7);
				lastdata.D7 = datasend.D7;
			}
		// Einstellen von D6 
			if (datasend.D6 != lastdata.D6 && datasend.D6 != 88) {
				GPIO_SET("D6", pinset.D6, datasend.D6);
				lastdata.D6 = datasend.D6;
			}
		// Einstellen von D5 
			if (datasend.D5 != lastdata.D5 && datasend.D5 != 88) {
				GPIO_SET("D5", pinset.D5, datasend.D5);
				lastdata.D5 = datasend.D5;
			}
		// Einstellen von D4 
			if (datasend.D4 != lastdata.D4 && datasend.D4 != 88) {
				GPIO_SET("D4", pinset.D4, datasend.D4);
				lastdata.D4 = datasend.D4;
			}
		// Einstellen von D3 
			if (datasend.D3 != lastdata.D3 && datasend.D3 != 88) {
				GPIO_SET("D3", pinset.D3, datasend.D3);
				lastdata.D3 = datasend.D3;
			}
		// Einstellen von D2 
			if (datasend.D2 != lastdata.D2 && datasend.D2 != 88) {
				GPIO_SET("D2", pinset.D2, datasend.D2);
				lastdata.D2 = datasend.D2;
			}
		// Einstellen von D1 
			if (datasend.D1 != lastdata.D1 && datasend.D1 != 88) {
				GPIO_SET("D1", pinset.D1, datasend.D1);
				lastdata.D1 = datasend.D1;
			}
		// Einstellen von D0 
			if (datasend.D0 != lastdata.D0 && datasend.D0 != 88) {
				GPIO_SET("D0", pinset.D0, datasend.D0);
				lastdata.D0 = datasend.D0;
			}
		// Senden der Daten
			HD44780_enable();

	return datasend_error;
}

int HD44780_datasend(char RS, char RW, char D7, char D6, char D5, char D4, char D3, char D2, char D1, char D0) {

	/* Funktionsbeschreibung
		Diese Funktion sendet die Daten RS, RW, D7, D6, D5, D4, D3, D2, D1 und D0, mittels GPIO an die HD44780,
		dabei wird zwischen 8Bit und 4Bit Modus unterschieden.

		Wenn die eingehenden Argumente nicht 0, 1 oder 'X' entsprechen oder der BitModus nicht auf 4 oder 8 Bit eingestellt ist,
		wird die Funktion abgebrochen und der Wert 1 zurückgegeben,
	*/

	// Interne Variablen Initialisieren
		int datasend_error = 0;

	// Daten versenden
		// im 4 Bit Modus
			if (functionset.DL == 0) {
				datasend_error = HD44780_datasend_4bit(RS, RW, D7, D6, D5, D4, D3, D2, D1, D0);
			}
		// im 8 Bit Modus
			else if (functionset.DL == 1) {
				datasend_error = HD44780_datasend_8bit(RS, RW, D7, D6, D5, D4, D3, D2, D1, D0);
			}
		// Fehlerfall
			else {
				datasend_error = 1;
			}

	return datasend_error;
}

int HD44780_pinset(char EN, char RS, char RW, char D7, char D6, char D5, char D4, char D3, char D2, char D1, char D0) {

	/* Funktionsbeschreibung
	
	
	*/

	// Interne Variablen Initialisieren
		typedefstruct_pinset setpinto = { 
										((EN == 88) ? pinset.EN : EN) ,
										((RS == 88) ? pinset.RS : RS) ,
										((RW == 88) ? pinset.RW : RW) ,
										((D7 == 88) ? pinset.D7 : D7) ,
										((D6 == 88) ? pinset.D6 : D6) ,
										((D5 == 88) ? pinset.D5 : D5) ,
										((D4 == 88) ? pinset.D4 : D4) ,
										((D3 == 88) ? pinset.D3 : D3) ,
										((D2 == 88) ? pinset.D2 : D2) ,
										((D1 == 88) ? pinset.D1 : D1) ,
										((D0 == 88) ? pinset.D0 : D0) };
		int pinset_error = 0;

	// Argumente überprüfen
		// für 4 Bit Modus
			if (functionset.DL == 0) {
				if (setpinto.EN == setpinto.RS || setpinto.EN == setpinto.RW || setpinto.EN == setpinto.D7 || setpinto.EN == setpinto.D6 || setpinto.EN == setpinto.D5 || setpinto.EN == setpinto.D4 ||
					setpinto.RS == setpinto.RW || setpinto.RS == setpinto.D7 || setpinto.RS == setpinto.D6 || setpinto.RS == setpinto.D5 || setpinto.RS == setpinto.D4 ||
					setpinto.RW == setpinto.D7 || setpinto.RW == setpinto.D6 || setpinto.RW == setpinto.D5 || setpinto.RW == setpinto.D4 ||
					setpinto.D7 == setpinto.D6 || setpinto.D7 == setpinto.D5 || setpinto.D7 == setpinto.D4 ||
					setpinto.D6 == setpinto.D5 || setpinto.D6 == setpinto.D4 ||
					setpinto.D5 == setpinto.D4) {
					return pinset_error = 1;
				}
			}
		// für 8 Bit Modus
			else if (functionset.DL == 1) {
				if (setpinto.EN == setpinto.RS || setpinto.EN == setpinto.RW || setpinto.EN == setpinto.D7 || setpinto.EN == setpinto.D6 || setpinto.EN == setpinto.D5 || setpinto.EN == setpinto.D4 || setpinto.EN == setpinto.D3 || setpinto.EN == setpinto.D2 || setpinto.EN == setpinto.D1 || setpinto.EN == setpinto.D0 ||
					setpinto.RS == setpinto.RW || setpinto.RS == setpinto.D7 || setpinto.RS == setpinto.D6 || setpinto.RS == setpinto.D5 || setpinto.RS == setpinto.D4 || setpinto.RS == setpinto.D3 || setpinto.RS == setpinto.D2 || setpinto.RS == setpinto.D1 || setpinto.RS == setpinto.D0 ||
					setpinto.RW == setpinto.D7 || setpinto.RW == setpinto.D6 || setpinto.RW == setpinto.D5 || setpinto.RW == setpinto.D4 || setpinto.RW == setpinto.D3 || setpinto.RW == setpinto.D2 || setpinto.RW == setpinto.D1 || setpinto.RW == setpinto.D0 ||
					setpinto.D7 == setpinto.D6 || setpinto.D7 == setpinto.D5 || setpinto.D7 == setpinto.D4 || setpinto.D7 == setpinto.D3 || setpinto.D7 == setpinto.D2 || setpinto.D7 == setpinto.D1 || setpinto.D7 == setpinto.D0 ||
					setpinto.D6 == setpinto.D5 || setpinto.D6 == setpinto.D4 || setpinto.D6 == setpinto.D3 || setpinto.D6 == setpinto.D2 || setpinto.D6 == setpinto.D1 || setpinto.D6 == setpinto.D0 ||
					setpinto.D5 == setpinto.D4 || setpinto.D5 == setpinto.D3 || setpinto.D5 == setpinto.D2 || setpinto.D5 == setpinto.D1 || setpinto.D5 == setpinto.D0 ||
					setpinto.D4 == setpinto.D3 || setpinto.D4 == setpinto.D2 || setpinto.D4 == setpinto.D1 || setpinto.D4 == setpinto.D0 ||
					setpinto.D3 == setpinto.D2 || setpinto.D3 == setpinto.D1 || setpinto.D3 == setpinto.D0 ||
					setpinto.D2 == setpinto.D1 || setpinto.D2 == setpinto.D0 ||
					setpinto.D1 == setpinto.D0) {
					return pinset_error = 1;
				}
			}

	// Pins zuweisen und ausschalten
		// EN Pin
			GPIO_SET_OUT("EN", setpin.EN);
			GPIO_OFF("EN", setpin.EN);
			pinset.EN = setpin.EN;
		// RS Pin
			GPIO_SET_OUT("RS", setpin.RS);
			GPIO_OFF("RS", setpin.RS);
			pinset.RS = setpin.RS;
		// RW Pin
			GPIO_SET_OUT("RW", setpin.RW);
			GPIO_OFF("RW", setpin.RW);
			pinset.RW = setpin.RW;
		// D7 Pin
			GPIO_SET_OUT("D7", setpin.D7);
			GPIO_OFF("D7", setpin.D7);
			pinset.D7 = setpin.D7;
		// D6 Pin
			GPIO_SET_OUT("D6", setpin.D6);
			GPIO_OFF("D6", setpin.D6);
			pinset.D6 = setpin.D6;
		// D5 Pin
			GPIO_SET_OUT("D5", setpin.D5);
			GPIO_OFF("D5", setpin.D5);
			pinset.D5 = setpin.D5;
		// D4 Pin
			GPIO_SET_OUT("D4", setpin.D4);
			GPIO_OFF("D4", setpin.D4);
			pinset.D4 = setpin.D4;
		// D3 Pin
			GPIO_SET_OUT("D3", setpin.D3);
			GPIO_OFF("D3", setpin.D3);
			pinset.D3 = setpin.D3;
		// D2 Pin
			GPIO_SET_OUT("D2", setpin.D2);
			GPIO_OFF("D2", setpin.D2);
			pinset.D2 = setpin.D2;
		// D1 Pin
			GPIO_SET_OUT("D1", setpin.D1);
			GPIO_OFF("D1", setpin.D1);
			pinset.D1 = setpin.D1;
		// D0 Pin
			GPIO_SET_OUT("D0", setpin.D0);
			GPIO_OFF("D0", setpin.D0);
			pinset.D0 = setpin.D0;

	return pinset_error;
}