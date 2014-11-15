/*
 * terminal_controller.c
 *
 * Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 */

#include <terminal_controller.h>

const usart_options_t TERMINAL_UART_OPTIONS =
{
	.baudrate = TERMINAL_UART_BAUD,
	.channelmode = USART_NORMAL_CHMODE,
	.charlength = 8,
	.paritytype = USART_NO_PARITY,
	.stopbits = USART_1_STOPBIT
};

void initTerminalInterface()
{
	gpio_enable_module_pin( USART1_1_TX_PIN, USART1_1_TX_FUNCTION );
	gpio_enable_module_pin( USART1_1_RX_PIN, USART1_1_RX_FUNCTION );
	
	if( usart_init_rs232( TERMINAL_UART, &TERMINAL_UART_OPTIONS, CPU_HZ ) == USART_SUCCESS )
		gpio_set_pin_low( ITASAT_LED0 );
}

void manage_command()
{
	char* string_aux;
	bool cmd_recognized = false;
	command_buffer[free_index] = '\0';
	
	if( strcmp( command_buffer, "i2c test all" ) == 0 )
	{
		i2c_test_all();
		cmd_recognized = true;
	}
	
	if( strcmp( command_buffer, "i2c test 1" ) == 0 )
	{
		i2c_test_01();
		cmd_recognized = true;
	}
	
	if( strcmp( command_buffer, "i2c test 2" ) == 0 )
	{
		i2c_test_02();
		cmd_recognized = true;
	}
	
	if(!cmd_recognized)
		print_dbg("\n\nComando nao reconhecido!");
	
	free_index = 0; //Simulate the reset of command_buffer
}

void start_terminal()
{
	int received_char;
	
	while(true)
	{
		if(free_index == 0)
			print_dbg("\n\n--> ");
		
		received_char = usart_getchar( TERMINAL_UART );
	
		switch(received_char)
		{
			case USART_FAILURE:
				//Tratar o ERRO
				break;
			case ENTER_CHAR:
				manage_command();
				break;
			default:
				command_buffer[free_index] = (char) received_char;
				free_index++;
				usart_putchar( TERMINAL_UART, received_char ); //Echo in PC terminal.
			break;
		}
	}
	
	print_dbg( "\n\nTerminal stops!\n\n" );
}