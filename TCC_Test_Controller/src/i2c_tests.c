/*
 * i2c_tests.c
 *
 * Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 */ 

#include <i2c_tests.h>
#include <tests_execution_control.h>

const twis_options_t TWIS_OPTIONS = {
	.pba_hz = 16000000, /* 16 MHz */
	.speed = 400000, /* 400 KHz */
	.chip = AVR_ADDRESS, /* Endereco desse Slave */
	.smbus = false, /* Modo SMBUS serah utilizado */
	.tenbit = false /* Serah utilizado endereco de 10 bits */
};

const twim_options_t TWIM_OPTIONS = {
	.chip = 	AVR_ADDRESS ,	/* Endereco desse Master, utilizado apenas em um simples teste na inicializacao do controlador TWIM */
	.pba_hz = 	16000000, 		/* PBA Div = 1 no arquivo de configuracao do clock */
	.smbus = 	false, 			/* Nao iremos utilizar o modo SMBUS */
	.speed = 	400000 			/* Velocidade da transmissao */
};

/* Funcoes para controle das transmissoes */
const twis_slave_fct_t TWIS_FUNCTIONS = {
	.rx = &RxFunction,
	.tx = &TxFunction,
	.stop = &StopFunction
};

void initI2CTestsInterface()
{
	gpio_enable_module_pin( TWIS0_1_TWD_PIN, TWIS0_1_TWD_FUNCTION );
	gpio_enable_module_pin( TWIS0_1_TWCK_PIN, TWIS0_1_TWCK_FUNCTION );
	
	if( STATUS_OK == twis_slave_init( TWI_SLAVE, &TWIS_OPTIONS, &TWIS_FUNCTIONS ))
		gpio_set_pin_low( ITASAT_LED2 );

	if( STATUS_OK == twim_master_init( TWI_MASTER, &TWIM_OPTIONS ))
		gpio_set_pin_low( ITASAT_LED3 );
}

/*!
 * \brief Funcao a ser executada quando um byte eh recebido do Master.
 *
 * Essa funcao eh executada quando uma interrupcao, que sinaliza a recepcao de um byte do Master, ocorre. O controlador TWIS automaticamente executa essa funcao
 * passando por parametro o byte recebido. Entao a funcao utiliza a flag \ref ReceivedBytesCount para realizar a correta verificacao com um determinado byte esperado,
 * caso a verificacao falhe a flag \ref ReceivedBytesOK recebe o valor \ref false.
 *
 * \param ReceivedData Byte recebido na comunicacao
 *
 * \return \ref void.
 */
void RxFunction( uint8_t ReceivedData )
{
	char* texto;
	gpio_tgl_gpio_pin(ITASAT_LED7);
	
// 	sprintf( texto, "\nByte %d recebido: 0x%x", bytes_count, ReceivedData);
// 	usart_write_line(DBG_UART, texto);
}

/*!
 * \brief Funcao a ser executada quando um byte tiver que ser enviado ao Master.
 *
 * Essa funcao eh executada quando uma interrupcao, que sinaliza que um byte deve ser enviado ao Master, ocorre. O controlador TWIS automaticamente executa essa funcao
 * e envia o byte que ela retorna para ao Master. A funcao utiliza a flag \ref SentBytesCount para enviar o byte correto.
 *
 * \return Byte a ser enviado ao Master.
 */
uint8_t TxFunction()
{
	const char* texto;
	
	gpio_tgl_gpio_pin(ITASAT_LED6);
	
	return 0xaa;
}

/*!
 * \brief Funcao a ser executada quando uma transmissao (envio ou recepcao) termina.
 *
 * Essa funcao eh executada quando uma interrupcao, que sinaliza que uma transmissao terminou, ocorre. O controlador TWIS automaticamente executa essa funcao
 * que basicamente realiza uma verificacao das flags \ref ReceivedBytesCount, \ref ReceivedBytesOK e \ref SentBytesCount, de acordo com o resultado de cada 
 * verificacao executa um comando toggle em um determino LED. Apos as verificacoes das flags, o programa "reseta" as mesmas para que sejam usadas na proxima transmissao.
 *
 * \return \ref void.
 */
