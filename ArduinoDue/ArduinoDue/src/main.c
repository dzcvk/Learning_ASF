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
void WDT_Init(void);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();
	sysclk_init();
	//delay_init(sysclk_get_cpu_hz());
	ioport_init();
	LED_Init();
	WDT_Init();

	/* Insert application code here, after the board has been initialized. */
	while(1)
	{
		ioport_toggle_pin_level(LED);
		delay_ms(1000);
		//while(!(REG_WDT_SR&WDT_SR_WDUNF));
	}
}


void LED_Init(void)
{
	ioport_set_pin_dir(LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED, IOPORT_PIN_LEVEL_HIGH);
}

void WDT_Init(void)
{
	REG_WDT_CR = WDT_CR_KEY(0xa5)|WDT_CR_WDRSTT;
	//REG_WDT_MR = 0b00000010000000000010001000000000;
	REG_WDT_MR = WDT_MR_WDD(500)|WDT_MR_WDRSTEN|WDT_MR_WDV(500);
}