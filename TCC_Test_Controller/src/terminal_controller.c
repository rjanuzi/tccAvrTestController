#include <terminal_controller.h>

/* Definicao de estrutura de configuracao da USART do terminal. */
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
	/* Inicializacao dos GPIOs utilizados pela USART do terminal. */
	gpio_enable_module_pin( USART1_1_TX_PIN, USART1_1_TX_FUNCTION );
	gpio_enable_module_pin( USART1_1_RX_PIN, USART1_1_RX_FUNCTION );
	
	/* Inicializacao do controlador USART do terminal. */
	if( usart_init_rs232( TERMINAL_UART, &TERMINAL_UART_OPTIONS, CPU_HZ ) == USART_SUCCESS )
		gpio_set_pin_low( ITASAT_LED0 );
}

void manage_command()
{
	char* string_aux;
	bool cmd_recognized = false;
	command_buffer[free_index] = '\0';
	
	/* Execucao do comando "help", exibe todos os comandos no terminal. */
	if( strcmp( command_buffer, "help" ) == 0 )
	{
		print_dbg("\n\nhelp: Apresenta todos os comandos existentes.");
		print_dbg("\n\ni2c all: Executa todos os testes do I2C.");
		print_dbg("\n\ni2c mtx: Executa o teste da I2C com o CubeComputer como Master Transmitter.");
		print_dbg("\n\ni2c mrx: Executa o teste da I2C com o CubeComputer como Master Receiver.");
		print_dbg("\n\ni2c srx: Executa o teste da I2C com o CubeComputer como Slave Receiver.");
		
		cmd_recognized = true;
	}
	
	/* Execucao do comando "reset", reinicializa todo o sistema. */
	if( strcmp( command_buffer, "reset" ) == 0 )
	{
		general_initialize();
		print_dbg("\n==============================\nTCC Test Controller\n==============================\n");
		cmd_recognized = true;
	}
	
	/* Execucao do comando "i2c all", executa todos os testes I2C programados em i2c_tests.c */
	if( strcmp( command_buffer, "i2c all" ) == 0 )
	{
		i2c_test_all();
		cmd_recognized = true;
	}
	
	/* Execucao do comando "i2c mtx", executa todos os testes I2C do tipo Master Transmitter. */
	if( strcmp( command_buffer, "i2c mtx" ) == 0 )
	{
		masterTransmitterTest();
		cmd_recognized = true;
	}
	
	/* Execucao do comando "i2c mtx", executa todos os testes I2C do tipo Master Receiver. */
	if( strcmp( command_buffer, "i2c mrx" ) == 0 )
	{
		masterReceiverTest();
		cmd_recognized = true;
	}
	
	/* Execucao do comando "i2c mtx", executa todos os testes I2C do tipo Slave Receiver. */
	if( strcmp( command_buffer, "i2c srx" ) == 0 )
	{
		slaveReceiverTest();
		cmd_recognized = true;
	}
	
	/* Quando o comando nao eh reconhecido exibe uma mensagem e volta ao funcionamento normal. */
	if(!cmd_recognized)
	{
		print_dbg("\n\nComando nao reconhecido!");
	}
	
	/* Apos o tratamento do comando no buffer, limpa o mesmo voltado o indice de controle para o inicio. */
	free_index = 0;
}

void start_terminal()
{
	int received_char;
	
	/* Se tudo funcionar normalmente esse loop nunca termina. */
	while(true)
	{
		/* Caso nenhum caracter exista no buffer, exibe um "-->" no terminal  */
		if(free_index == 0)
			print_dbg("\n\n--> ");
		
		/* Aguarda ateh que um character seja digitado no terminal. */
		received_char = usart_getchar( TERMINAL_UART );

		/* Trata o caracter recebido. */
		switch(received_char)
		{
			/* Caso o caracter seja recebido com erro, exibe uma mensagem no terminal e reinicia o sistema. */
			case USART_FAILURE:
				print_dbg("\nterminal_controller.c - start_terminal - USART_FAILURE");
				initTerminalInterface();
				break;
			
			/* Caso o caracter recebido seja um enter, chama a funcao manage_command(). */
			case ENTER_CHAR:
				manage_command();
				break;
			
			/*	Caso o caracter seja recebido corretamente e nao seja um enter adiciona o
			 * mesmo no buffer de comandos, incrementa o indice de controle do buffer e
			 * exibe o caracter recebido no terminal (echo).
			 */
			default:
				command_buffer[free_index] = (char) received_char;
				free_index++;
				usart_putchar( TERMINAL_UART, received_char ); //Echo in PC terminal.
			break;
		}
	}
	
	/* Caso o loop infinito termine exibe uma mensagem de erro antes de terminar a funcao. */
	print_dbg( "\n\nTerminal stops!\n\n" );
}