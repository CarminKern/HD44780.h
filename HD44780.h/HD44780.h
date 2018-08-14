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
#   define PRINT_TEST                   printf("\n[ TEST ] ");
#	define PRINT_FAILED					printf("\n[FAILED] ");
#	define PRINT_OK						printf("\n[  OK  ] ");

			
// printfs lang
// DE
#	define PRINT_GPIO_INI				printf("%s - Initialisieren", GPIO_H);
#	define PRINT_GPIO_SET_OUT(port,pin)	printf("%s - Setze Pin %2i (%s) auf OUTPUT", GPIO_H, pin, port); 
#	define PRINT_GPIO_SET_IN(port,pin)	printf("%s - Setze Pin %2i (%s) auf INPUT", GPIO_H, pin, port); 


// 1 PIGPIO
#	ifdef PIGPIO_H
#		include "pigpio.h"
#
#   	define GPIO_INI()           if (gpioInitialise() < 0){PRINT_FAILED}else{PRINT_OK};; PRINT_GPIO_INI;
#
#	    define GPIO_SET_OUT(pin)    gpioSetMode(pin, PI_OUTPUT); if(gpioGetMode(pin)!=PI_OUTPUT){PRINT_FAILED}else{PRINT_OK}; PRINT_GPIO_SET_OUT(port,pin);
#	    define GPIO_SET_IN(pin)	    gpioSetMode(pin, PI_INPUT); if(gpioGetMode(pin)!=PI_INPUT){PRINT_FAILED}else{PRINT_OK}; PRINT_GPIO_SET_IN(port,pin);
#  		define GPIO_OFF(pin)        gpioWrite(pin, 0);
#    	define GPIO_ON(pin)         gpioWrite(pin, 1);
#		define GPIO_X(pin)
#	else

// 0 NONE
#		define GPIO_H "NONE"
#		// no include 
#
#	    define GPIO_INI()				PRINT_TEST; PRINT_GPIO_INI;
#
#		define GPIO_SET_OUT(port,pin)	PRINT_TEST; PRINT_GPIO_SET_OUT(port,pin);
#   	define GPIO_SET_IN(port,pin)	PRINT_TEST; PRINT_GPIO_SET_IN(port,pin);
#    	define GPIO_OFF(pin)			PRINT_TEST; printf("Pin %i ausschalten", pin);
#		define GPIO_ON(pin)				PRINT_TEST; printf("Pin %i einschalten", pin);
#
#	endif // GPIO_H == NONE

// default Werte

#define DEFAULT_FUNKTIONSET_DL 1
#define DEFAULT_FUNKTIONSET_N 1
#define DEFAULT_FUNKTIONSET_F 0

/*--- Strukturdefinitionen und Variablen ------------------------------*/

typedef struct typedefstruct_pinset {
	char EN_pin;
	char RS_pin;
	char RW_pin;
	char D7_pin;
	char D6_pin;
	char D5_pin;
	char D4_pin;
	char D3_pin;
	char D2_pin;
	char D1_pin;
	char D0_pin;
}typedefstruct_pinset;

typedef struct {
	char DL;						// 0 : 4 Bit Modus	| 1 : 8 Bit Modus
	char N;							// 0 : 1 Zeile		| 1 : 2 Zeilen
	char F;							// 0 : 5x8 Pixel	| 1 : 5x10 Pixel
}typedefstruct_funktionset;


/*--- Variablendefinitionen ------------------------------------------*/


/*--- Funktionsdefinitionen ------------------------------------------*/
extern void HD44780_pinset(typedefstruct_pinset);
extern int HD44780_initialize(char, char, char, char, char, char, char, char, char, char, char, char, char, char);

#endif // HD44780_H
