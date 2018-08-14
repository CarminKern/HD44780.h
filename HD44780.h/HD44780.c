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
#define DEFAULT_PINSET_EN 22
#define DEFAULT_PINSET_RS 17
#define DEFAULT_PINSET_RW 27
#define DEFAULT_PINSET_D7 21
#define DEFAULT_PINSET_D6 20
#define DEFAULT_PINSET_D5 16
#define DEFAULT_PINSET_D4 12
#define DEFAULT_PINSET_D3 1
#define DEFAULT_PINSET_D2 7
#define DEFAULT_PINSET_D1 8
#define DEFAULT_PINSET_D0 25

#define DEFAULT_FUNCTIONSET_DL 1
#define DEFAULT_FUNCTIONSET_N 1
#define DEFAULT_FUNCTIONSET_F 0

/*--- typedef und Variablen------------------------------------------ */
typedefstruct_pinset pinset = { DEFAULT_PINSET_EN , DEFAULT_PINSET_RS , DEFAULT_PINSET_RW , DEFAULT_PINSET_D7 , DEFAULT_PINSET_D6 , DEFAULT_PINSET_D5 , DEFAULT_PINSET_D4 , DEFAULT_PINSET_D3 , DEFAULT_PINSET_D2 , DEFAULT_PINSET_D1 , DEFAULT_PINSET_D0  };
typedefstruct_functionset functionset = { DEFAULT_FUNCTIONSET_DL , DEFAULT_FUNCTIONSET_N , DEFAULT_FUNCTIONSET_F };


/*--- getVar ---------------------------------------------------------*/



/*--- Funktionen -----------------------------------------------------*/

int main(void) {
	printf("\n Starte test...\n\n");
	printf("\nEN %d RS %d RW %d D7 %d D6 %d D5 %d D4 %d D3 %d D2 %d D1 %d D0 %d", pinset.EN, pinset.RS, pinset.RW, pinset.D7, pinset.D6, pinset.D5, pinset.D4, pinset.D3, pinset.D2, pinset.D1, pinset.D0);
	HD44780_initialize(10,9,8,7,6,5,4,3,3,1,0,8,2,10);
	printf("\nEN %d RS %d RW %d D7 %d D6 %d D5 %d D4 %d D3 %d D2 %d D1 %d D0 %d", pinset.EN, pinset.RS, pinset.RW, pinset.D7, pinset.D6, pinset.D5, pinset.D4, pinset.D3, pinset.D2, pinset.D1, pinset.D0);
	HD44780_initialize(10, 9, 8, 7, 6, 5, 4, 3, 3, 1, 0, 4, 2, 10);
	printf("\nEN %d RS %d RW %d D7 %d D6 %d D5 %d D4 %d D3 %d D2 %d D1 %d D0 %d", pinset.EN, pinset.RS, pinset.RW, pinset.D7, pinset.D6, pinset.D5, pinset.D4, pinset.D3, pinset.D2, pinset.D1, pinset.D0);
	HD44780_initialize(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 8, 2, 10);
	printf("\nEN %d RS %d RW %d D7 %d D6 %d D5 %d D4 %d D3 %d D2 %d D1 %d D0 %d", pinset.EN, pinset.RS, pinset.RW, pinset.D7, pinset.D6, pinset.D5, pinset.D4, pinset.D3, pinset.D2, pinset.D1, pinset.D0);
	getchar();
}

