

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

/*--- Globale Strukturen initialisierne ----------------------------- */

typdefstruct_datasend lastdata = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
typedefstruct_pinset pinset = { DEFAULT_PINSET_EN , DEFAULT_PINSET_RS , DEFAULT_PINSET_RW , DEFAULT_PINSET_D7 , DEFAULT_PINSET_D6 , DEFAULT_PINSET_D5 , DEFAULT_PINSET_D4 , DEFAULT_PINSET_D3 , DEFAULT_PINSET_D2 , DEFAULT_PINSET_D1 , DEFAULT_PINSET_D0 };
typedefstruct_functionset functionset = { DEFAULT_FUNCTIONSET_DL , DEFAULT_FUNCTIONSET_N , DEFAULT_FUNCTIONSET_F };

/*--- Funktionen ---------------------------------------------------- */


void HD44780_enable() {

	// Wartezeit für GPIO umschaltung
		DELAY_GPIO;
	// Einstellen von EN Pin 
		GPIO_SET("EN", pinset.EN, 1);
	// Wartezeit für Enable umschaltung
		DELAY_ENABLE;
	// Einstellen von EN Pin
		GPIO_SET("EN", pinset.EN, 0);

}

int HD44780_datasend(char RS, char RW, char D7, char D6, char D5, char D4, char D3, char D2, char D1, char D0) {

	typdefstruct_datasend datasend = { RS , RW , D7 , D6 , D5 , D4 , D3 , D2 , D1 , D0 };
	int datasend_error = 0;

	// Parameter überprüfen
		if ((RS != 0 && RS != 1 && RS != 88) || (RW != 0 && RW != 1 && RW != 88) || (D7 != 0 && D7 != 1 && D7 != 88) || (D6 != 0 && D6 != 1 && D6 != 88) || (D5 != 0 && D5 != 1 && D5 != 88) || (D4 != 0 && D4 != 1 && D4 != 88) || (D3 != 0 && D3 != 1 && D3 != 88) || (D2 != 0 && D2 != 1 && D2 != 88) || (D1 != 0 && D1 != 1 && D1 != 88) || (D0 != 0 && D0 != 1 && D0 != 88)) {
		// Abbruch wenn die Parameter 0/1 oder 'X' sind
			/*FEHLERMELDUNG -> Parameter entsprechen nicht 0 / 1 / X */
			return datasend_error = 1;
	}

	// Senden an HD44780 ( Die Einstellungen werden nicht verstellt, wenn der Parameter 'X' (Dont Care) ist oder der Parameter dem letzten eingestellten Wert entspricht)
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
		// Aufteilung wenn im 4 Bit Modus gesendet wird
			if (functionset.DL == 0) {
				// Datenhälfte absenden
					HD44780_enable();
				// Einstellen von RS für zweite Datenhälfte
					if (0 != lastdata.RS) {
						GPIO_SET("RS", pinset.RS, 0);
						lastdata.RS = 0;
					}
				// Einstellen von RW für zweite Datenhälfte
					if (0 != lastdata.RW) {
						GPIO_SET("RW", pinset.RW, 0);
						lastdata.RW = 0;
					}
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

int HD44780_pinset(char EN, char RS, char RW, char D7, char D6, char D5, char D4, char D3, char D2, char D1, char D0) {

	typedefstruct_pinset setpinto = { EN , RS , RW , D7 , D6 , D5 , D4 , D3 , D2 , D1 , D0 };

	int pinset_error = 0;

	// Parameter überprüfen
		// für 4 Bit Modus
			if (functionset.DL == 0) {
				if (setpinto.EN == setpinto.RS || setpinto.EN == setpinto.RW || setpinto.EN == setpinto.D7 || setpinto.EN == setpinto.D6 || setpinto.EN == setpinto.D5 || setpinto.EN == setpinto.D4 ||
					setpinto.RS == setpinto.RW || setpinto.RS == setpinto.D7 || setpinto.RS == setpinto.D6 || setpinto.RS == setpinto.D5 || setpinto.RS == setpinto.D4 ||
					setpinto.RW == setpinto.D7 || setpinto.RW == setpinto.D6 || setpinto.RW == setpinto.D5 || setpinto.RW == setpinto.D4 ||
					setpinto.D7 == setpinto.D6 || setpinto.D7 == setpinto.D5 || setpinto.D7 == setpinto.D4 ||
					setpinto.D6 == setpinto.D5 || setpinto.D6 == setpinto.D4 ||
					setpinto.D5 == setpinto.D4) {
					/*FEHLERMELDUNG -> Parameter sind mehrfach vorhanden*/
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
					/*FEHLERMELDUNG -> Parameter sind mehrfach vorhanden*/
					return pinset_error = 1;
				}
			}

	// Port Einstellungen
		// Port den Pins zuweisen
			pinset = setpinto;

		// Pins als Output festlegen und ausschalten
			// EN Pin
				GPIO_SET_OUT("EN", pinset.EN)
				GPIO_OFF("EN", pinset.EN)
			// RS Pin
				GPIO_SET_OUT("RS", pinset.RS)
				GPIO_OFF("RS", pinset.RS)
			// RW Pin
				GPIO_SET_OUT("RW", pinset.RW)
				GPIO_OFF("RW", pinset.RW)
			// D7 Pin
				GPIO_SET_OUT("D7", pinset.D7)
				GPIO_OFF("D7", pinset.D7)
			// D6 Pin
				GPIO_SET_OUT("D6", pinset.D6)
				GPIO_OFF("D6", pinset.D6)
			// D5 Pin
				GPIO_SET_OUT("D5", pinset.D5)
				GPIO_OFF("D5", pinset.D5)
			// D4 Pin
				GPIO_SET_OUT("D4", pinset.D4)
				GPIO_OFF("D4", pinset.D4)
			// Pins als Output festlegen und ausschalten für 8 Bit Modus
				if (functionset.DL == 1) {
					// D3 Pin
						GPIO_SET_OUT("D3", pinset.D3)
						GPIO_OFF("D3", pinset.D3)
					// D2 Pin
						GPIO_SET_OUT("D2", pinset.D2)
						GPIO_OFF("D2", pinset.D2)
					// D1 Pin
						GPIO_SET_OUT("D1", pinset.D1)
						GPIO_OFF("D1", pinset.D1)
					// D0 Pin
						GPIO_SET_OUT("D0", pinset.D0)
						GPIO_OFF("D0", pinset.D0)
				}

	return pinset_error;
}

int HD44780_functionset(char DL, char N, char F) {

	typedefstruct_functionset setfunctionto = { DL , N, F };

	int functionset_error = 0;

	// Parameter überprüfen
		if ( (setfunctionto.DL != 4 && setfunctionto.DL != 8 && setfunctionto.DL != 88) || (setfunctionto.N != 1 && setfunctionto.N != 2 && setfunctionto.N != 4 && setfunctionto.N != 88) || (setfunctionto.F != 8 && setfunctionto.F != 10 && setfunctionto.F != 88) ) {
			// DL Parameter überprüfen
				if (setfunctionto.DL != 4 && setfunctionto.DL != 8 && setfunctionto.DL != 88) {
					/*FEHLERMELDUNG -> Parameter entsprechen nicht 4 / 8 / X */
				}
			// N Parameter überprüfen
				if (setfunctionto.N != 1 && setfunctionto.N != 2 && setfunctionto.N != 4 && setfunctionto.N != 88) {
					/*FEHLERMELDUNG -> Parameter entsprechen nicht 1 / 2/4 / X */
				}
			// F Parameter überprüfen
				if (setfunctionto.F != 8 && setfunctionto.F != 10 && setfunctionto.F != 88) {
					/*FEHLERMELDUNG -> Parameter entsprechen nicht 8 / 10 / X */
				}
			// Abbruch wegen ungültigen Parametern
				return functionset_error = 1;
		}
	
	// Funktionen Einstellen
		// DL - Data length
			/*
				Legt die Schnittstellendatenlänge fest.
				4 -> 0 = 4 Bit Modus (DB7 - DB4)
				8 -> 1 = 8 Bit Modus (DB7 - DB0)
			*/
			if (setfunctionto.DL == 4) {
				functionset.DL = 0;
				// MELDUNG ?
			}
			else if (setfunctionto.DL == 8) {
				functionset.DL = 1;
				// MELDUNG ?
			}
			else {
				functionset.DL = 88;
				// MELDUNG ?
			}

		// N - Numbers of Display Lines
			/*
				Legt die Anzahl der Displayzeilen fest.
				1 -> 0 = 1 Zeile
				2 -> 1 = 2 Zeilen
				4 -> 1 = 4 Zeilen
			*/
			if (setfunctionto.N == 1) {
				functionset.N = 0;
				// MELDUNG ?
			}
			else if (setfunctionto.N == 2 || setfunctionto.N == 4) {
				functionset.N = 1;
				// MELDUNG ?
			}
			else {
				functionset.N = 88;
				// MELDUNG ?
			}

		// F - Fonts
			/*
				Legt die Pixelgröße fest.
				 8 -> 0 = 5x8  Pixel
				10 -> 1 = 5x10 Pixel
			*/
			if (setfunctionto.F == 8) {
				functionset.F = 0;
				// MELDUNG ?
			}
			else if (setfunctionto.F == 10){
				functionset.F = 1;
				// MELDUNG ?
			}
			else {
				functionset.F = 88;
				// Meldung ?
			}

	// Daten an HD44780 senden
		HD44780_datasend( 0 , 0 , 0 , 0 , 1 , functionset.DL , functionset.N , functionset.F , 'X' , 'X' );

	return functionset_error;
}

int HD44780_initialize(char EN, char RS, char RW, char D7, char D6, char D5, char D4, char D3, char D2, char D1, char D0, char DL, char N, char F) {

	typedefstruct_pinset setpinto = { EN , RS , RW , D7 , D6 , D5 , D4 , D3 , D2 , D1 , D0 };
	typedefstruct_functionset setfunktionto = { DL , N , F };

	int initialize_error = 0;

	// Parameter überprüfung
		if (DL != 4 && DL != 8 && DL != 88) {
			/*FEHLERMELDUNG -> Parameter entsprechen nicht 4 / 8 / X */

			// Abbruch wegen ungültigen Parametern
				return initialize_error = 1;
		}

	// Funktionsparameter DL (im vorfeld setzen)
		if (DL == 4) {
			functionset.DL = 0;
			// MELDUNG ?
		}
		else if (DL == 8) {
			functionset.DL = 1;
			// MELDUNG ?
		}
		else {
			functionset.DL = 88;
			// MELDUNG ?
		}

	// Pin & Port Einstellungen mit überprüfung
		if (HD44780_pinset( EN , RS , RW , D7 , D6 , D5 , D4 , D3 , D2 , D1 , D0 ) == 1) {
			// FEHLERMELDUNG ABBRUCH INITIALISIERUNG
			return initialize_error = 1;
		}

	// HD44780 Initialisierung
		// 
			DELAY_MS(40);
			if (HD44780_datasend( 0 , 0 , 0 , 0 , 1 , 1 ,'X','X','X','X') == 1) {
				// FEHLERMELDUNG ABBRUCH INITIALISIERUNG
				return initialize_error = 1;
			}
			DELAY_MS(5);
			if (HD44780_datasend(0, 0, 0, 0, 1, 1, 'X', 'X', 'X', 'X') == 1) {
				// FEHLERMELDUNG ABBRUCH INITIALISIERUNG
				return initialize_error = 1;
			}
			DELAY_MS(1);
			if (HD44780_datasend(0, 0, 0, 0, 1, 1, 'X', 'X', 'X', 'X') == 1) {
				// FEHLERMELDUNG ABBRUCH INITIALISIERUNG
				return initialize_error = 1;
			}
			DELAY_MS(1);

	// Functionset mit überprüfung
		if (HD44780_functionset( DL , N , F) == 1) {
			// FEHLERMELDUNG ABBRUCH INITIALISIERUNG
			return initialize_error = 1;
		}

	// Display OFF

	// DISPLAY CLEAR

	// ENTRY MODE SET


	return initialize_error;
}

int main(void) {
	printf("HD44780.c - Starte Test");
	
	HD44780_initialize(13, 19, 26, 25, 8, 7, 1, 12, 16, 20, 21, 8, 2, 8);

	getchar();
}