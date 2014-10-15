#include "lcd.h"

LcdClass::LcdClass(){
	bitmap = false;
	pixel = 0;
}

void LcdClass::operator<<(unsigned char data){
	if(!this->bitmap){
	//	int color = 0;
	//	this->color((unsigned char*)&color);
		digitalWrite(LCD_RS,LOW);
		this->writeData(0x02c); //write_memory_start
		digitalWrite(LCD_RS,HIGH);
		digitalWrite(LCD_CS,LOW);
		this->setAddress(0,0,239,399);
		digitalWrite(LCD_RS,HIGH);
		this->bitmap = true;
	}
	if(pixel < 96000){
		// Serial.println(this->pixel);
		this->pixel++;
		this->writeData(data);
	}
	if(pixel == 96000){
		this->pixel = 0;
		this->bitmap = false;
		digitalWrite(LCD_CS,HIGH);
		// Serial.println("It's done!");
	}
}

void LcdClass::begin(){
	for(int p=2;p<10;p++) pinMode(p,OUTPUT);
	pinMode(A0,OUTPUT);
	pinMode(A1,OUTPUT);
	pinMode(A2,OUTPUT);
	pinMode(A3,OUTPUT);
	pinMode(A4,OUTPUT);
	digitalWrite(A0, HIGH);
	digitalWrite(A1, HIGH);
	digitalWrite(A2, HIGH);
	digitalWrite(A3, HIGH);
	digitalWrite(A4, HIGH);

	//Inserting configuration
	digitalWrite(LCD_REST,HIGH);
	delay(5);
	digitalWrite(LCD_REST,LOW);
	delay(15);
	digitalWrite(LCD_REST,HIGH);
	delay(15);

	digitalWrite(LCD_CS,HIGH);
	digitalWrite(LCD_WR,HIGH);
	digitalWrite(LCD_CS,LOW);  //CS

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xE9);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x20);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x11);
	delay(100);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xD1);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x00);
	this->writeData(0x71);
	this->writeData(0x19);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xD0);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x07);
	this->writeData(0x01);
	this->writeData(0x08);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x36);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x48);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x3A);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x05);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xC1);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x10);
	this->writeData(0x10);
	this->writeData(0x02);
	this->writeData(0x02);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xC0);
	digitalWrite(LCD_RS,HIGH); //Set Default Gamma
	this->writeData(0x00);
	this->writeData(0x35);
	this->writeData(0x00);
	this->writeData(0x00);
	this->writeData(0x01);
	this->writeData(0x02);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xC5);
	digitalWrite(LCD_RS,HIGH); //Set frame rate
	this->writeData(0x04);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xD2);
	digitalWrite(LCD_RS,HIGH); //power setting
	this->writeData(0x01);
	this->writeData(0x44);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0xC8);
	digitalWrite(LCD_RS,HIGH); //Set Gamma
	this->writeData(0x04);
	this->writeData(0x67);
	this->writeData(0x35);
	this->writeData(0x04);
	this->writeData(0x08);
	this->writeData(0x06);
	this->writeData(0x24);
	this->writeData(0x01);
	this->writeData(0x37);
	this->writeData(0x40);
	this->writeData(0x03);
	this->writeData(0x10);
	this->writeData(0x08);
	this->writeData(0x80);
	this->writeData(0x00);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x2A);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x00);
	this->writeData(0x00);
	this->writeData(0x00);
	this->writeData(0xeF);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x2B);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(0x00);
	this->writeData(0x00);
	this->writeData(0x01);
	this->writeData(0x3F);
	this->writeData(0x8F); // on internet

	/* Display On */
	digitalWrite(LCD_RS,LOW);
	this->writeData(0x29);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x2C);

	digitalWrite(LCD_CS,HIGH);
}

void LcdClass::writeData(unsigned char data){
	this->writeData(data,true);
}

void LcdClass::writeData(unsigned char data,bool tosend){
	digitalWrite(8,data&0x01);
	digitalWrite(9,data&0x02);
	digitalWrite(2,data&0x04);
	digitalWrite(3,data&0x08);
	digitalWrite(4,data&0x10);
	digitalWrite(5,data&0x20);
	digitalWrite(6,data&0x40);
	digitalWrite(7,data&0x80);
	if(tosend) send();
}

void LcdClass::send(){
	digitalWrite(LCD_WR,LOW);
	digitalWrite(LCD_WR,HIGH);
}

void LcdClass::color(unsigned char* color){
	unsigned int i,m;
	digitalWrite(LCD_RS,LOW);
	this->writeData(0x02c); //write_memory_start
	digitalWrite(LCD_RS,HIGH);
	digitalWrite(LCD_CS,LOW);
	this->setAddress(0,0,239,399);
	digitalWrite(LCD_RS,HIGH);

	for(i=0;i<400;i++) for(m=0;m<240;m++){
		this->writeData(color[1]);
		this->writeData(color[0]);
	}
	digitalWrite(LCD_CS,HIGH);
}

void LcdClass::writePixel(unsigned int x, unsigned int y,unsigned char* color){
	digitalWrite(LCD_RS,LOW);
	this->writeData(0x02c); //write_memory_start
	digitalWrite(LCD_RS,HIGH);
	digitalWrite(LCD_CS,LOW);
	setAddress(x,y,x,y);
	digitalWrite(LCD_RS,HIGH);
	this->writeData(color[1]);
	this->writeData(color[0]);
	digitalWrite(LCD_CS,HIGH);  
}

void LcdClass::setAddress(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2){
	digitalWrite(LCD_RS,LOW);
	this->writeData(0x2a); // Set_column_address 4 parameters
	digitalWrite(LCD_RS,HIGH);
	this->writeData(x1>>8);
	this->writeData(x1);
	this->writeData(x2>>8);
	this->writeData(x2);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x2b); // Set_page_address 4 parameters
	digitalWrite(LCD_RS,HIGH);
	this->writeData(y1>>8);
	this->writeData(y1);
	this->writeData(y2>>8);
	this->writeData(y2);

	digitalWrite(LCD_RS,LOW);
	this->writeData(0x2c); // Write_memory_start	
}

void LcdClass::line(unsigned int x,unsigned int y,unsigned int l,unsigned char* color){
	unsigned int i,j;
	digitalWrite(LCD_RS,LOW);
	this->writeData(0x02c); //write_memory_start
	digitalWrite(LCD_RS,HIGH);
	digitalWrite(LCD_CS,LOW);
	l=l+x;
	this->setAddress(x,y,x,l);
	j=l*2;
	digitalWrite(LCD_RS,HIGH);
	for(i=0;i<j;i++){
		this->writeData(color[1]);
		this->writeData(color[0]);
	}
	digitalWrite(LCD_CS,HIGH);  
}