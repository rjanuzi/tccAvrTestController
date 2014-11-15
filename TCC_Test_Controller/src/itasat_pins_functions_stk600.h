/*!
 * \file
 *
 *	Este arquivo header, pode ser utilizado para facilitar o uso dos pinos disponiveis no KIT STK600 + Processador AT32UC3C0512c.
 *	Aqui estao mapeados todos os pino disponivel, da seguinte forma: 
 *	
 *	- USART0_1_CLK_PIN PK5: PK5 eh o numero de GPIO de um pino de Clock da USART0 e esse pino eh a opcao 1 (apenas indexacao).
 *	- USART0_1_RTS_FUNCTION 3: 3 eh o numero da opcao de funcionalidade de Clock para o pino PK5
 *
 * \date 14/10/2013
 * \version 1.3
 * \author Rafael B. Januzi (rjanuzi@gmail.com) | Rodrigo Bittencourt (rodrigo.bittenc@gmail.com)
 */

#ifndef ITASAT_PINS_FUNCTIONS_STK600_H
#define ITASAT_PINS_FUNCTIONS_STK600_H

#define PA0 0 /* PA00 */
#define PA1 1 /* PA01 */
#define PA2 2 /* PA02 */
#define PA3 3 /* PA03 */
#define PA4 4 /* PA04 */
#define PA5 5 /* PA05 */
#define PA6 6 /* PA06 */
#define PA7 7 /* PA07 */

#define PB0 8 /* PA08 */
#define PB1 9 /* PA09 */
#define PB2 10 /* PA10 */
#define PB3 11 /* PA11 */
#define PB4 12 /* PA12 */
#define PB5 13 /* PA13 */
#define PB6 14 /* PA14 */
#define PB7 15 /* PA15 */

#define PC0 16 /* PA16 */
//#define PC1 -1 /* ADCREFP */
//#define PC2 -1 /* ADCREFN */
#define PC3 19 /* PA19 */
#define PC4 20 /* PA20 */
#define PC5 21 /* PA21 */
#define PC6 22 /* PA22 */
#define PC7 23 /* PA23 */

#define PD0 24 /* PA24 */
#define PD1 25 /* PA25 */
#define PD2 26 /* PA26 */
#define PD3 27 /* PA27 */
#define PD4 28 /* PA28 */
#define PD5 29 /* PA29 */
//#define PD6 -1 /* NA */
//#define PD7 -1 /* NA */

#define PE0 32 /* PB00 */
#define PE1 33 /* PB01 */
#define PE2 34 /* PB02 */
#define PE3 35 /* PB03 */
#define PE4 36 /* PB04 */
#define PE5 37 /* PB05 */
#define PE6 38 /* PB06 */
#define PE7 39 /* PB07 */

#define PF0 40 /* PB08 */
#define PF1 41 /* PB09 */
#define PF2 42 /* PB10 */
#define PF3 43 /* PB11 */
#define PF4 44 /* PB12 */
#define PF5 45 /* PB13 */
#define PF6 46 /* PB14 */
#define PF7 47 /* PB15 */

#define PG0 48 /* PB16 */
#define PG1 49 /* PB17 */
#define PG2 50 /* PB18 */
#define PG3 51 /* PB19 */
#define PG4 52 /* PB20 */
#define PG5 53 /* PB21 */
#define PG6 54 /* PB22 */
#define PG7 55 /* PB23 */

#define PH0 56 /* PB24 */
#define PH1 57 /* PB25 */
#define PH2 58 /* PB26 */
#define PH3 59 /* PB27 */
#define PH4 60 /* PB28 */
#define PH5 61 /* PB29 */
//#define PH6 62 /* XINO */ 
#define PH7 63 /* PB31 */

#define PJ0 64 /* PC00 */
#define PJ1 65 /* PC01 */
#define PJ2 66 /* PC02 */
#define PJ3 67 /* PC03 */
#define PJ4 68 /* PC04 */
#define PJ5 69 /* PC05 */
#define PJ6 70 /* PC06 */
#define PJ7 71 /* PC07 */

#define PK0 72 /* PC08 */
#define PK1 73 /* PC09 */
#define PK2 74 /* PC10 */
#define PK3 75 /* PC11 */
#define PK4 76 /* PC12 */
#define PK5 77 /* PC13 */
#define PK6 78 /* PC14 */
#define PK7 79 /* PC15 */

