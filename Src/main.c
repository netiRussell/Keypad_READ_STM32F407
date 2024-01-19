#include <stdint.h>
#include <stdio.h>


union GPIO_1digitPerR{

	uint32_t binary_code;

	struct {
		uint32_t pin0: 1;
		uint32_t pin1: 1;
		uint32_t pin2: 1;
		uint32_t pin3: 1;
		uint32_t pin4: 1;
		uint32_t pin5: 1;
		uint32_t pin6: 1;
		uint32_t pin7: 1;
		uint32_t pin8to15: 8;
		uint32_t reserved: 16;
	} Pins;

};

union GPIO_2digitsPerR{

	uint32_t binary_code;

	struct{
		uint32_t pin0: 2;
		uint32_t pin1: 2;
		uint32_t pin2: 2;
		uint32_t pin3: 2;
		uint32_t pin4: 2;
		uint32_t pin5: 2;
		uint32_t pin6: 2;
		uint32_t pin7: 2;
		uint32_t pin8to15: 16;
	} Pins;

};

void delay(){
	for(int i = 0; i < 400000; i++);
}


int main(void)
{

	// Pointers
	uint32_t volatile *AHB1_bus = (uint32_t*)0x40023830;

	uint32_t volatile *GPIOA_mode = (uint32_t*) 0x40020000;
	uint32_t volatile *GPIOA_input = (uint32_t*) 0x40020010;
	uint32_t volatile *GPIOA_output = (uint32_t*) 0x40020014;
	uint32_t volatile *GPIOA_resistor = (uint32_t*) 0x4002000C;


	// Enabling the AHB1 bus for GPIOA
	*AHB1_bus = *AHB1_bus | 0b1;


	// Setting modes of the pins PA0-PA7
	union GPIO_2digitsPerR GPIOA2dPerR;
	GPIOA2dPerR.binary_code = *GPIOA_mode;

	GPIOA2dPerR.Pins.pin0 = 0b00;
	GPIOA2dPerR.Pins.pin2 = 0b00;
	GPIOA2dPerR.Pins.pin4 = 0b00;
	GPIOA2dPerR.Pins.pin6 = 0b00;
	GPIOA2dPerR.Pins.pin1 = 0b01;
	GPIOA2dPerR.Pins.pin3 = 0b01;
	GPIOA2dPerR.Pins.pin5 = 0b01;
	GPIOA2dPerR.Pins.pin7 = 0b01;

	*GPIOA_mode = GPIOA2dPerR.binary_code;


	// Enabling the inner pull-up resistors for the pins PA0-PA7
	GPIOA2dPerR.binary_code = *GPIOA_resistor;

	GPIOA2dPerR.Pins.pin0 = 0b01;
	GPIOA2dPerR.Pins.pin2 = 0b01;
	GPIOA2dPerR.Pins.pin4 = 0b01;
	GPIOA2dPerR.Pins.pin6 = 0b01;

	*GPIOA_resistor = GPIOA2dPerR.binary_code;


    /* Loop forever */
	union GPIO_1digitPerR GPIOA1dPerR;
	while(1){

		// 1st row
		GPIOA1dPerR.binary_code = *GPIOA_output;
		GPIOA1dPerR.Pins.pin1 = 0b0;
		GPIOA1dPerR.Pins.pin3 = 0b1;
		GPIOA1dPerR.Pins.pin5 = 0b1;
		GPIOA1dPerR.Pins.pin7 = 0b1;
		*GPIOA_output = GPIOA1dPerR.binary_code;

		GPIOA1dPerR.binary_code = *GPIOA_input;
		if(GPIOA1dPerR.Pins.pin0 != 0b1) {
			delay();
			printf("1\n");
		} else if(GPIOA1dPerR.Pins.pin2 != 0b1){
			delay();
			printf("2\n");
		} else if(GPIOA1dPerR.Pins.pin4 != 0b1){
			delay();
			printf("3\n");
		} else if(GPIOA1dPerR.Pins.pin6 != 0b1){
			delay();
			printf("A\n");
		}
		*GPIOA_input = GPIOA1dPerR.binary_code;


		// 2nd row
		GPIOA1dPerR.binary_code = *GPIOA_output;
		GPIOA1dPerR.Pins.pin1 = 0b1;
		GPIOA1dPerR.Pins.pin3 = 0b0;
		*GPIOA_output = GPIOA1dPerR.binary_code;

		GPIOA1dPerR.binary_code = *GPIOA_input;
		if (GPIOA1dPerR.Pins.pin0 != 0b1) {
			delay();
			printf("4\n");
		} else if (GPIOA1dPerR.Pins.pin2 != 0b1) {
			delay();
			printf("5\n");
		} else if (GPIOA1dPerR.Pins.pin4 != 0b1) {
			delay();
			printf("6\n");
		} else if (GPIOA1dPerR.Pins.pin6 != 0b1) {
			delay();
			printf("B\n");
		}
		*GPIOA_input = GPIOA1dPerR.binary_code;


		// 3rd row
		GPIOA1dPerR.binary_code = *GPIOA_output;
		GPIOA1dPerR.Pins.pin3 = 0b1;
		GPIOA1dPerR.Pins.pin5 = 0b0;
		*GPIOA_output = GPIOA1dPerR.binary_code;

		GPIOA1dPerR.binary_code = *GPIOA_input;
		if (GPIOA1dPerR.Pins.pin0 != 0b1) {
			delay();
			printf("7\n");
		} else if (GPIOA1dPerR.Pins.pin2 != 0b1) {
			delay();
			printf("8\n");
		} else if (GPIOA1dPerR.Pins.pin4 != 0b1) {
			delay();
			printf("9\n");
		} else if (GPIOA1dPerR.Pins.pin6 != 0b1) {
			delay();
			printf("C\n");
		}
		*GPIOA_input = GPIOA1dPerR.binary_code;


		// 4th row
		GPIOA1dPerR.binary_code = *GPIOA_output;
		GPIOA1dPerR.Pins.pin5 = 0b1;
		GPIOA1dPerR.Pins.pin7 = 0b0;
		*GPIOA_output = GPIOA1dPerR.binary_code;

		GPIOA1dPerR.binary_code = *GPIOA_input;
		if (GPIOA1dPerR.Pins.pin0 != 0b1) {
			delay();
			printf("*\n");
		} else if (GPIOA1dPerR.Pins.pin2 != 0b1) {
			delay();
			printf("0\n");
		} else if (GPIOA1dPerR.Pins.pin4 != 0b1) {
			delay();
			printf("#\n");
		} else if (GPIOA1dPerR.Pins.pin6 != 0b1) {
			delay();
			printf("D\n");
		}
		*GPIOA_input = GPIOA1dPerR.binary_code;


	}
}
