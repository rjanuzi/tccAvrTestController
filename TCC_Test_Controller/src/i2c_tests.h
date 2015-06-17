/**
 * i2c_tests.h
 *
 * Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 *
 *	Este arquivo juntamente com o arquivo \ref i2c_tests.c, reune todo o codigo fonte relacionado 
 * com os testes da interface I2C do CubeComputer. Nesses arquivos sao reunidas as funcoes e constantes
 * referentes ao teste I2C,
 */ 

#ifndef I2C_TESTS_H_
#define I2C_TESTS_H_

#include <tcc_test_controller.h>
#include <terminal_controller.h>
#include <itasat_pins_functions_stk600.h>
#include <usart.h>
#include <twim.h>
#include <twis.h>

/* Definicao de constantes */
#define AVR_ADDRESS 0x1A
#define CUBE_COMPUTER_ADDRESS 0x05
#define TWI_MASTER &TWIM0
#define TWI_SLAVE &TWIS0
#define RESULT_TEST_PASS 0xAA
#define RESULT_TEST_FAIL 0xFF
#define CC_PREPARE_TO_TEST_DELAY 1000
#define TEST_CASES_COUNT	20

/**
 *	Funcao executada sempre que o AVR (Test Controller) recebe um byte 
 * como Slave. A funcao simplesmente salva os bytes recebidos em uma 
 * mesma transmissao (ateh que exista um Stop) em um Buffer.
 *
 *	Param ReceivedData
 *		Byte recebido pela I2C.
 */
void RxFunction( uint8_t ReceivedData );

/**
 *	Funcao executada sempre que o AVR (Test Controller) envia um byte 
 * como Slave. A funcao envia os bytes a serem transmitidos durante o 
 * teste em execucao.
 *
 *	Return uint8_t
 *		Byte a ser transmitidos pelo Slave.
 */
uint8_t TxFunction();

/**
 *	Funcao executada sempre que o AVR (Test Controller) detecta um 
 * sinal de Stop no I2C. A funcao seta a flag transmissionEnded para
 * true.
 */
void StopFunction();

/**
 *	Realiza a inicializacao da interface I2C conectada a interface 
 * sob testes do equipamento.
 */
void initI2CTestsInterface();

/**
 *	Executa todos os testes I2C implementados no array test_cases.
 */
void i2c_test_all();

/** 
 * Funcao para execucao dos testes de Master Trasmitter (CubeComputer),
 * a definicao de quais testes vao ser feitos sao definidos na variavel 
 * \ref tests_M_TX definida no arquivo i2c_tests.c.
 */
void masterTransmitterTest();

/** 
 * Funcao para execucao dos testes de Master Receiver (CubeComputer),
 * a definicao de quais testes vao ser feitos sao definidos na variavel 
 * \ref tests_S_RX definida no arquivo i2c_tests.c.
 */
void masterReceiverTest();

/**
 * Funcao para execucao dos testes de Slave Receiver (CubeComputer),
 * a definicao de quais testes vao ser feitos sao definidos na variavel 
 * \ref tests_S_RX definida no arquivo i2c_tests.c.
 */
void slaveReceiverTest();

#endif /* I2C_TESTS_H_ */