#define PL0 80 /* PC16 */
#define PL1 81 /* PC17 */
#define PL2 82 /* PC18 */
#define PL3 83 /* PC19 */
#define PL4 84 /* PC20 */
#define PL5 85 /* PC21 */
#define PL6 86 /* PC22 */
#define PL7 87 /* PC23 */

#define PM0 88 /* PC24 */
#define PM1 89 /* PC25 */
#define PM2 90 /* PC26 */
#define PM3 91 /* PC27 */
#define PM4 92 /* PC28 */
#define PM5 93 /* PC29 */
#define PM6 94 /* PC30 */
#define PM7 95 /* PC31 */

#define PN0 96 /* PD00 */
#define PN1 97 /* PD01 */
#define PN2 98 /* PD02 */
#define PN3 99 /* PD03 */
#define PN4 100 /* PD04 */
#define PN5 101 /* PD05 */
#define PN6 102 /* PD06 */
#define PN7 103 /* PD07 */

#define PP0 104 /* PD08 */
#define PP1 105 /* PD09 */
#define PP2 106 /* PD10 */
#define PP3 107 /* PD11 */
#define PP4 108 /* PD12 */
#define PP5 109 /* PD13 */
#define PP6 110 /* PD14 */
#define PP7 111 /* PD15 */

#define PQ0 112 /* PD16 */
#define PQ1 113 /* PD17 */
#define PQ2 114 /* PD18 */
#define PQ3 115 /* PD19 */
#define PQ4 116 /* PD20 */
#define PQ5 117 /* PD21 */
#define PQ6 118 /* PD22 */
#define PQ7 119 /* PD23 */

/* USART PORTS */

/* USART0 Adress */
#define USART0_ADDRESS 0xFFFF2800
#define USART0 ( *((volatile avr32_usart_t*)USART0_ADDRESS) )

/* USART0 - Opcao 1 */
#define USART0_1_RTS_PIN PK5
#define USART0_1_RTS_FUNCTION 3
#define USART0_1_CTS_PIN PK6
#define USART0_1_CTS_FUNCTION 3
#define USART0_1_CLK_PIN PK6
#define USART0_1_CLK_FUNCTION 1  
#define USART0_1_RX_PIN PK7
#define USART0_1_RX_FUNCTION 3
#define USART0_1_TX_PIN PL0
#define USART0_1_TX_FUNCTION 3

/* USART0 - Opcao 2 */
#define USART0_2_RTS_PIN 126 /* TGT_PDATA6 */
#define USART0_2_RTS_FUNCTION 0
#define USART0_2_CTS_PIN 125 /* TGT_PDATA5 */
#define USART0_2_CTS_FUNCTION 0
#define USART0_2_CLK_PIN 125 /* TGT_PDATA5 */
#define USART0_2_CLK_FUNCTION 2
#define USART0_2_RX_PIN 124 /* TGT_PDATA4 */
#define USART0_2_RX_FUNCTION 0
#define USART0_2_TX_PIN 123 /* TGT_PDATA3 */
#define USART0_2_TX_FUNCTION 0

/* USART0 - Opcao 3 */
#define USART0_3_CLK_PIN PE0 /* TGT_PDATA5 */
#define USART0_3_CLK_FUNCTION 0


/* USART1 Adress */
#define USART1_ADDRESS 0xFFFD1400
#define USART1 ( *((volatile avr32_usart_t*)USART1_ADDRESS) )

/* USART1 - Opcao 1 */
#define USART1_1_CLK_PIN PE6
#define USART1_1_CLK_FUNCTION 3
#define USART1_1_CTS_PIN PF7
#define USART1_1_CTS_FUNCTION 0
#define USART1_1_RTS_PIN PP6
#define USART1_1_RTS_FUNCION 0
#define USART1_1_RX_PIN PG0
#define USART1_1_RX_FUNCTION 0
#define USART1_1_TX_PIN PG1
#define USART1_1_TX_FUNCTION 0


/* USART1 - Opcao 2 */
#define USART1_2_CLK_PIN PF7
#define USART1_2_CLK_FUNCTION 1
#define USART1_2_CTS_PIN PP5
#define USART1_2_CTS_FUNCTION 0
#define USART1_2_RTS_PIN PF6
#define USART1_2_RTS_FUNCTION 0
#define USART1_2_RX_PIN PP4
#define USART1_2_RX_FUNCTION 0
#define USART1_2_TX_PIN PP3
#define USART1_2_TX_FUNCTION 0

