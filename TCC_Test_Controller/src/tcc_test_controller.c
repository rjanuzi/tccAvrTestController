#include <asf.h>
#include <itasat_pins_functions_stk600.h>
#include <tcc_test_controller.h>

int main (void)
{	
	general_initialize();
	
	print_dbg("\n==============================\nTCC Test Controller\n==============================\n");
	
	while(true)
		start_terminal();
}

void general_initialize()
{
	sysclk_init();
	delay_init(CPU_HZ);
	
	gpio_configure_pin( ITASAT_LED0, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED1, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED2, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED3, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED4, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED5, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED6, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED7, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	
	initTerminalInterface();
	initTestsExecContrInterface();
	
	/* 
	 * Importante: Caso o sistema esteja travando, verificar se 
	 * nao estah ocorrendo nenhum erro na inicializacao do I2C, pois 
	 * isso pode travar. 
	 */
	initI2CTestsInterface();
}
