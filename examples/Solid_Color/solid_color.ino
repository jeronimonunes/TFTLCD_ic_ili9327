#include "lcd.h"

LcdClass Lcd;
void setup()
{
	Lcd.begin();
	int color = 0;
	Lcd.color((unsigned char*)&color);
}

void loop()
{
}