/* USART1 - Opcao 3 */
#define USART1_3_CLK_PIN PP5
#define USART1_3_CLK_FUNCTION 1

/* USART2 - Adress */
#define USART2_ADDRESS 0xFFFF2C00
#define USART2 ( *((volatile avr32_usart_t*)USART2_ADDRESS) )

/*USART 2 - Opcao 1 */
#define USART2_1_CLK_PIN PJ6
#define USART2_1_CLK_FUNCTION 1
#define USART2_1_CTS_PIN PJ0
#define USART2_1_CTS_FUNCTION 2
#define USART2_1_RTS_PIN PJ1
#define USART2_1_RTS_FUNCTION 2
#define USART2_1_RX_PIN PJ2
#define USART2_1_RX_FUNCTION 2
#define USART2_1_TX_PIN PJ3
#define USART2_1_TX_FUNCTION 2

/*USART2 - Opcao 2 */
#define USART2_2_CLK_PIN PK4 
#define USART2_2_CLK_FUNCTION 3
#define USART2_2_CTS_PIN PJ6
#define USART2_2_CTS_FUNCTION 2
#define USART2_2_RTS_PIN PJ7 
#define USART2_2_RTS_FUNCTION 2
#define USART2_2_RX_PIN PJ5
#define USART2_2_RX_FUNCTION 2
#define USART2_2_TX_PIN PJ4
#define USART2_2_TX_FUNCTION 2

/* USART3 - Adress */
#define USART3_ADDRESS 0xFFFF3000
#define USART3 ( *((volatile avr32_usart_t*)USART3_ADDRESS) )

/* USART3 - OPcaO 1 */
#define USART3_1_CLK_PIN PQ1
#define USART3_1_CLK_FUNCTION 3
#define USART3_1_CTS_PIN PQ7
#define USART3_1_CTS_FUNCTION 0
#define USART3_1_RTS_PIN 120 /* TGT_PDATA0 */
#define USART3_1_RTS_FUNCTION 0
#define USART3_1_RX_PIN PL2
#define USART3_1_RX_FUNCTION 5
#define USART3_1_TX_PIN PL1
#define USART3_1_TX_FUNCTION 5

/* USART3 - Opcao 2 */
#define USART3_2_CLK_PIN PQ7
#define USART3_2_CLK_FUNCTION 1 
#define USART3_2_CTS_PIN PL3
#define USART3_2_CTS_FUNCTION 5
#define USART3_2_RTS_PIN PL4
#define USART3_2_RTS_FUNCTION 5
#define USART3_2_RX_PIN PQ0
#define USART3_2_RX_FUNCTION 1
#define USART3_2_TX_PIN PP7
#define USART3_2_TX_FUNCTION 1

/* USART3 - Opcao 3 */
#define USART3_3_CLK_PIN PE5
#define USART3_3_CLK_FUNCTION 3
#define USART3_3_CTS_PIN PQ1
#define USART3_3_CTS_FUNCTION 1
#define USART3_3_RTS_PIN PQ2
#define USART3_3_RTS_FUNCTION 1
#define USART3_3_RX_PIN PQ6
#define USART3_3_RX_FUNCTION 0
#define USART3_3_TX_PIN PQ5
#define USART3_3_TX_FUNCTION 0

/* USART3 - Opcao 4 */
#define USART3_4_CLK_PIN PL6
#define USART3_4_CLK_FUNCTION 4

/* USART4 - Adress */
#define USART4_ADDRESS 0xFFFD2800
#define USART4 ( *((volatile avr32_usart_t*)USART4_ADDRESS) )

/* USART4 - Opcao 1 */
#define USART4_1_TX_PIN PM1
#define USART4_1_TX_FUNCTION 4
#define USART4_1_RX_PIN PM2
#define USART4_1_RX_FUNCTION 4
#define USART4_1_CTS_PIN PM3
#define USART4_1_CTS_FUNCTION 4
#define USART4_1_RTS_PIN PM4
#define USART4_1_RTS_FUNCTION 4
#define USART4_1_CLK_PIN PM7
#define USART4_1_CLK_FUNCTION 4

