#ifndef HD44780_H
#define HD44780_H


/*--- #defines ------------------------------------------------------ */

//	printfs
#   define PRINT_TEST                   printf("\n[ TEST ] ");
#	define PRINT_FAILED					printf("\n[FAILED] ");
#	define PRINT_OK						printf("\n[  OK  ] ");
#	define PRINTF_MSG(msg)				printf("%s", msg);
#	define PRINTF_VAR2_MSG(var, msg)	printf("%2d %s",var,msg);


// GPIO

// 1 PIGPIO
#	ifdef PIGPIO_H
#		include "pigpio.h"
#
#   	define GPIO_INI()           if (gpioInitialise() < 0){PRINT_FAILED}else{PRINT_OK};PRINTF_MSG("PIGPIO - ");PRINTF_MSG("Initialisieren");
#
#	    define GPIO_SET_OUT(pin)    gpioSetMode(pin, PI_OUTPUT); if(gpioGetMode(pin)!=PI_OUTPUT){PRINT_FAILED}else{PRINT_OK};PRINTF_MSG("PIGPIO - ");PRINTF_VAR2_MSG(pin, "auf Output setzen");
#	    define GPIO_SET_IN(pin)	    gpioSetMode(pin, PI_INPUT); if(gpioGetMode(pin)!=PI_INPUT){PRINT_FAILED}else{PRINT_OK};PRINTF_MSG("PIGPIO - ");PRINTF_VAR2_MSG(pin, "auf Input setzen");
#  		define GPIO_OFF(pin)        gpioWrite(pin, 0);
#    	define GPIO_ON(pin)         gpioWrite(pin, 1);
#		define GPIO_X(pin)
#
#	else

// 0 NONE
#   
#		/*include <pigpio.h>*/
#
#	    define GPIO_INI()           PRINT_TEST;PRINTF_MSG("NONE GPIO - ");PRINTF_MSG("Initialisieren");
#
#		define GPIO_SET_OUT(pin)    PRINT_TEST;PRINTF_MSG("NONE GPIO - ");PRINTF_VAR2_MSG(pin, "auf Output setzen");
#   	define GPIO_SET_IN(pin)	    PRINT_TEST;PRINTF_MSG("NONE GPIO - ");PRINTF_VAR2_MSG(pin, "auf Input setzen");
#    	define GPIO_OFF(pin)        PRINT_TEST;PRINTF_MSG("NONE GPIO - ");PRINTF_VAR2_MSG(pin, "AUS");
#		define GPIO_ON(pin)         PRINT_TEST;PRINTF_MSG("NONE GPIO - ");PRINTF_VAR2_MSG(pin, "AN");
#	    define GPIO_X(pin)          PRINT_TEST;PRINTF_MSG("NONE GPIO - ");PRINTF_VAR2_MSG(pin, "UNVERÄNDERT");
#
#	endif // GPIO_H == NONE

/*--- Funktionsdefinitionen ------------------------------------------*/
extern int HD44780variablen();
extern void HD44780Initialise(int, int, int, int, int, int, int, int, int, int, int);


#endif // HD44780_H
