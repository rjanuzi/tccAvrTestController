/*
 * tcc_test_controller.h
 *
 * Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 */ 


#ifndef TCC_TEST_CONTROLLER_H_
#define TCC_TEST_CONTROLLER_H_

#include <itasat_pins_functions_stk600.h>
#include <terminal_controller.h>
#include <tests_execution_control.h>

#define CPU_HZ 16000000

#define TERMINAL_UART &USART1
#define TERMINAL_UART_BAUD 115200
#define ENTER_CHAR 0x0D

#define TESTS_EXEC_CTRL_UART &USART0
#define TESTS_EXEC_CTRL_UART_BAUD 115200

#define ITASAT_LED0 PB0
#define ITASAT_LED1 PB1
#define ITASAT_LED2 PB2
#define ITASAT_LED3 PB3
#define ITASAT_LED4 PB4
#define ITASAT_LED5 PB5
#define ITASAT_LED6 PB6
#define ITASAT_LED7 PB7

void general_initialize();

#endif /* TCC_TEST_CONTROLLER_H_ */