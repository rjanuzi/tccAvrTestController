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
#include <dlmalloc.h>

#define PARAM_TEST_PASS 0xAA
#define PARAM_TEST_FAIL 0xFF

typedef struct __attribute__ ((__packed__)) {
	uint16_t magicCode;
	uint16_t testNumber;
	uint8_t dataSize;
	uint8_t* data;
} cmd_frame_t;

void printfCmd(cmd_frame_t frame);
void initTestsExecContrInterface();
cmd_frame_t newEmptyTestCmdFrame(uint16_t testNumber, uint8_t paramSize);
void freeCmdFrame(cmd_frame_t frame);
void sendTestCmdFrame(cmd_frame_t frame);
cmd_frame_t rcvTestCmdAnswer();

#endif /* TESTS_EXECUTION_CONTROL_H_ */