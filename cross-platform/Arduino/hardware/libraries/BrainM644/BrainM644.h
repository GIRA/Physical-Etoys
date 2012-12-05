#ifndef Brain_M644__h
#define Brain_M644__h


//DEPENDENCIES: the Multiplo MotorDC library:
#include "../MotorDC/MotorDC.h"


// ATMEL ATMEGA644P / SANGUINO / Multiplo.Brain.M644 / Multiplo.Brain.M1284
//
//		      	              +---\/---+
// Yellow LED INT0 (D0) PB0  1|        |40  PA0 (A0 / D31 / S0_In / S0_Out / Batt)
// Red LED	  INT1 (D1) PB1  2|        |39  PA1 (A1 / D30 / S1_In / S1_Out)
// Run Button INT2 (D2) PB2  3|        |38  PA2 (A2 / D29 / D0_Rx_In / D0_Rx_Out)
//			   PWM (D3) PB3  4|        |37  PA3 (A3 / D28 / D0_Tx_In / D0_Tx_Out)
//			   PWM (D4) PB4  5|        |36  PA4 (A4 / D27 / D1_Rx_In / D1_Rx_Out)
//			  MOSI (D5) PB5  6|        |35  PA5 (A5 / D26 / D1_Tx_In / D1_Tx_Out)
//			  MISO (D6) PB6  7|        |34  PA6 (A6 / D25 / D2_Rx_In / D2_Rx_Out)
//			   SCK (D7) PB7  8|        |33  PA7 (A7 / D24 / D2_Tx_In / D2_Tx_Out)
//		    	        RST  9|        |32  AREF
//			            VCC 10|        |31  GND
//			            GND 11|        |30  AVCC
//		          	  XTAL2 12|        |29  PC7 (D23) Motor1_D1
//		      	      XTAL1 13|        |28  PC6 (D22) Motor1_D0
//	Comm0_Rx  RX0 (D8)  PD0 14|        |27  PC5 (D21) TDI
//	Comm0_Tx  TX0 (D9)  PD1 15|        |26  PC4 (D20) TDO
//	Comm1_Rx  RX1 (D10) PD2 16|        |25  PC3 (D19) TMS
//	Comm1_Tx  TX1 (D11) PD3 17|        |24  PC2 (D18) TCK
//	Motor1_EN PWM (D12) PD4 18|        |23  PC1 (D17) SDA 	J16
//	Motor0_EN PWM (D13) PD5 19|        |22  PC0 (D16) SCL 	J5
//  Motor0_D0 PWM (D14) PD6 20|        |21  PD7 (D15) PWM Motor0_D1
//							  +--------+

#define S0_In		0
#define S0_Out		31

#define	S1_In		1
#define	S1_Out		30

#define D0_Rx_In 	2
#define D0_Rx_Out	29
#define D0_Tx_In	3
#define D0_Tx_Out	28

#define D1_Rx_In	4
#define D1_Rx_Out	27
#define D1_Tx_In	5
#define D1_Tx_Out	26

#define D2_Rx_In	6
#define D2_Rx_Out	25
#define D2_Tx_In	7
#define D2_Tx_Out	24

extern MotorDC motor0;
extern MotorDC motor1;

#endif