/* USART4 - Opcao 2 */
#define USART4_2_TX_PIN PN7
#define USART4_2_TX_FUNCTION 4
#define USART4_2_RX_PIN PP0
#define USART4_2_RX_FUNCTION 4
#define USART4_2_CTS_PIN PP1
#define USART4_2_CTS_FUNCTION 4
#define USART4_2_RTS_PIN PP2
#define USART4_2_RTS_FUNCTION 4
#define USART4_2_CLK_PIN 121 /* TGT_PDATA1 */
#define USART4_2_CLK_FUNCTION 4

/* USART4 - Opcao 3 */
#define USART4_3_TX_PIN PK0
#define USART4_3_TX_FUNCTION 4
#define USART4_3_RX_PIN PK1
#define USART4_3_RX_FUNCTION 4

/* SPI PORTS */

/* SPI0 - Adress */
#define SPI0_ADDRESS 0xFFFD1800
#define SPI0 ( *((volatile avr32_spi_t*)SPI0_ADDRESS) )

/* SPI0 - Opcao 1 */
#define SPI0_1_MOSI_PIN PF2
#define SPI0_1_MOSI_FUNCTION 1
#define SPI0_1_MISO_PIN PF3
#define SPI0_1_MISO_FUNCTION 1
#define SPI0_1_SCK_PIN PF4
#define SPI0_1_SCK_FUNCTION 1
#define SPI0_1_NPCS0_PIN PF5
#define SPI0_1_NPCS0_FUNCTION 1
#define SPI0_1_NPCS1_PIN PF6
#define SPI0_1_NPCS1_FUNCTION 1
#define SPI0_1_NPCS2_PIN PG0
#define SPI0_1_NPCS2_FUNCTION 1
#define SPI0_1_NPCS3_PIN PG1
#define SPI0_1_NPCS3_FUNCTION 1

/* SPI0 - Opcao 2 */
#define SPI0_2_NPCS0_PIN PB4
#define SPI0_2_NPCS0_FUNCTION 1
#define SPI0_2_NPCS1_PIN PB5
#define SPI0_2_NPCS1_FUNCTION 1
#define SPI0_2_NPCS2_PIN PJ1
#define SPI0_2_NPCS2_FUNCTION 1
#define SPI0_2_NPCS3_PIN PJ2
#define SPI0_2_NPCS3_FUNCTION 1

/* SPI0 - Opcao 3 */
#define SPI0_3_NPCS0_PIN PH5
#define SPI0_3_NPCS0_FUNCTION 1
#define SPI0_3_NPCS1_PIN PJ0
#define SPI0_3_NPCS1_FUNCTION 1
#define SPI0_3_NPCS2_PIN PL1
#define SPI0_3_NPCS2_FUNCTION 1

/* SPI0 - Opcao 4 */
#define SPI0_4_NPCS0_PIN PK7
#define SPI0_4_NPCS0_FUNCTION 1
#define SPI0_4_NPCS1_PIN PL0
#define SPI0_4_NPCS1_FUNCTION 1
#define SPI0_4_NPCS2_PIN PM6
#define SPI0_4_NPCS2_FUNCTION 0

/* SPI0 - Opcao 5 */
#define SPI0_5_NPCS0_PIN PN3
#define SPI0_5_NPCS0_FUNCTION 0
#define SPI0_5_NPCS1_PIN PM5
#define SPI0_5_NPCS1_FUNCTION 0

/* SPI1 - Adress */
#define SPI1_ADDRESS 0xFFFF3400
#define SPI1 ( *((volatile avr32_spi_t*)SPI1_ADDRESS) )

/* SPI1 - Opcao 1 */
#define SPI1_1_MOSI_PIN PE4
#define SPI1_1_MOSI_FUNCTION 0
#define SPI1_1_MISO_PIN PE5
#define SPI1_1_MISO_FUNCTION 0
#define SPI1_1_SCK_PIN PE6
#define SPI1_1_SCK_FUNCTION 0
#define SPI1_1_NPCS0_PIN PE7
#define SPI1_1_NPCS0_FUNCTION 0
#define SPI1_1_NPCS1_PIN PF0
#define SPI1_1_NPCS1_FUNCTION 0
#define SPI1_1_NPCS2_PIN PF1
#define SPI1_1_NPCS2_FUNCTION 0
#define SPI1_1_NPCS3_PIN PD1
#define SPI1_1_NPCS3_FUNCTION 1

