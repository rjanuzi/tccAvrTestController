/*
 * sd_tests.h
 *
 * Created: 04/12/2014
 *  Author: Rafael B. Januzi
 */ 


#ifndef SD_TESTS_H_
#define SD_TESTS_H_

#include <tcc_test_controller.h>
#include <terminal_controller.h>
#include <itasat_pins_functions_stk600.h>
#include <usart.h>

#define SD_TEST_NUMBER_OFFSET 30 /* No CC o TestNumber dos testes do SD comecao de 30 */
#define CC_DELAY_TO_EXEC_TEST 1000
#define PARAM_TEST_PASS 0xAA
#define PARAM_TEST_FAIL 0xFF

void sd_test_all();
bool sd_test_01();
bool sd_test_02();
bool sd_test_03();
bool sd_test_04();

#endif /* SD_TESTS_H_ */