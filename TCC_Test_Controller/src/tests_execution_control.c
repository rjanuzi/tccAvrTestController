/*
 * test_execution_control.c
 *
 * Created: 10/11/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 */

#include <tests_execution_control.h>

const usart_options_t TESTS_EXECUTION_CONTROL =
{
	.baudrate = TESTS_EXEC_CTRL_UART_BAUD,
	.channelmode = USART_NORMAL_CHMODE,
	.charlength = 8,
	.paritytype = USART_NO_PARITY,
	.stopbits = USART_1_STOPBIT
};

void printfCmd(cmd_frame_t frame)
{
	int i;
	char* textAux;

	sprintf(textAux, "\nCmd code: 0x%x\nParam Size: %d\nTest Number: %d\nParams:", frame.cmdCode, frame.paramSize, frame.testNumber);
	print_dbg(textAux);

	for( i = 0; i < frame.paramSize; i++)
	{
		sprintf(textAux, " 0x%x ", frame.params[i]);
		print_dbg(textAux);
	}
}

void initTestsExecContrInterface()
{
	gpio_enable_module_pin( USART0_1_TX_PIN, USART0_1_TX_FUNCTION );
	gpio_enable_module_pin( USART0_1_RX_PIN, USART0_1_RX_FUNCTION );
	
	if( usart_init_rs232( TESTS_EXEC_CTRL_UART, &TESTS_EXECUTION_CONTROL, CPU_HZ ) == USART_SUCCESS )
		gpio_set_pin_low( ITASAT_LED1 );
}

cmd_frame_t newEmptyTestCmdFrame(uint16_t testNumber, uint16_t paramSize)
{
	cmd_frame_t newFrame;
	
	newFrame.cmdCode = 0x3C7E;
	newFrame.testNumber = testNumber;
	newFrame.paramSize = paramSize;
	
	if( paramSize != 0 )
		newFrame.params = dlmalloc(paramSize);
	
	return newFrame;
}

void freeCmdFrame(cmd_frame_t frame)
{
	if( frame.paramSize != 0 )
		dlfree(frame.params);
	frame.cmdCode = 0;
	frame.paramSize = 0;
	frame.testNumber = 0;
}

void sendTestCmdFrame(cmd_frame_t frame)
{
	int aux, i;
	cmd_frame_t anwser;
	
	/* Send cmdCode */
	aux = (frame.cmdCode>>8);
	usart_putchar( TESTS_EXEC_CTRL_UART, aux);
	aux = (frame.cmdCode&0x000000FF);
	usart_putchar( TESTS_EXEC_CTRL_UART, aux);
	
	/* Send testNumber */
	aux = (frame.testNumber>>8);
	usart_putchar( TESTS_EXEC_CTRL_UART, aux);
	aux = (frame.testNumber&0x000000FF);
	usart_putchar( TESTS_EXEC_CTRL_UART, aux);
	
	/* Send paramSize */
	aux = (frame.paramSize>>8);
	usart_putchar( TESTS_EXEC_CTRL_UART, aux);
	aux = (frame.paramSize&0x000000FF);
	usart_putchar( TESTS_EXEC_CTRL_UART, aux);
	
	/* Send params */ 
	for( i = 0; i < frame.paramSize; i++)
	{
		aux = frame.params[i];		
		usart_putchar( TESTS_EXEC_CTRL_UART, aux);
	}
}

cmd_frame_t rcvTestCmdAnswer()
{
	//Frame 0xE7C3 + 2_Bytes_Test_Number + 2_Bytes_N_Data + N_Data_N_Bytes
	int rcvByte = 0;
	char* textAux;
	uint8_t rcvAnswerFlag = 0, automataState = 1;
	uint16_t c = 0, N = 0, testCaseNumber = 0;
	cmd_frame_t cmdAwsFrameRcv;
	
	while(rcvAnswerFlag == 0)
	{		
		rcvByte = usart_getchar_timeout( TESTS_EXEC_CTRL_UART );
		
		if(rcvByte == USART_TIMEOUT || rcvByte == USART_FAILURE)
		{
			initTestsExecContrInterface(); /* Reinicia a interface */
			cmdAwsFrameRcv.cmdCode = 0;
			cmdAwsFrameRcv.paramSize = 0;
			cmdAwsFrameRcv.testNumber = 0;
			return cmdAwsFrameRcv;
		}

		switch( automataState )
		{
		case 1:
			if( rcvByte == 0xE7 )
				automataState = 2;
			break;

		case 2:
			if( rcvByte == 0xC3 )
				automataState = 3;

			else
				automataState = 1;
			break;

		case 3:
			switch( c )
			{
			case 0:
				/* Recebendo o MSByte do testCaseNumber */
				testCaseNumber = (rcvByte<<8);
				c++;
				break;

			case 1:
				/* Recebendo o LSByte do testCaseNumber */
				testCaseNumber |= rcvByte;
				c++;
				break;

			case 2:
				/* Recebendo o MSByte do N */
				N = (rcvByte<<8);
				c++;
				break;

			case 3:
				/* Recebendo o LSByte do N e trocando de estado */
				N |= rcvByte;
				automataState = 4;
				c = 0;
				
				/* Comando identificado, agora basta receber os parametros */
				cmdAwsFrameRcv = newEmptyTestCmdFrame( testCaseNumber, N );
				
				/* Apenas deixando o pacote de resposta no padrao, pois a 
				 * funcao newEmptyTestCmdFrame foi reaproveitada. Nao causa 
				 * problemas, pois o automato identifica apenas frames com o parametro 0xE7C3.
				 */
				cmdAwsFrameRcv.cmdCode = 0xE7C3;
				
				/* Caso nao irah ser recebido nenhum parametro o programa nao pode continuar aguardando*/
				if( N == 0)
				{
					automataState = 1;
					rcvByte = 0;
					c = 0;
					N = 0;
					rcvAnswerFlag = 1;
				}
			
				break;
			}
			break;

			case 4:
				if( c < N )
				{
					cmdAwsFrameRcv.params[c] = rcvByte;
					c++;
				}
				
				/* O estado 5 possui uma e-transicao, entao nao deve-se
				 * aguardar o recebimento de mais um byte para a mudanca de estado */
				if( c == N )
				{
					automataState = 1;
					rcvByte = 0;
					c = 0;
					N = 0;
					
					rcvAnswerFlag = 1;
				}
				break;

			default:
				automataState = 1;
				rcvByte = 0;
				c = 0;
				N = 0;
				break;
		}
	}
	
	return cmdAwsFrameRcv;
}