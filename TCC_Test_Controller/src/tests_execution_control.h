/*
 * tests_execution_control.h
 *
 * Created: 10/11/2014 14:59:05
 *  Author: itasat
 */ 


#ifndef TESTS_EXECUTION_CONTROL_H_
#define TESTS_EXECUTION_CONTROL_H_

#include <terminal_controller.h>
#include <tcc_test_controller.h>
#include <usart.h>
#include <i2c_tests.h>
#include <string.h>
#include <stdio.h>
#include <delay.h>

#define DATA_MAX_SIZE	255 /* utilizando um byte para o paramSize (2^8) */

#define RESULT_TEST_PASS 0xAA
#define RESULT_TEST_FAIL 0xFF

/* Constantes para os possíveis valores para o campo testType do comando.
 * Sempre considerendo o CC como principal, ou seja ItaTests_TEST_TYPE_M_TX
 * corresponde a um teste onde o CC funciona com Master Transmitter. */
#define TEST_TYPE_M_TX	0x01
#define TEST_TYPE_M_RX	0x02
#define TEST_TYPE_S_TX	0x03
#define TEST_TYPE_S_RX	0x04

typedef struct __attribute__ ((__packed__)) {
	uint16_t magicCode;
	uint8_t testType;
	uint8_t dataSize;
	uint8_t data[DATA_MAX_SIZE];
} cmd_frame_t;

void printfCmd(cmd_frame_t frame);
void initTestsExecContrInterface();
cmd_frame_t newEmptyTestCmdFrame(uint8_t testType, uint8_t paramSize);
void freeCmdFrame(cmd_frame_t frame);
void sendTestCmdFrame(cmd_frame_t frame);
cmd_frame_t rcvTestCmdAnswer();

#endif /* TESTS_EXECUTION_CONTROL_H_ */