void StopFunction()
{
	const char* texto;
	
	gpio_tgl_gpio_pin(ITASAT_LED5);
}

void i2c_test_all()
{
	i2c_test_01();
	i2c_test_02();
}

/*
 * Simples teste de envio (AVR -> CC) para verificacao do sistema de testes. (Result Pass)
 */
bool i2c_test_01()
{
	print_dbg("\n\n==============================\nExecutando i2c teste 01...\n==============================\n");
	
	uint8_t sendBuffer[5] = {0x03, 0xFF, 0xEF, 0x3F, 0x23};
	int i, aux, testNumber = 1, paramsSize = 5;
	cmd_frame_t cmdFrame, ansFrame;
	bool result;
	
	cmdFrame = newEmptyTestCmdFrame(testNumber, paramsSize);
	cmdFrame.params[0] = 0x03;
	cmdFrame.params[1] = 0xFF;
	cmdFrame.params[2] = 0xEF;
	cmdFrame.params[3] = 0x3F;
	cmdFrame.params[4] = 0x23;
		
	//Notifica o CC sobre a execucao do teste 01 e envia os dados auxiliares.
	sendTestCmdFrame(cmdFrame);
	
	print_dbg("\n\nTest command sent: ");
	printfCmd(cmdFrame);

	//Espera o CC se preparar para o teste.
	delay_ms(CC_PREPARE_TO_TEST_DELAY);
	twim_write( TWI_MASTER, sendBuffer, paramsSize, CUBE_COMPUTER_ADDRESS, false );
	
	ansFrame = rcvTestCmdAnswer();
	if(ansFrame.cmdCode != 0)
	{
		if( ansFrame.params[0] == PARAM_TEST_FAIL )
		{
			result = false;
			print_dbg( "\n\nFAIL" );
		}
		else
		{
			result = true;
			print_dbg( "\n\nPASS" );
		}
		
		print_dbg("\n\nTest answer received: ");
		printfCmd(ansFrame);
		freeCmdFrame(ansFrame);
	}
	else
	{
		print_dbg( "\n\nFAIL" );
		result = false;
	}
	
	return result;
}

/*
 * Simples teste de envio (AVR -> CC) para verificacao do sistema de testes. (Result Fail)
 */
bool i2c_test_02()
{
	print_dbg("\n\n==============================\nExecutando i2c teste 02...\n==============================\n");
	
	uint8_t sendBuffer[5] = {0x03, 0xFF, 0xEF, 0x3F, 0x23};
	int i, aux, testNumber = 2, paramsSize = 5;
	cmd_frame_t cmdFrame, ansFrame;
	bool result;
	
	cmdFrame = newEmptyTestCmdFrame(testNumber, paramsSize);
	cmdFrame.params[0] = 0x03;
	cmdFrame.params[1] = 0xFF;
	cmdFrame.params[2] = 0xEF;
	cmdFrame.params[3] = 0x3E; //Causara o Erro
	cmdFrame.params[4] = 0x23;
	
	//Notifica o CC sobre a execucao do teste 01 e envia os dados auxiliares.
	sendTestCmdFrame(cmdFrame);
	
	print_dbg("\n\nTest command sent: ");
	printfCmd(cmdFrame);

	//Espera o CC se preparar para o teste.
	delay_ms(CC_PREPARE_TO_TEST_DELAY);
	twim_write( TWI_MASTER, sendBuffer, paramsSize, CUBE_COMPUTER_ADDRESS, false );
	
	ansFrame = rcvTestCmdAnswer();
	if(ansFrame.cmdCode != 0)
	{
		if( ansFrame.params[0] == PARAM_TEST_FAIL )
		{
			result = false;
			print_dbg( "\n\nFAIL" );
		}
		else
		{
			result = true;
			print_dbg( "\n\nPASS" );
		}
		
		print_dbg("\n\nTest answer received: ");
		printfCmd(ansFrame);
		freeCmdFrame(ansFrame);
	}
	else
	{
		print_dbg( "\n\nFAIL" );
		result = false;
	}
	
	return result;
}
