/**********************************************************************\
* Kurzbeschreibung:
*
* Datum:       Autor:        Grund der Aenderung:
* 09.08.2018   Carmin Kern   Neuerstellung
*
\**********************************************************************/


#ifndef HD44780_H
#define HD44780_H


/*--- #defines ------------------------------------------------------ */

//	printfs
#   define PRINT_TEST							printf("\n[ TEST ] ");
#	define PRINT_ERROR							printf("\n[ ERROR] ");
#	define PRINT_FAILED							printf("\n[FAILED] ");
#	define PRINT_OK								printf("\n[  OK  ] ");

			

// DE
	// printfs lang
#		define PRINT_GPIO_INI					printf("%s - Initialisieren", GPIO_H);
#		define PRINT_GPIO_SET_OUT(port,pin)		printf("%s - Setze Pin %2i (%s) auf OUTPUT", GPIO_H, pin, port); 
#		define PRINT_GPIO_SET_IN(port,pin)		printf("%s - Setze Pin %2i (%s) auf INPUT", GPIO_H, pin, port); 
	// ERRORs

#		define PRINT_ERROR_PINSET_PINISBUSY		printf("PIN EINSTELLUNGEN - EINGABEFEHLER - Mehrfache Pinbelegung");
#		define PRINT_ERROR_PINSET_WRONGDL		printf("PIN EINSTELLUNGEN - EINGABEFEHLER - Ungueltige Datenlaenge");
#		define PRINT_ERROR_FUNCTIONSET_WRONG_DL	printf("FUNKTIONS EINSTELLUNGEN - EINGABEFEHLER - Ungueltige Datenlaenge");
#		define PRINT_ERROR_FUNCTIONSET_WRONG_N	printf("FUNKTIONS EINSTELLUNGEN - EINGABEFEHLER - Ungueltige Zeilenanzahl");
#		define PRINT_ERROR_FUNCTIONSET_WRONG_F	printf("FUNKTIONS EINSTELLUNGEN - EINGABEFEHLER - Ungueltige Pixelgroesse");

// GPIO
#	ifdef PIGPIO_H
	// 1 PIGPIO
#		include "pigpio.h"
#
#   	define GPIO_INI()						if (gpioInitialise() < 0){PRINT_FAILED}else{PRINT_OK}; PRINT_GPIO_INI
#
#	    define GPIO_SET_OUT(pin)				gpioSetMode(pin, PI_OUTPUT); if(gpioGetMode(pin)!=PI_OUTPUT){PRINT_FAILED}else{PRINT_OK}; PRINT_GPIO_SET_OUT(port,pin)
#	    define GPIO_SET_IN(pin)					gpioSetMode(pin, PI_INPUT); if(gpioGetMode(pin)!=PI_INPUT){PRINT_FAILED}else{PRINT_OK}; PRINT_GPIO_SET_IN(port,pin)
#  		define GPIO_OFF(pin)					gpioWrite(pin, 0);
#    	define GPIO_ON(pin)				        gpioWrite(pin, 1);
#		define GPIO_X(pin)
#	else

	// 0 NONE
#		define GPIO_H "NONE"
#		// no include 
#
#	    define GPIO_INI()						PRINT_TEST PRINT_GPIO_INI
#
#		define GPIO_SET_OUT(port,pin)			PRINT_TEST PRINT_GPIO_SET_OUT(port,pin)
#   	define GPIO_SET_IN(port,pin)			PRINT_TEST PRINT_GPIO_SET_IN(port,pin)
#    	define GPIO_OFF(pin)					PRINT_TEST printf("Pin %i ausschalten", pin)
#		define GPIO_ON(pin)						PRINT_TEST printf("Pin %i einschalten", pin)
#
#	endif // GPIO_H == NONE

// ERRORs

#define ERROR_PINSET_PINISBUSY			PRINT_ERROR PRINT_ERROR_PINSET_PINISBUSY
#define ERROR_PINSET_WRONGDL			PRINT_ERROR PRINT_ERROR_PINSET_WRONGDL
#define ERROR_FUNCTIONSET_WRONG_DL		PRINT_ERROR PRINT_ERROR_FUNCTIONSET_WRONG_DL
#define ERROR_FUNCTIONSET_WRONG_N		PRINT_ERROR PRINT_ERROR_FUNCTIONSET_WRONG_N
#define	ERROR_FUNCTIONSET_WRONG_F		PRINT_ERROR PRINT_ERROR_FUNCTIONSET_WRONG_F


/*--- Strukturdefinitionen und Variablen ------------------------------*/

typedef struct {
	char EN;
	char RS;
	char RW;
	char D7;
	char D6;
	char D5;
	char D4;
	char D3;
	char D2;
	char D1;
	char D0;
}typedefstruct_pinset;

typedef struct {
	char DL;						// 0 : 4 Bit Modus	| 1 : 8 Bit Modus
	char N;							// 0 : 1 Zeile		| 1 : 2 Zeilen
	char F;							// 0 : 5x8 Pixel	| 1 : 5x10 Pixel
}typedefstruct_functionset;


/*--- Variablendefinitionen ------------------------------------------*/


/*--- Funktionsdefinitionen ------------------------------------------*/
extern int HD44780_initialize(char, char, char, char, char, char, char, char, char, char, char, char, char, char);
extern int HD44780_pinset(char, typedefstruct_pinset);
extern int HD44780_functionset(typedefstruct_functionset);



#endif // HD44780_H