/* SPI1 - Opcao 2 */
#define SPI1_2_MOSI_PIN PG3
#define SPI1_2_MOSI_FUNCTION 1
#define SPI1_2_MISO_PIN PG4
#define SPI1_2_MISO_FUNCTION 1
#define SPI1_2_SCK_PIN PG5
#define SPI1_2_SCK_FUNCTION 1
#define SPI1_2_NPCS0_PIN PB6
#define SPI1_2_NPCS0_FUNCTION 1
#define SPI1_2_NPCS1_PIN PB7
#define SPI1_2_NPCS1_FUNCTION 1
#define SPI1_2_NPCS2_PIN PD0
#define SPI1_2_NPCS2_FUNCTION 1
#define SPI1_2_NPCS3_PIN PG6
#define SPI1_2_NPCS3_FUNCTION 1

/* SPI1 - Opcao 3 */
#define SPI1_3_MOSI_PIN PH4
#define SPI1_3_MOSI_FUNCTION 1
#define SPI1_3_MISO_PIN PH3
#define SPI1_3_MISO_FUNCTION 1
#define SPI1_3_SCK_PIN PH2
#define SPI1_3_SCK_FUNCTION 1
#define SPI1_3_NPCS0_PIN PH1
#define SPI1_3_NPCS0_FUNCTION 1
#define SPI1_3_NPCS1_PIN PH0
#define SPI1_3_NPCS1_FUNCTION 1
#define SPI1_3_NPCS2_PIN PG7
#define SPI1_3_NPCS2_FUNCTION 1
#define SPI1_3_NPCS3_PIN PK2
#define SPI1_3_NPCS3_FUNCTION 1

/* SPI1 - Opcao 4 */
#define SPI1_4_NPCS1_PIN PK0
#define SPI1_4_NPCS1_FUNCTION 1
#define SPI1_4_NPCS2_PIN PK1
#define SPI1_4_NPCS2_FUNCTION 1
#define SPI1_4_NPCS3_PIN PM4
#define SPI1_4_NPCS3_FUNCTION 0

/* CAN INTERFACE PORTS */

#define CANIF_ADDRESS 0xFFFD1C00
#define CANIF ( *((volatile avr32_canif_t*)CANIF_ADDRESS) )

/* CAN0 - Opcao 1 */
#define CAN0_1_RX_PIN PE4
#define CAN0_1_RX_FUNCTION 1
#define CAN0_1_TX_PIN PE5
#define CAN0_1_TX_FUNCTION 1

/* CAN0 - Opcao 2 */
#define CAN0_2_RX_PIN PG0
#define CAN0_2_RX_FUNCTION 4
#define CAN0_2_TX_PIN PG1
#define CAN0_2_TX_FUNCTION 4

/* CAN0 - Opcao 3 */
#define CAN0_3_RX_PIN PL5
#define CAN0_3_RX_FUNCTION 1
#define CAN0_3_TX_PIN PL6
#define CAN0_3_TX_FUNCTION 1

/* CAN0 - Opcao 4 */
#define CAN0_4_RX_PIN PP1
#define CAN0_4_RX_FUNCTION 1
#define CAN0_4_TX_PIN PP2
#define CAN0_4_TX_FUNCTION 1

/* CAN0 - Opcao 5 */
#define CAN0_5_RX_PIN 123 /*TGT_PDATA3 */
#define CAN0_5_RX_FUNCTION 1
#define CAN0_5_TX_PIN 124 /*TGT_PDATA4 */
#define CAN0_5_TX_FUNCTION 1

/* CAN1 - Opcao 1 */
#define CAN1_1_TX_PIN PJ0
#define CAN1_1_TX_FUNCTION 4
#define CAN1_1_RX_PIN PJ1
#define CAN1_1_RX_FUNCTION 4

/* CAN1 - Opcao 2 */
#define CAN1_2_RX_PIN PK3
#define CAN1_2_RX_FUNCTION 1
#define CAN1_2_TX_PIN PK4
#define CAN1_2_TX_FUNCTION 1

/* CAN1 - Opcao 3 */
#define CAN1_3_TX_PIN PA0
#define CAN1_3_TX_FUNCTION 1
#define CAN1_3_RX_PIN PA1
#define CAN1_3_RX_FUNCTION 1

