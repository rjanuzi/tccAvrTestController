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

	sprintf(textAux, "\nCmd code: 0x%x\nTest Type: %d\nData Size: %d\nData:", frame.magicCode, frame.testType, frame.dataSize);
	print_dbg(textAux);

	for( i = 0; i < frame.dataSize; i++)
	{
		sprintf(textAux, " 0x%x ", frame.data[i]);
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

cmd_frame_t newEmptyTestCmdFrame(uint8_t testType, uint8_t dataSize)
{
	cmd_frame_t newFrame;
	int i = 0;
	
	newFrame.magicCode = 0x3C7E;
	newFrame.testType = testType;
	newFrame.dataSize = dataSize;
	
	for(i = 0; i < dataSize; i++)
		newFrame.data[i] = 0;
	
	return newFrame;
}

void freeCmdFrame(cmd_frame_t frame)
{
	int i;
	
	frame.magicCode = 0;
	frame.dataSize = 0;
	frame.testType = 0;
	
	for(i = 0; i < frame.dataSize; i++)
		frame.data[i] = 0;
}

void sendTestCmdFrame(cmd_frame_t frame)
{
	int aux, i;
	cmd_frame_t anwser;
	
	/* Send cmdCode */
	aux = (frame.magicCode>>8);	
	if( USART_FAILURE == usart_putchar( TESTS_EXEC_CTRL_UART, aux))
	{
		print_dbg("\ntests_execution_control - sendTestCmdFrame - USART_FAILURE");
	}
	aux = (frame.magicCode&0x00FF);
	if(USART_FAILURE == usart_putchar( TESTS_EXEC_CTRL_UART, aux))
	{
		print_dbg("\ntests_execution_control - sendTestCmdFrame - USART_FAILURE");
	}
	
	/* Send testType */
	aux = frame.testType;
	if(USART_FAILURE == usart_putchar( TESTS_EXEC_CTRL_UART, aux))
	{
		print_dbg("\ntests_execution_control - sendTestCmdFrame - USART_FAILURE");
	}
	
	/* Send dataSize */
	aux = frame.dataSize;
	if(USART_FAILURE == usart_putchar( TESTS_EXEC_CTRL_UART, aux))
	{
		print_dbg("\ntests_execution_control - sendTestCmdFrame - USART_FAILURE");
	}
	
	/* Send data */ 
	for( i = 0; i < frame.dataSize; i++)
	{
		aux = frame.data[i];		
		if(USART_FAILURE == usart_putchar( TESTS_EXEC_CTRL_UART, aux))
		{
			print_dbg("\ntests_execution_control - sendTestCmdFrame - USART_FAILURE");
		}
	}
}

cmd_frame_t rcvTestCmdAnswer()
{
	//Frame 0xE7C3 + 2_Bytes_Test_Number + 2_Bytes_N_Data + N_Data_N_Bytes
	int rcvByte = 0;
	char* textAux;
	uint8_t rcvAnswerFlag = 0, automataState = 1, testType;
	uint16_t c = 0, dataSize = 0;
	cmd_frame_t cmdAwsFrameRcv;
	
	while(rcvAnswerFlag == 0)
	{		
		//rcvByte = usart_getchar_timeout( TESTS_EXEC_CTRL_UART );
		rcvByte = usart_getchar( TESTS_EXEC_CTRL_UART );
		
		if(rcvByte == USART_TIMEOUT || rcvByte == USART_FAILURE)
		{
			print_dbg("\n\ntests_execution_control - rcvTestCmdAnswer - USART_TIMEOUT OR USART_FAILURE");
			initTestsExecContrInterface(); /* Reinicia a interface */
			cmdAwsFrameRcv.magicCode = 0;
			cmdAwsFrameRcv.dataSize = 0;
			cmdAwsFrameRcv.testType = 0;
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
				testType = rcvByte;
				c++;
				break;

			case 1:
				/* Recebendo o MSByte do N */
				dataSize = rcvByte;
				automataState = 4;
				c = 0;
				
				/* Comando identificado, agora basta receber os parametros */
				cmdAwsFrameRcv = newEmptyTestCmdFrame( testType, dataSize );
				
				/* Apenas deixando o pacote de resposta no padrao, pois a 
				 * funcao newEmptyTestCmdFrame foi reaproveitada. Nao causa 
				 * problemas, pois o automato identifica apenas frames com o parametro 0xE7C3.
				 */
				cmdAwsFrameRcv.magicCode = 0xE7C3;
				
				/* Caso nao irah ser recebido nenhum dado extra, o programa nao pode continuar aguardando*/
				if( dataSize == 0)
				{
					automataState = 1;
					rcvByte = 0;
					c = 0;
					dataSize = 0;
					rcvAnswerFlag = 1;
				}
				
				break;
			}
			break;

			case 4:
				if( c < dataSize )
				{
					cmdAwsFrameRcv.data[c] = rcvByte;
					c++;
				}
				
				/* O estado 5 possui uma e-transicao, entao nao deve-se
				 * aguardar o recebimento de mais um byte para a mudanca de estado */
				if( c == dataSize )
				{
					automataState = 1;
					rcvByte = 0;
					c = 0;
					dataSize = 0;
					
					rcvAnswerFlag = 1;
				}
				break;

			default:
				automataState = 1;
				rcvByte = 0;
				c = 0;
				dataSize = 0;
				break;
		}
	}
	
	return cmdAwsFrameRcv;
}