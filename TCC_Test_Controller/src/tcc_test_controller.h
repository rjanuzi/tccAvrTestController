/**
 * tcc_test_controller.h
 *
 *  Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 *  
 *  Esse arquivo, juntamente com o arquivo tcc_test_controller.c, reune as funcoes e 
 * constantes utilizadas para inicializar o sistema de controle de testes.
 */ 

#ifndef TCC_TEST_CONTROLLER_H_
#define TCC_TEST_CONTROLLER_H_

#include <itasat_pins_functions_stk600.h>
#include <terminal_controller.h>
#include <tests_execution_control.h>

#define CPU_HZ 16000000	/* Frequencia de clock utilizada na placa STK600 */

#define TERMINAL_UART		&USART1	/* Endereco do contralador da USART1, conecta do terminal de controle. */
#define TERMINAL_UART_BAUD	115200	/* Taxa de transmissao da interface do terminal de controle. */
#define ENTER_CHAR			0x0D	/* Valor numero recebido via termina, quando um enter eh clicado pelo usuario */

#define TESTS_EXEC_CTRL_UART		&USART0 /* Endereco do controlador da USART0, utilizada para o controle dos testes.*/
#define TESTS_EXEC_CTRL_UART_BAUD	115200	/* Taxa de transmissao da interface de contrle de testes. */

/* Definicao dos pinos conectados aos LEDs da placa STK600 */
#define ITASAT_LED0 PB0
#define ITASAT_LED1 PB1
#define ITASAT_LED2 PB2
#define ITASAT_LED3 PB3
#define ITASAT_LED4 PB4
#define ITASAT_LED5 PB5
#define ITASAT_LED6 PB6
#define ITASAT_LED7 PB7

/**
 *	Funcao utilizada para inicializacao do sistema de testes, ela eh responsavel por 
 * realizar as inicializacoes basicas do processador e chamar as funcoes de inicializacao
 * de cada parte do sistema de testes. 
 */
void general_initialize();

#endif /* TCC_TEST_CONTROLLER_H_ */