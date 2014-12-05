/*
 * i2c_tests.h
 *
 * Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 */ 


#ifndef I2C_TESTS_H_
#define I2C_TESTS_H_

#include <tcc_test_controller.h>
#include <terminal_controller.h>
#include <itasat_pins_functions_stk600.h>
#include <usart.h>
#include <twim.h>
#include <twis.h>

#define AVR_ADDRESS 0x02
#define CUBE_COMPUTER_ADDRESS 0x05
#define TWI_MASTER &TWIM0
#define TWI_SLAVE &TWIS0
#define PARAM_TEST_PASS 0xAA
#define PARAM_TEST_FAIL 0xFF
#define CC_PREPARE_TO_TEST_DELAY 500

typedef struct __attribute__((__packed__)) {
	uint16_t NBytes; /* {4, …, 65536} */
	uint8_t AddrSize; /* {7} */
	uint8_t Addr; /* {1, ..., 32} */
	uint8_t CommType; /* ITA_DBG_TESTS_COMM_TYPE_X */
	uint8_t OperationMode; /* ITA_DBG_TESTS_OPER_MODE_M_M */
	uint8_t ACKRecption; /* ITA_DBG_TESTS_ACKReception_ACK ou ITA_DBG_TESTS_ACKReception_NACK */
	uint8_t Baudrate; /* ITA_DBG_TESTS_Baudrate_400 */
} ItaTestSys_i2cTestCaseParam_t;

void RxFunction( uint8_t ReceivedData );
uint8_t TxFunction();
void StopFunction();
void initI2CTestsInterface();

void i2c_test_all();
bool i2c_test_01();
bool i2c_test_02();

#endif /* I2C_TESTS_H_ */