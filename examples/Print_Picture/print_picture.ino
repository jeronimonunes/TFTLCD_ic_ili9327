#include "lcd.h"

LcdClass Lcd;
void setup()
{
	Serial.begin(9600);
	// Serial.println(millis());
	Lcd.begin();
	int color = 0;
	// Lcd.color((unsigned char*)&color);
	// color = 0;
	// Lcd.line((unsigned int)10,(unsigned int)0,(unsigned int)400,(unsigned char*)&color);
	//  for(unsigned int x=0;x<400;x++){
	//  	color=1<<((unsigned int)((unsigned int)x/(unsigned int)25));
	//  	// color = x<25?0:32;
	//  	for(unsigned int y=0;y<240;y++){
	//  		Lcd.pixel(y,x,(unsigned char*)&color);
	//  	}
	//  }
}

void loop()
{
	if(Serial.available()){
		Lcd<<Serial.read();
	}
}
