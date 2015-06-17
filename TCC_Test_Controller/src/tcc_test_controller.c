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
	/* Inicializa o sistema de clocks do processador. */
	sysclk_init();
	
	/* Inicializa o sistema de delays. */
	delay_init(CPU_HZ);
	
	/* Configuracao dos GPIOs conectados aos LEDs da placa STK600 */
	gpio_configure_pin( ITASAT_LED0, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED1, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED2, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED3, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED4, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED5, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED6, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	gpio_configure_pin( ITASAT_LED7, GPIO_INIT_HIGH | GPIO_DIR_OUTPUT );
	
	/* Inicializa a interface USART conectada ao terminal */
	initTerminalInterface();
	
	/* Incializa a interface USART utilizada no controle dos testes. */
	initTestsExecContrInterface();
	
	/* 
	 * Inicializa a interface I2C conectada a interface sob testes.
	 *
	 * Importante: Caso o sistema esteja travando, verificar se 
	 * nao estah ocorrendo nenhum erro na inicializacao do I2C.
	 */
	initI2CTestsInterface();
}
