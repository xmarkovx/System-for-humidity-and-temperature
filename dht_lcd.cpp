#include "dht.h"
#include <LiquidCrystal.h>

//GPIO definition
#define		LED_1 PI_0
#define		LED_2 PI_6
#define		DHT_INPUT_PIN P2_0

DhtBuffered	mydht(DHT_INPUT_PIN, true);
LiquidCrystal lcd(P2_1, P1_1, P1_4, P1_5, P2_5, P1_7);

float temp_TH = 32.0;	//ThreshHold for temperature
float hm_TH = 60.0;		//ThreshHold for humidity

//function setup is called only once and before loop
void setup() {

	initPin(DHT_INPUT_PIN);	//init DHT
	lcd.begin(16, 2);		//int LCD

	//init LEDs
	pinMode(LED_1, OUTPUT);	
	pinMode(LED_2, OUTPUT);
	digitalWrite(LED_1, LOW);	
	digitalWrite(LED_1, LOW);

/*	ui : data we want to print
*	example: int 302 stands for float value 30.2
*	mark : temeperature or humidity value?
*/

	void printDec(uint32_t ui, char mark) {
		if (!mark) {
			//Print temperature
			lcd.setCursor(0, 0);	//set cursor on LCD
			lcd.print("Temp: ");	
			lcd.print(ui / 10);		//print integer value
			lcd.print(".");
			lcd.print(ui % 10);		//print decimal value
			lcd.print("\337C    ");	//print celsius sign

			if (ui > temp_TH * 10) {	//if value is greater than set ThreshHold
				lcd.print(">");
				digitalWrite(LED_1, HIGH);	//turn on LED alarm
			}

			else{
				lcd.print("<");
				digitalWrite(LED_1, LOW);	//turn off LED alarm
			}
		}

		else {
			//Print humidity
			lcd.setCursor(0, 1);
			lcd.print("Hum: ");
			lcd.print(ui / 10);
			lcd.print(".");
			lcd.print(ui % 10);
		}
			if (ui > hum_TH * 10) {
				lcd.print(" >");
				digitalWrite(LED_2, HIGH);
			}
			else {
				lcd.print(" <");
				digitalWrite(LED_2, LOW);
			}
	}

	void loop() {

		//marks if the reading is real time data or buffer data
		boolean actualReadingMade = false;

		if (mydht.update(&actualReadingMade)) {	//if reading is successfull
			printDec(mydht.temperature(), 0);	//print temperature
			printDec(mydht.humidity(), 1);		//and print humidity

			//no need for high frequency reading + LCD is slow
			delay(500);
		}
	
	}
