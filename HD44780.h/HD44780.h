#ifndef HD44780_H
#define HD44780_H

/*--- #defines ------------------------------------------------------ */

// DELAYs

#	define DELAY_MS(zeit)
#	define DELAY_GPIO
#	define DELAY_ENABLE


// ...
#	define PRINT_OK											printf("\n[  OK  ] ");
#	define PRINT_FAILED										printf("\n[FAILED] ");
#	define PRINT_ERROR										printf("\n[ ERROR] ");
#   define PRINT_TEST										printf("\n[ TEST ] ");

// PRINTs 
	// DE
#		define PRINT_GPIO_INI								printf("%s - Initialisieren", GPIO_H);
#		define PRINT_GPIO_SET_OUT(port,pin)					printf("%s - Setze Pin %2i (%s) auf OUTPUT", GPIO_H, pin, port); 
#		define PRINT_GPIO_SET_IN(port,pin)					printf("%s - Setze Pin %2i (%s) auf INPUT", GPIO_H, pin, port); 

// GPIOs
#		define GPIO_H "NONE"
#		// no include 
#
#	    define GPIO_INI()									PRINT_TEST PRINT_GPIO_INI
#
#		define GPIO_SET_OUT(port,pin)						PRINT_TEST PRINT_GPIO_SET_OUT(port,pin)
#   	define GPIO_SET_IN(port,pin)						PRINT_TEST PRINT_GPIO_SET_IN(port,pin)
#    	define GPIO_OFF(port, pin)							PRINT_TEST printf("Pin %2i (%s) ausschalten", pin, port);
#		define GPIO_ON(port, pin)							PRINT_TEST printf("Pin %2i (%s) einschalten", pin, port);
#		define GPIO_SET(port, pin, var)						if(var==0){GPIO_OFF(port, pin)}else{GPIO_ON(port, pin)};

/*--- Variablendefinitionen ----------------------------------------- */


/*--- Strukturdefinitionen ------------------------------------------ */

typedef struct {
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
}typdefstruct_datasend;

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

typedef struct typedefstruct_functionset {
	char DL;						// 0 : 4 Bit Modus	| 1 : 8 Bit Modus
	char N;							// 0 : 1 Zeile		| 1 : 2 Zeilen
	char F;							// 0 : 5x8 Pixel	| 1 : 5x10 Pixel
}typedefstruct_functionset;

/*--- Funktionsdefinitionen ----------------------------------------- */

// Funktion zum senden von Daten an HD44780
extern void HD44780_enable();
extern int HD44780_datasend(char, char, char, char, char, char, char, char, char, char);
extern int HD44780_pinset(char, char, char, char, char, char, char, char, char, char, char);
extern int HD44780_functionset(char, char, char);
extern int HD44780_initialize();

#endif//HD44780_H