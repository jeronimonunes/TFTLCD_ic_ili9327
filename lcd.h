#ifndef __LCD_INCLUDE_H____
#define __LCD_INCLUDE_H____

#include <Arduino.h>

//   ic:ili9327  
#define LCD_RD   A0
#define LCD_WR   A1    //clock
#define LCD_RS   A2    //endereço ou dados (cor)
#define LCD_CS   A3      
#define LCD_REST A4


class LcdClass {
	private:
		bool bitmap;
		int pixel;
	public:
		/**
		* Constructs and initialize the LCD
		*/
		LcdClass();

		void operator<<(unsigned char);

		/**
		* Initialize the LCD
		*/
		void begin();

		/**
		* Function that write some data on data pins
		* @param data The data to write on pins
		*/
		void writeData(unsigned char data);

		/**
		* Function that write some data on data pins
		* @param data The data to write on pins
		* @param tosend If the clock should cicle to LCD to read the data
		*/
		void writeData(unsigned char data,bool tosend);
		/**
		* Cicles the clock to write data on LCD internal memory
		*/
		void send();

		/**
		* Colorate the LCD with one given color
		*/
		void color(unsigned char* color);

		/**
		* Defines wich address will receive data
		*/
		void setAddress(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);

		void writePixel(unsigned int x, unsigned int y,unsigned char* color);

		void line(unsigned int x,unsigned int y,unsigned int l ,unsigned char* color);
		
};

#endif //LCD_INCLUDE_H