/* CAN1 - Opcao 4 */
#define CAN1_4_RX_PIN PK7
#define CAN1_4_RX_FUNCTION 4
#define CAN1_4_TX_PIN PL0
#define CAN1_4_TX_FUNCTION 4

/* CAN1 - Opcao 5 */
#define CAN1_5_RX_PIN PL7
#define CAN1_5_RX_FUNCTION 1
#define CAN1_5_TX_PIN PM0
#define CAN1_5_TX_FUNCTION 1

/* CAN1 - Opcao 6 */
#define CAN1_6_RX_PIN PE0
#define CAN1_6_RX_FUNCTION 1
#define CAN1_6_TX_PIN PE1
#define CAN1_6_TX_FUNCTION 1

/* TWIM0 - Adress */
#define TWIM0_ADDRESS 0xFFFF3800
#define TWIM0 ( *((volatile avr32_twim_t*)TWIM0_ADDRESS) )

/* TWIM0 - Opcao 1 */
#define TWIM0_1_TWD_PIN PJ2 /* PC02 */
#define TWIM0_1_TWD_FUNCTION 0
#define TWIM0_1_TWCK_PIN PJ3 /* PC03 */
#define TWIM0_1_TWCK_FUNCTION 0
#define TWIM0_1_TWALM_PIN PJ6 /* PC06 */
#define TWIM0_1_TWALM_FUNCTION 5

/* TWIM1 - Adress */
#define TWIM1_ADDRESS 0xFFFF3C00
#define TWIM1 ( *((volatile avr32_twim_t*)TWIM1_ADDRESS) )

/* TWIM1 - Opcao 1 */
#define TWIM1_1_TWD_PIN PJ4
#define TWIM1_1_TWD_FUNCTION 0
#define TWIM1_1_TWCK_PIN PJ5
#define TWIM1_1_TWCK_FUNCTION 0
#define TWIM1_1_TWALM_PIN 71
#define TWIM1_1_TWALM_FUNCTION 5

/* TWIM2 - Adress */
#define TWIM2_ADDRESS 0xFFFD2C00
#define TWIM2 ( *((volatile avr32_twim_t*)TWIM2_ADDRESS) )

/* TWIM2 - Opcao 1 */
#define TWIM2_1_TWD_PIN 70
#define TWIM2_1_TWD_FUNCTION 4
#define TWIM2_1_TWCK_PIN 71
#define TWIM2_1_TWCK_FUNCTION 4

/* TWIS0 - Adress */
#define TWIS0_ADDRESS 0xFFFF4000
#define TWIS0 ( *((volatile avr32_twis_t*)TWIS0_ADDRESS) )

/* TWIS0 - Opcao 1 */
#define TWIS0_1_TWD_PIN PJ2 /* PC02 */
#define TWIS0_1_TWD_FUNCTION 0
#define TWIS0_1_TWCK_PIN PJ3 /* PC03 */
#define TWIS0_1_TWCK_FUNCTION 0
#define TWIS0_1_TWALM_PIN PJ6 /* PC06 */
#define TWIS0_1_TWALM_FUNCTION 5

/* TWIS1 - Adress */
#define TWIS1_ADDRESS 0xFFFF4400
#define TWIS1 ( *((volatile avr32_twis_t*)TWIS1_ADDRESS) )

/* TWIS1 - Opcao 1 */
#define TWIS1_1_TWD_PIN 68
#define TWIS1_1_TWD_FUNCTION 0
#define TWIS1_1_TWCK_PIN 69
#define TWIS1_1_TWCK_FUNCTION 0
#define TWIS1_1_TWALM_PIN 71
#define TWIS1_1_TWALM_FUNCTION 5

/* TWIS2 - Adress */
#define TWIS2_ADDRESS 0xFFFD3000
#define TWIS2 ( *((volatile avr32_twis_t*)TWIS2_ADDRESS) )

/* TWIS2 - Opcao 1 */
#define TWIS2_1_TWD_PIN 70
#define TWIS2_1_TWD_FUNCTION 4
#define TWIS2_1_TWCK_PIN 71
#define TWIS2_1_TWCK_FUNCTION 4

#endif /* ITASAT_PINS_FUNCTIONS_STK600_H */