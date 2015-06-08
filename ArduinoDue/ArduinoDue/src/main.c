/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

#define LED IOPORT_CREATE_PIN(PIOB,27)

void LED_Init(void);
void reloadwdt(void);
void initwdt(double secs);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	initwdt(1);
	ioport_init();
	LED_Init();
	/* Insert application code here, after the board has been initialized. */
	while(1);
}


void LED_Init(void)
{
	ioport_set_pin_dir(LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED, IOPORT_PIN_LEVEL_HIGH);
}


void reloadwdt(void)
{
	REG_WDT_CR = WDT_CR_KEY(0xa5)|WDT_CR_WDRSTT;	//setting key and restart watchdog
}

void initwdt(double secs)
{
	uint value;
	value = (int)(secs*(32768/128));
	NVIC_EnableIRQ(WDT_IRQn);		//enable watchdog interrupt in NVIC
	REG_WDT_MR = WDT_MR_WDD(value)|WDT_MR_WDV(value)|WDT_MR_WDFIEN;	//setting feeding underflow period and enable sending watchdog interrupt request to NVIC
}

void WDT_Handler()
{
	enum{GREEN, AMBER, RED};
	uint value = REG_WDT_SR;	//without this line, interrupt will not be cleared
	static uint state  = GREEN;
	static uint counter = 0;

	switch(state)
	{
		case GREEN:
		{
			counter++;
			if(counter == 5)
			{
				state = AMBER;
				//AMBER light
				ioport_set_pin_level(LED,LOW);
				counter = 0;
			}
			break;
		}
		case AMBER:
		{
			counter++;
			if(counter == 1)
			{
				state = RED;
				//RED light
				ioport_set_pin_level(LED,HIGH);
				counter = 0;
			}
			break;
		}
		case RED:
		{
			counter++;
			if(counter == 3)
			{
				state = GREEN;
				//GREEN light
				ioport_set_pin_level(LED,HIGH);
				counter = 0;
			}
			break;
		}
	}
	//ioport_toggle_pin_level(LED);
}
