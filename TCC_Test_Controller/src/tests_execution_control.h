/*
 * tests_execution_control.h
 *
 *  Created: 10/11/2014
 *  Author: Rafael B. Januzi (rjanuzi@gmail.com)
 *
 *	Esse arquivo, juntamente com o arquivo tests_execution_control.c, eh
 * responsavel por controlar a execucao dos testes realizados pelo sistema,
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

#define RESULT_TEST_PASS 0xAA	/* Constante para definicao do valor de sucesso de um teste. */
#define RESULT_TEST_FAIL 0xFF	/* Constante para definicao do valor de falha de um teste. */

#define MAGIC_CODE_CMDS	0x3C7E
#define MAGIC_CODE_AWS	0xE7C3

/* 
 *	Constantes para os possiveis valores para o campo 
 * testType do comando.
 *
 *	Sempre considerendo o CC como principal, ou seja 
 * ItaTests_TEST_TYPE_M_TX corresponde a um teste onde 
 * o CC funciona com Master Transmitter.
 */
#define TEST_TYPE_M_TX	0x01
#define TEST_TYPE_M_RX	0x02
#define TEST_TYPE_S_TX	0x03
#define TEST_TYPE_S_RX	0x04

/* 
 *	Estrutura de dados utilizada para definir os 
 * pacotes de dados, para controle,  trocados entre 
 * o Test Controller e o equipamento sobre teste.
 */
typedef struct __attribute__ ((__packed__)) {
	uint16_t magicCode;	/* Codigo fixo para identificacao de pacotes de controle. */
	uint8_t testType;	/* Campo para definicao do tipo de teste (ex.: TEST_TYPE_M_TX) */
	uint8_t dataSize;	/* Campo para definicao da quantidade de bytes no campo data. */
	uint8_t data[DATA_MAX_SIZE];	/* Array para armazenamento dos dados a serem transmitidos no teste. */
} cmd_frame_t;


/**
 *	Essa funcao foi implementada para facilitar a exibicao de 
 * pacotes do tipo cmd_frame_t no terminal de controle.
 *
 *	Param cmd_frame_t frame
 *		Variavel com os dados a serem exibidos no terminal.
 */
void printfCmd(cmd_frame_t frame);

/**
 *	Essa funcao realiza a inicializacao da interface USART 
 * utilizada no controle dos testes.
 */
void initTestsExecContrInterface();

/**
 *	Essa funcao criar um novo pacote de dados do tipo cmd_frame_t
 * com os campos preenchidos de acordo com os parametros passados,
 * como sao criados pacotes de comando, o campo magicCode sempre 
 * eh preenchido com o valor 0x3C7E.
 *
 *	Param uint8_t testType
 *		Tipo de teste a ser disparado com o comando;
 *	Param uint8_t paramSize
 *		Quantidade de bytes a serem transmitidos no teste.
 */
cmd_frame_t newEmptyTestCmdFrame(uint8_t testType, uint8_t paramSize);

/**
 *	Essa funcao realiza a transmissao de um pacote de comando
 * do tipo cmd_frame_t via interface USART de controle de teste,
 * esse comando eh enviado ao equipamento sob testes disparando 
 * a sequencia de teste no equipamento de acordo com os dados 
 * contidos no pacote.
 *
 *	Param cmd_frame_t frame
 *		Pacote de dados com as informacoes do teste a ser executado.
 */
void sendTestCmdFrame(cmd_frame_t frame);

/**
 *	Essa funcao aguarda, por um tempo, a recepcao de uma 
 * resposta a um comando enviado, quando a resposta e recebida
 * a funcao se encarrega de receber todos os dados e montar um pacote
 * do tipo cmd_frame_t com essas informacoes.
 */
cmd_frame_t rcvTestCmdAnswer();

#endif /* TESTS_EXECUTION_CONTROL_H_ */