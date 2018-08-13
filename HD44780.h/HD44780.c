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

char cleardisplay;
char returnhome;

HD44780_entrymode entrymode;
HD44780_diplaycontrol displaycontrol;
HD44780_funktionset funktionset;


/*--- Funktionen -----------------------------------------------------*/

void HD44780_Initialise(char EN_pin, char RS_pin, char RW_pin, char D7_pin, char D6_pin, char D5_pin, char D4_pin, char D3_pin, char D2_pin, char D1_pin, char D0_pin, char numberoflines) {

	// GPIO Initialisieren
		GPIO_INI();

	// GPIO Pin Einstellungen
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
	
	// Variablen Einstellungen
		// Clear Display
			/*
				Clear Display schreibt Space Code 20H (Zeichenmuster für Zeichencode 20H muss ein leeres Muster sein) in
				alle DDRAM-Adressen. Er setzt dann die DDRAM-Adresse 0 in den Adresszähler und gibt die Anzeige an
				sein ursprünglicher Status, wenn es verschoben wurde. Mit anderen Worten, die Anzeige verschwindet und der Cursor oder das Blinken geht zu
				der linke Rand der Anzeige (in der ersten Zeile, wenn 2 Zeilen angezeigt werden). Es setzt auch I / D auf 1 (Inkrement-Modus)
				im Eingabemodus. S des Eingangsmodus ändert sich nicht.
			*/
			cleardisplay = 0;

		// Return Home
			/*
				Return Home setzt die DDRAM-Adresse 0 in den Adresszähler und bringt die Anzeige in ihren ursprünglichen Zustand zurück
				wenn es verschoben wurde. Der Inhalt von DDRAM ändert sich nicht.
				Der Cursor oder das Blinken gehen zum linken Rand des Displays (in der ersten Zeile, wenn 2 Zeilen angezeigt werden).
			*/
			returnhome = 0;

		// Entry Mode
			// ID Inkrement/Dekrement
				/*
					Inkrementiert (ID = 1) oder dekrementiert (ID = 0) die DDRAM-Adresse um 1, wenn ein Zeichencode ist
					geschrieben oder gelesen von DDRAM.
				*/
				entrymode.ID = 0;
			// S
				/*
					Verschiebt die gesamte Anzeige entweder nach rechts (I / D = 0) oder nach links (I / D = 1), wenn S 1 ist. Das Display tut dies
					nicht verschieben, wenn S 0 ist.
					Wenn S 1 ist, wird es so aussehen, als würde sich der Cursor nicht bewegen, aber das Display tut es. Das Display schaltet nicht um
					Lesen von DDRAM. Wenn Sie in CGRAM schreiben oder auslesen, wird die Anzeige nicht verschoben.
				*/
				entrymode.S = 0;

		// Display ON/OFF Control
			// D
				/*
					Die Anzeige ist eingeschaltet, wenn D 1 ist, und aus, wenn D 0 ist. Wenn die Anzeige aus ist, bleiben die Anzeigedaten in DDRAM, aber
					kann sofort angezeigt werden, indem D auf 1 gesetzt wird.
				*/
				displaycontrol.D=1;
			// C
				/*
					Der Cursor wird angezeigt, wenn C 1 ist, und wird nicht angezeigt, wenn C 0 ist. Auch wenn der Cursor verschwindet, wird die
					Funktion der I / D oder andere Spezifikationen ändern sich nicht während des Schreibens der Anzeigedaten. Der Cursor wird angezeigt
					Verwenden Sie 5 Punkte in der 8. Zeile für 5 '8 Punkt Schriftart Auswahl und in der 11. Zeile für die 5' 10 Punkt
					Schriftartauswahl (Abbildung 13).
				*/
				displaycontrol.C=1;
			// B
				/*
					Das durch den Cursor angezeigte Zeichen blinkt, wenn B den Wert 1 hat (Abbildung 13). Das Blinken wird als angezeigt
					Umschalten zwischen allen leeren Punkten und angezeigten Zeichen mit einer Geschwindigkeit von 409,6 ms bei fcp oder fOSC
					ist 250 kHz. Der Cursor und das Blinken können so eingestellt werden, dass sie gleichzeitig angezeigt werden. (Die Blinkfrequenz ändert sich
					nach fOSC oder dem reziproken von fcp. Zum Beispiel, wenn fcp 270 kHz ist, 409,6 '250/270 = 379,2 ms.)
				*/
				displaycontrol.B=0;

		// Function Set
			// DL
				/*
					Legt die Schnittstellendatenlänge fest. Daten werden in 8-Bit-Längen (DB7 bis DB0) gesendet oder empfangen, wenn DL 1 ist,
					und in 4-Bit-Längen (DB7 bis DB4), wenn DL 0 ist. Wenn 4-Bit-Länge ausgewählt ist, müssen Daten gesendet werden oder
					zweimal erhalten.
				*/
				if (D3_pin == 0 && D2_pin == 0 && D1_pin == 0 && D0_pin == 0) {
					funktionset.DL = 0;
					VAR_FUNKTION_SET_DL(0);
				}
				else {
					funktionset.DL = 1;
					VAR_FUNKTION_SET_DL(1);
				}
			// N
				/*
					Legt die Anzahl der Displayzeilen fest.
				*/
				if (numberoflines == 10) {
					funktionset.N = 1;
					VAR_FUNKTION_SET_N(1);
				}
				else if (numberoflines == 8) {
					funktionset.N = 0;
					VAR_FUNKTION_SET_N(0);
				}
				else
					printf("\n Initialisierungsfehler ...");
			// F
				/*
					Legt die Schriftart fest.
				*/
				funktionset.F;


}

void HD44780_test() {

}

int main(void) {
	HD44780_Initialise(17, 27, 22, 25, 8, 7, 1, 12, 16, 20, 21, 8);
	HD44780_test();
	getchar();
}
