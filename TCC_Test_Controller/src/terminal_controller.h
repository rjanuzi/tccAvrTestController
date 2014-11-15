/*
 * terminal_controller.h
 *
 * Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 */ 


#ifndef TERMINAL_CONTROLLER_H_
#define TERMINAL_CONTROLLER_H_

#include <tcc_test_controller.h>
#include <usart.h>
#include <gpio.h>
#include <i2c_tests.h>
#include <string.h>
#include <stdio.h>

#define print_dbg(text) usart_write_line( TERMINAL_UART, text )

static char command_buffer[20];
static int free_index = 0;

void initTerminalInterface();
void start_terminal();

#endif /* TERMINAL_CONTROLLER_H_ */