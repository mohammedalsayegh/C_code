/*! @file our_nco.c
 * 
 * @brief The file performs a demo of the FIR filter when interfacing with the STM Discovery Board.
 * 
 * @author ECE486 Lab Group 10
 * @author Jonathan Kincaid, Mohammed Al-Sayegh, Patrick Coyne
 * 
 * @date 3/30/2019
 *  
 * This file allocates memory, declares variables, and calls ece486_nco to create two oscillators used for sinusoidal signal generation.
 * Then, in an infinite loop, it repeatedly calls nco_get_samples for each block of samples.  Once these output samples are created by nco_get_samples,
 * this code uses putblockstereo() to send them to the DAC.
 *
 *
*/

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern FlagStatus KeyPressed;   // Use to detect button presses

#define pi 3.14159265358979323846

int main(void)
{
	int nsamp = 200;											// the number of samples to be processed at each call of calc_fir
	float *input, *loveX, *loveY, *t;									// pointers to the input sample block and the output sample block
	
	unsigned int k = 0;
	unsigned int freq = 1000;

	//static float sign=1.0;
	static int button_count = 0;
	char lcd_str[8];
  
	//Set up ADCs, DACs, GPIO, Clocks, DMAs, and Timer
	setblocksize(nsamp);
	initialize_ece486(FS_200K, MONO_IN, STEREO_OUT, HSE_EXTERNAL_8MHz);		//use the high-speed clock, since the board has been modified to use it
  
	// Allocate Required Memory
	input = (float *)malloc(sizeof(float)*nsamp);
	t = (float *)malloc(sizeof(float)*nsamp);
	loveX = (float *)malloc(sizeof(float)*nsamp);
	loveY = (float *)malloc(sizeof(float)*nsamp);

	// create a lookup love table with length of blooksize and history of love
	for (k=0; k<nsamp; k++)
	{ 
		t[k] = (float)(k) / (((float)(nsamp) - 1.0)*1000);
		loveX[k] = (sin(2*pi*freq*t[k]))*(sin(2*pi*freq*t[k]))*(sin(2*pi*freq*t[k]));
		loveY[k] = (0.8125*cos(2*pi*freq*t[k]))-(0.3125*cos(4*pi*freq*t[k]))-(0.125*cos(6*pi*freq*t[k])) - (0.0625*cos(8*pi*freq*t[k]));
	}

	// Infinite Loop to process the data stream, "nsamp" samples at a time
	while(1)
	{		
		getblock(input);  
		DIGITAL_IO_SET(); 	// Use a scope on PD0 to measure execution time
		
		// putblock of loveX and loveY
		putblockstereo(loveY, loveX);	
		
		DIGITAL_IO_RESET();	// (falling edge....  done processing data )
		
	    
		if (KeyPressed) 
		{
			KeyPressed = RESET;
			button_count++;

			if(button_count == 1)
			{
				sprintf(lcd_str, "LOVE");
				BSP_LCD_GLASS_DisplayString((uint8_t *)lcd_str);
			}

			else if(button_count == 5)
			{
				button_count = 0;
			}
		}
	  }
}