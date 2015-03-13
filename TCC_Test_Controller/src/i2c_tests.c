/*
 * i2c_tests.c
 *
 * Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 */ 

#include <i2c_tests.h>
#include <tests_execution_control.h>

const cmd_frame_t test_cases[TEST_CASES_COUNT] =
{
	{	
		0x3C7E,			/* magicCode */
		TEST_TYPE_M_TX,	/* testType */
		1,				/* dataSize */
		{0x37}			/* data */
	},
	
	{
		0x3C7E,			/* magicCode */
		TEST_TYPE_M_TX,	/* testType */
		10,				/* dataSize */
		{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10}			/* data */
	},
	
	{
		0x3C7E,			/* magicCode */
		TEST_TYPE_M_TX,	/* testType */
		5,				/* dataSize */
		{0x37, 0x23, 0x45, 0x67, 0x12}			/* data */
	},
	
	{
		0x3C7E,			/* magicCode */
		TEST_TYPE_M_TX,	/* testType */
		3,				/* dataSize */
		{0x49, 0x18, 0x23}			/* data */
	},

	{	0x3C7E,			/* magicCode */
		TEST_TYPE_M_RX,	/* testType */
		1,				/* dataSize */
		{0x37}			/* data */
	},
	
	{
		0x3C7E,			/* magicCode */
		TEST_TYPE_M_RX,	/* testType */
		10,				/* dataSize */
		{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10}			/* data */
	},

	{	0x3C7E,			/* magicCode */
		TEST_TYPE_S_TX,	/* testType */
		1,				/* dataSize */
		{0x37}			/* data */
	},
	
	{
		0x3C7E,			/* magicCode */
		TEST_TYPE_S_TX,	/* testType */
		10,				/* dataSize */
		{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10}			/* data */
	},

	{	0x3C7E,			/* magicCode */
		TEST_TYPE_S_RX,	/* testType */
		1,				/* dataSize */
		{0x37}			/* data */
	},
	
	{
		0x3C7E,			/* magicCode */
		TEST_TYPE_S_RX,	/* testType */
		10,				/* dataSize */
		{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10}			/* data */
	},
};

uint8_t i2cBytesBuffer[DATA_MAX_SIZE];
uint8_t receivedBytesCount = 0, sentBytesCount = 0, runningMrxTest = 0;
bool transmissionEnded = false;

const twis_options_t TWIS_OPTIONS = {
	.pba_hz = 16000000,		/* 16 MHz */
	.speed = 400000,		/* 400 KHz */
	.chip = AVR_ADDRESS,	/* Endereco desse Slave */
	.smbus = false,			/* Modo SMBUS serah utilizado */
	.tenbit = false			/* Serah utilizado endereco de 10 bits */
};

