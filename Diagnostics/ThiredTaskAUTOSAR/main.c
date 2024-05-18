/*
 * main.c
 *
 *  Created on: May 18, 2024
 *      Author: M.Moussa
 */

#include "StdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "UART_Interface.h"

void main() {
	DIO_Init();
	UART_Init();
	u8 arr_serv1[] = { 127, 49, 51 };
	u8 arr_serv2[] = { 103, 1, 0, 0, 0, 0 };
	u8 arr_serv3[] = { 103, 2 };
	u8 arr_serv4[] = { 103, 1, 170, 0 };
	u8 arr_rec1[] = { 0 };
	u8 arr_rec2[] = { 0 };
	u8 arr_rec3[] = { 0 };
	u8 arr_rec4[] = { 0 };

	u32 collector = 0;

	/**********************************************************************/
	for (u8 i = 0; i < 4; i++) {
		arr_rec1[i] = UART_receiveByteSynch();
	}

	for (u8 i = 0; i < 4; i++) {
		collector += arr_rec1[i];
	}

	if (collector == 220) {

		for (u8 i = 0; i < 3; i++) {
			UART_sendByte(arr_serv1[i]);
		}

		/***********************************************************************/
		arr_rec2[0] = UART_receiveByteSynch();
		arr_rec2[1] = UART_receiveByteSynch();
		collector = 0;

		for (u8 i = 0; i < 2; i++) {
			collector += arr_rec2[i];
		}
		if (collector == 40) {

			for (u8 i = 0; i < 6; i++) {

				UART_sendByte(arr_serv2[i]);
			}
		}

		/***********************************************************************/

		for (u8 i = 0; i < 6; i++) {
			arr_rec3[i] = UART_receiveByteSynch();
		}
		collector = 0;

		if (collector == 104) {

			for (u8 i = 0; i < 2; i++) {

				UART_sendByte(arr_serv3[i]);
			}

		}
		/***************************************************************************/

		for (u8 i = 0; i < 4; i++) {

			arr_rec4[i] = UART_receiveByteSynch();
		}

		collector = 0;

		if (collector == 220) {

			for (u8 i = 0; i < 4; i++) {

				UART_sendByte(arr_serv4[i]);
			}
			DIO_WritePin(PINA0, HIGH);
		}
	}
	while (1) {

	}
}

