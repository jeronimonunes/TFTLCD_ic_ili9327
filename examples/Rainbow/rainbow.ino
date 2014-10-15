#include "lcd.h"

LcdClass Lcd;
void setup()
{
	Lcd.begin();
	int color;
	 for(unsigned int x=0;x<400;x++){
	 	color=1<<((unsigned int)((unsigned int)x/(unsigned int)25));
	 	for(unsigned int y=0;y<240;y++){
	 		Lcd.writePixel(y,x,(unsigned char*)&color);
	 	}
	 }
}

void loop()
{
}
