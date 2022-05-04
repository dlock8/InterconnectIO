#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "scpi/scpi.h"

#include "hardware/uart.h"
#include "include/fts_scpi.h"
#include "include/master.h"







int main() {
    int result;

	bi_decl(bi_program_description("This is a test binary, including the SCPI library."));

	stdio_init_all();
    init_scpi();



// Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);
  //  stdout_uart_init();
  //  stdio_usb_init();

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);


    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, "UART Connected!\n");
    printf("USB CONNECTED \r\n");

    #define LED_PIN 16
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
   

#define TEST_SCPI_INPUT(cmd)  result = SCPI_Input(&scpi_context, cmd, strlen(cmd))

   // TEST_SCPI_INPUT("TEST:CHANnellist (@1!2:3!4,5!6)\r\n");


    TEST_SCPI_INPUT("*IDN?\r\n"); 
    TEST_SCPI_INPUT("ROUT:CLOSE:EXCL (@120:125)\r\n"); 
    TEST_SCPI_INPUT("ROUT:CLOSE (@100:105)\r\n"); 
    

    
   // TEST_SCPI_INPUT("TEST:CHANnellist (@100:105)\r\n");
   // TEST_SCPI_INPUT("TEST:CHANnellist:EXCL (@120:125)\r\n");

	while (1) {
        printf("Hello, world!\n");
        uart_puts(UART_ID, "Hello UART!\n");
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);

		// Feed single characters into the SCPI library.
		// This is somewhat discouraged, since (according to the docs) it will
		// apparently cause the whole buffer to be re-parsed after each character.
		//* char c = fgetc(stdin);  // TODO: Error handling.
		//*SCPI_Input(&scpi_context, &c, 1);
	}
	
    printf("program terminated\r");
}
