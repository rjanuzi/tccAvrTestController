/*
 * terminal_controller.h
 *
 *  Created: 29/09/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 *
 *  Esse arquivo, juntamente com o arquivo terminal_controller.c, eh 
 * responsavel por controlar a troca de informacao com o terminal 
 * utilizado pelo usuario para controlar o sistema. Sao definidas 
 * funcoes que facilitam o envio de mensagens de texto via interface 
 * USART, alem de funcoes para controle de comandos recebidos por 
 * essa interface.
 */ 

#ifndef TERMINAL_CONTROLLER_H_
#define TERMINAL_CONTROLLER_H_

#include <tcc_test_controller.h>
#include <usart.h>
#include <gpio.h>
#include <i2c_tests.h>
#include <string.h>
#include <stdio.h>

/*
 *	Define uma assinatura de funcao para envio de 
 * mensagens de texto para o terminal (print), 
 * essa nova funcao utiliza exatamente o codigo
 * da funcao usart_write_line(), porem aguadando
 * apenas um texto (char*) como parametro.
 */
#define print_dbg(text) usart_write_line( TERMINAL_UART, text )

/* Buffer para armazenamento temporario de comandos */
static char command_buffer[20];
/* Variavel para controlar o acesso ao buffer de comandos. */
static int free_index = 0;

/**
 *	Inicializa os pinos (GPIOs) e o controlador da USART conectada
 * ao terminal de usuario.
 */
void initTerminalInterface();

/**
 *	Funcao chamada sempre que um enter eh digitado no terminal 
 * pelo usuario, isso significa que o buffer de comandos contem 
 * um novo comando, a funcao entao analisa esse novo comando e 
 * executa a acao requisitada.
 */
void manage_command();

/**
 *	Essa funcao mantem o terminal rodando via terminal, se tudo 
 * funcionar como o esperado ela nunca termina, controla as 
 * chamadas da funcao manage_command() e coloca novos comandos 
 * no buffer de comandos.
 */
void start_terminal();

#endif /* TERMINAL_CONTROLLER_H_ */