const twim_options_t TWIM_OPTIONS = {
	.chip = 	CUBE_COMPUTER_ADDRESS ,		/* Endereco desse Master, utilizado apenas em um simples teste na inicializacao do controlador TWIM */
	.pba_hz = 	16000000, 					/* PBA Div = 1 no arquivo de configuracao do clock */
	.smbus = 	false, 						/* Nao iremos utilizar o modo SMBUS */
	.speed = 	400000 						/* Velocidade da transmissao */
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


/* TODO - Add Text */
void RxFunction( uint8_t ReceivedData )
{
	i2cBytesBuffer[receivedBytesCount++] = ReceivedData;
	
	gpio_tgl_gpio_pin(ITASAT_LED7);
}

/* TODO - Add Text */
uint8_t TxFunction()
{
	uint8_t byteToSend = test_cases[runningMrxTest].data[sentBytesCount];
	
	sentBytesCount++;
	
	gpio_tgl_gpio_pin(ITASAT_LED6);
	
	return byteToSend; /* Envia o byte de numero sentBytesCount do teste em andamento */
}

/* TODO - Add Text */
void StopFunction()
{
	transmissionEnded = true;	
	gpio_tgl_gpio_pin(ITASAT_LED5);
}

void i2c_test_all()
{
	masterTransmitterTest();
	masterReceiverTest();
	slaveTransmitterTest();
	slaveReceiverTest();
}

void masterTransmitterTest()
{
	print_dbg("\n\n==============================\nExecutando i2c mtx...\n==============================\n");
	
	int i, j, timeout = 10000000, trys, countAux = 1;
	char* text;
	bool testResult = true;
	
	for(i = 0; i < TEST_CASES_COUNT; i++ )
	{
		if(test_cases[i].testType == TEST_TYPE_M_TX)
		{
			trys = 0;
		
			sprintf(text, "\nTest %d...", countAux++);
			print_dbg(text);
		
			//Notifica o CC sobre a execucao do teste e envia o comando.
			sendTestCmdFrame(test_cases[i]);
		
			//Espera o CC se preparar para o teste.
			delay_ms(CC_PREPARE_TO_TEST_DELAY);
		
			/* Aguarda ateh o CC tenha enviado todos os bytes da transmissao de teste. */
			while( (transmissionEnded != true) && (++trys < timeout) ) {};
		
			if( trys >= timeout )
			{
				print_dbg("\nErro - i2c_tests.c - masterTransmitterTest - timeout");
				testResult = false;
			}
		
			/* Compara o bytes recebidos com os bytes esperados */
			for( j = 0; j < receivedBytesCount; j++)
			{
				if( i2cBytesBuffer[j] != test_cases[i].data[j] )
				testResult = false;
			}
		
			/* Reseta as flags globais */
			receivedBytesCount = 0;
			transmissionEnded = false;
		
			/* Verifica e imprime o resultado do teste */
			if( testResult == false)
			{
				print_dbg( " FAIL" );
			}
			else
			{
				print_dbg( " PASS" );
			}	
		}
	}
}

void masterReceiverTest()
{
	print_dbg("\n\n==============================\nExecutando i2c mrx...\n==============================\n");
	
	int i, timeout = 100000000, trys, countAux = 1;
	cmd_frame_t ansFrame;
	char* text;
	bool testResult;

	for(i = 0; i < TEST_CASES_COUNT; i++ )
	{
		if(test_cases[i].testType == TEST_TYPE_M_RX)
		{
			trys = 0;
			sentBytesCount = 0;
			runningMrxTest = i; /* Para que a funcao de interrupcao TxFunction saiba qual teste estah sendo executado. */
			
			sprintf(text, "\nTest %d...", countAux++);
			print_dbg(text);
			
			//Notifica o CC sobre a execucao do teste e envia o comando.
			sendTestCmdFrame(test_cases[i]);
			
			ansFrame = rcvTestCmdAnswer();
			
			if(ansFrame.magicCode != 0)
			{
				if( ansFrame.data[0] == RESULT_TEST_FAIL )
				{
					print_dbg( " FAIL" );
				}
				else
				{
					print_dbg( " PASS" );
				}
			}
			else
			{
				print_dbg( " MagicCode error! - FAIL" );
			}
		}
	}
}

void slaveTransmitterTest()
{
	print_dbg("\n\n==============================\nExecutando i2c stx...\n==============================\n");
	print_dbg("\nFAIL - Nao implementado");
}

void slaveReceiverTest()
{
	print_dbg("\n\n==============================\nExecutando i2c srx...\n==============================\n");
	
	int i, countAux = 1;
	cmd_frame_t ansFrame;
	char* text;
	
	for(i = 0; i < TEST_CASES_COUNT; i++ )
	{
		if(test_cases[i].testType == TEST_TYPE_S_RX)
		{
			sprintf(text, "\nTest %d...", countAux++);
			print_dbg(text);
			
			//Notifica o CC sobre a execucao do teste e envia o comando.
			sendTestCmdFrame(test_cases[i]);

			//Espera o CC se preparar para o teste.
			delay_ms(CC_PREPARE_TO_TEST_DELAY);
			twim_write( TWI_MASTER, &test_cases[i].data[0], test_cases[i].dataSize, CUBE_COMPUTER_ADDRESS, false );
			
			ansFrame = rcvTestCmdAnswer();
			
			if(ansFrame.magicCode != 0)
			{
				if( ansFrame.data[0] == RESULT_TEST_FAIL )
				{
					print_dbg( " FAIL" );
				}
				else
				{
					print_dbg( " PASS" );
				}
			}
			else
			{
				print_dbg( " MagicCode error! - FAIL" );
			}
		}
	}
}