int HD44780_pinset(typedefstruct_pinset setpinto) {

	typedefstruct_pinset save_pinset = pinset;
	int pinset_error = 0;
	
	pinset = setpinto;

	if (setpinto.D3 == 88 && setpinto.D2 == 88 && setpinto.D1 == 88 && setpinto.D0 == 88) {
		if (pinset.EN == pinset.RS || pinset.EN == pinset.RW || pinset.EN == pinset.D7 || pinset.EN == pinset.D6 || pinset.EN == pinset.D5 || pinset.EN == pinset.D4 ||
			pinset.RS == pinset.RW || pinset.RS == pinset.D7 || pinset.RS == pinset.D6 || pinset.RS == pinset.D5 || pinset.RS == pinset.D4 ||
			pinset.RW == pinset.D7 || pinset.RW == pinset.D6 || pinset.RW == pinset.D5 || pinset.RW == pinset.D4 ||
			pinset.D7 == pinset.D6 || pinset.D7 == pinset.D5 || pinset.D7 == pinset.D4 ||
			pinset.D6 == pinset.D5 || pinset.D6 == pinset.D4 ||
			pinset.D5 == pinset.D4) {
			pinset_error = 1;
			printf("doppelte belegung 4bit");
		}
	}
	else {
		if (pinset.EN == pinset.RS || pinset.EN == pinset.RW || pinset.EN == pinset.D7 || pinset.EN == pinset.D6 || pinset.EN == pinset.D5 || pinset.EN == pinset.D4 || pinset.EN == pinset.D3 || pinset.EN == pinset.D2 || pinset.EN == pinset.D1 || pinset.EN == pinset.D0 ||
			pinset.RS == pinset.RW || pinset.RS == pinset.D7 || pinset.RS == pinset.D6 || pinset.RS == pinset.D5 || pinset.RS == pinset.D4 || pinset.RS == pinset.D3 || pinset.RS == pinset.D2 || pinset.RS == pinset.D1 || pinset.RS == pinset.D0 ||
			pinset.RW == pinset.D7 || pinset.RW == pinset.D6 || pinset.RW == pinset.D5 || pinset.RW == pinset.D4 || pinset.RW == pinset.D3 || pinset.RW == pinset.D2 || pinset.RW == pinset.D1 || pinset.RW == pinset.D0 ||
			pinset.D7 == pinset.D6 || pinset.D7 == pinset.D5 || pinset.D7 == pinset.D4 || pinset.D7 == pinset.D3 || pinset.D7 == pinset.D2 || pinset.D7 == pinset.D1 || pinset.D7 == pinset.D0 ||
			pinset.D6 == pinset.D5 || pinset.D6 == pinset.D4 || pinset.D6 == pinset.D3 || pinset.D6 == pinset.D2 || pinset.D6 == pinset.D1 || pinset.D6 == pinset.D0 ||
			pinset.D5 == pinset.D4 || pinset.D5 == pinset.D3 || pinset.D5 == pinset.D2 || pinset.D5 == pinset.D1 || pinset.D5 == pinset.D0 ||
			pinset.D4 == pinset.D3 || pinset.D4 == pinset.D2 || pinset.D4 == pinset.D1 || pinset.D4 == pinset.D0 ||
			pinset.D3 == pinset.D2 || pinset.D3 == pinset.D1 || pinset.D3 == pinset.D0 ||
			pinset.D2 == pinset.D1 || pinset.D2 == pinset.D0 ||
			pinset.D1 == pinset.D0) {
			pinset_error = 1;
			printf("doppelte belegung 8bit");
		}
	}
	if (pinset_error == 1) {
		pinset = save_pinset;
		return pinset_error;
	}

	GPIO_SET_OUT("EN", pinset.EN)
	GPIO_SET_OUT("RS", pinset.RS)
	GPIO_SET_OUT("RW", pinset.RW)
	GPIO_SET_OUT("D7", pinset.D7)
	GPIO_SET_OUT("D6", pinset.D6)
	GPIO_SET_OUT("D5", pinset.D5)
	GPIO_SET_OUT("D4", pinset.D4)
	if (!(setpinto.D3 == 88 && setpinto.D2 == 88 && setpinto.D1 == 88 && setpinto.D0 == 88)) {
		GPIO_SET_OUT("D3", pinset.D3)
		GPIO_SET_OUT("D2", pinset.D2)
		GPIO_SET_OUT("D1", pinset.D1)
		GPIO_SET_OUT("D0", pinset.D0)
	}

	return pinset_error;
}

int HD44780_initialize(char EN_pin, char RS_pin, char RW_pin, char D7_pin, char D6_pin, char D5_pin, char D4_pin, char D3_pin, char D2_pin, char D1_pin, char D0_pin, char functionset_DL, char functionset_N, char functionset_F) {
	
	// GPIO Initialisieren
		GPIO_INI()

	// Pin einstellungen für 4 Bit Modus
		if (functionset_DL == 4) {
			typedefstruct_pinset setpinto = { EN_pin, RS_pin, RW_pin, D7_pin, D6_pin, D5_pin, D4_pin, 88, 88, 88, 88 };
			if (HD44780_pinset(setpinto) == 1) {
				return 0;
			}
		}
	// Pin einstellungen für 8 Bit Modus
		else if (functionset_DL == 8) {
			typedefstruct_pinset setpinto = { EN_pin, RS_pin, RW_pin, D7_pin, D6_pin, D5_pin, D4_pin, D3_pin, D2_pin, D1_pin, D0_pin };
			if (HD44780_pinset(setpinto) == 1) {
				return 0;
			}
		}

	// Functionset einstellungen
		// DL - Data length
		/*	
			Legt die Schnittstellendatenlänge fest. 
			0 = 4 Bit Modus (DB7 - DB4)
			1 = 8 Bit Modus (DB7 - DB0) 
		*/
			if (functionset_DL == 4) {
				functionset.DL = 0;
			}
			else if (functionset_DL == 8) {
				functionset.DL = 1;
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
			if (functionset_N == 1) {
				functionset.N = 0;
			}
			else if (functionset_N == 2 || functionset_N == 4) {
				functionset.N = 1;
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
			if (functionset_F == 8) {
				functionset.F = 0;
			}
			else if (functionset_F == 10) {
				functionset.F = 1;
			}
			else {
				return 0;													// Funktionsabbruch wegen falscher Eingabe
			}

		// Daten an HD44780 senden

		
	return 0;
}