#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "scpi/scpi.h"

#include "hardware/uart.h"


#define UART_ID uart0
#define BAUD_RATE 115200

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1


// "IDN?" fields. Their meanings are "suggestions" in the standard.
#define SCPI_IDN1 "FirstTestStation"      /* Manufacturer */
#define SCPI_IDN2 "InterconnectIO"       /* Model */
#define SCPI_IDN3 "2022A"               /* no suggestion */
#define SCPI_IDN4 "0.1"                /* Firmware level */



// This will hold the SCPI "instance".
scpi_t scpi_context;

// Input buffer for reading SCPI commands.
#define SCPI_INPUT_BUFFER_SIZE 256
char scpi_input_buffer[SCPI_INPUT_BUFFER_SIZE];

// Error queue required by the library. Size taken from the docs.
#define SCPI_ERROR_QUEUE_SIZE 17
scpi_error_t scpi_error_queue[SCPI_ERROR_QUEUE_SIZE];


// The function called by the SCPI library when it wants to send data.
size_t write_scpi(scpi_t *context, const char *data, size_t len) {
	return fwrite(data, 1, len, stdout);
}

struct _scpi_channel_value_t {
    int32_t row;
    int32_t col;
};
typedef struct _scpi_channel_value_t scpi_channel_value_t;

/**
 * @brief
 * parses lists
 * channel numbers > 0.
 * no checks yet.
 * valid: (@1), (@3!1:1!3), ...
 * (@1!1:3!2) would be 1!1, 1!2, 2!1, 2!2, 3!1, 3!2.
 * (@3!1:1!3) would be 3!1, 3!2, 3!3, 2!1, 2!2, 2!3, ... 1!3.
 *
 * @param channel_list channel list, compare to SCPI99 Vol 1 Ch. 8.3.2
 */
static scpi_result_t Relay_Chanlst(scpi_t *context) {
    scpi_parameter_t channel_list_param;
#define MAXROW 1    /* maximum number of rows */
#define MAXCOL 10    /* maximum number of columns */
#define MAXDIM 1    /* maximum number of dimensions */
    scpi_channel_value_t array[MAXROW * MAXCOL]; /* array which holds values in order (2D) */
    size_t chanlst_idx; /* index for channel list */
    size_t arr_idx = 0; /* index for array */
    size_t n, m = 1; /* counters for row (n) and columns (m) */

    /* get channel list */
    if (SCPI_Parameter(context, &channel_list_param, TRUE)) {
        scpi_expr_result_t res;
        scpi_bool_t is_range;
        int32_t values_from[MAXDIM];
        int32_t values_to[MAXDIM];
        size_t dimensions;

        bool for_stop_row = FALSE; /* true if iteration for rows has to stop */
        bool for_stop_col = FALSE; /* true if iteration for columns has to stop */
        int32_t dir_row = 1; /* direction of counter for rows, +/-1 */
        int32_t dir_col = 1; /* direction of counter for columns, +/-1 */

        /* the next statement is valid usage and it gets only real number of dimensions for the first item (index 0) */
        if (!SCPI_ExprChannelListEntry(context, &channel_list_param, 0, &is_range, NULL, NULL, 0, &dimensions)) {
            chanlst_idx = 0; /* call first index */
            arr_idx = 0; /* set arr_idx to 0 */
            do { /* if valid, iterate over channel_list_param index while res == valid (do-while cause we have to do it once) */
                res = SCPI_ExprChannelListEntry(context, &channel_list_param, chanlst_idx, &is_range, values_from, values_to, 4, &dimensions);
                if (is_range == FALSE) { /* still can have multiple dimensions */
                    if (dimensions == 1) {
                        /* here we have our values
                         * row == values_from[0]
                         * col == 0 (fixed number)
                         * call a function or something */
                        array[arr_idx].row = values_from[0];
                        array[arr_idx].col = 0;
                    } else {
                        return SCPI_RES_ERR;
                    }
                    arr_idx++; /* inkrement array where we want to save our values to, not neccessary otherwise */
                    if (arr_idx >= MAXROW * MAXCOL) {
                        return SCPI_RES_ERR;
                    }
                } else if (is_range == TRUE) {
                    if (values_from[0] > values_to[0]) {
                        dir_row = -1; /* we have to decrement from values_from */
                    } else { /* if (values_from[0] < values_to[0]) */
                        dir_row = +1; /* default, we increment from values_from */
                    }

                    /* iterating over rows, do it once -> set for_stop_row = false
                     * needed if there is channel list index isn't at end yet */
                    for_stop_row = FALSE;
                    for (n = values_from[0]; for_stop_row == FALSE; n += dir_row) {
                      
                        if (dimensions == 1) {
                            /* here we have values
                             * row == n
                             * col == 0 (fixed number)
                             * call function or sth. */
                            array[arr_idx].row = n;
                            array[arr_idx].col = 0;
                            arr_idx++;
                            if (arr_idx >= MAXROW * MAXCOL) {
                                return SCPI_RES_ERR;
                            }
                        }
                        if (n == (size_t)values_to[0]) {
                            /* endpoint reached, stop row for-loop */
                            for_stop_row = TRUE;
                        }
                    }


                } else {
                    return SCPI_RES_ERR;
                }
                /* increase index */
                chanlst_idx++;
            } while (SCPI_EXPR_OK == SCPI_ExprChannelListEntry(context, &channel_list_param, chanlst_idx, &is_range, values_from, values_to, 4, &dimensions));
            /* while checks, whether incremented index is valid */
        }
        /* do something at the end if needed */
        /* array[arr_idx].row = 0; */
        /* array[arr_idx].col = 0; */
    }

    {
        size_t i;
        fprintf(stdout, "Channel List: ");
        for (i = 0; i< arr_idx; i++) {
            fprintf(stdout, "%d,", array[i].row);
            
        }
        fprintf(stdout, "\r\n");
    }
    return SCPI_RES_OK;
}
#define SCPI_EXCL "EXCL"

static scpi_result_t Relay_Chanlst2(scpi_t *context) {
    scpi_parameter_t channel_list_param;
    volatile scpi_bool_t ValMatch;
    int32_t Valtag, Vcomp;
    char cdat;

 fprintf(stdout,"tag test\r\n");

 fprintf(stdout,"raw: %s\r\n", context->param_list.cmd_raw.data);
  
  Valtag = SCPI_CmdTag(context);

  fprintf(stdout,"tagvalue: %d\r\n", Valtag);


  //ValMatch = SCPI_IsCmd(context,SCPI_EXCL);
 // fprintf(stdout,"ValMatch: %dn\r\n", ValMatch);

 // ValMatch = SCPI_Match( context->param_list.cmd_raw.data, "EXCL",15);
 // fprintf(stdout,"ValMatch: %dn\r\n", ValMatch);
 // Vcomp = strcmp( context->param_list.cmd_raw.data, "TATA");
 // fprintf(stdout,"Vcomp: %d\r\n", Vcomp);

    SCPI_ResultText(context, "termine avec succes");

    return SCPI_RES_OK;

}




// The SCPI commands we support and the callbacks they use.
scpi_command_t scpi_commands[] = {
	{ .pattern = "*IDN?", .callback = SCPI_CoreIdnQ, },
	{ .pattern = "*RST",  .callback = SCPI_CoreRst, },
    {.pattern = "ROUTe:CLOSE", .callback = Relay_Chanlst,1},
    {.pattern = "ROUTe:CLOSE[:EXCLusive]", .callback = Relay_Chanlst,2},
    {.pattern = "ROUTe:OPEN", .callback = Relay_Chanlst,3},
    {.pattern = "ROUTe:OPEN:ALL", .callback = Relay_Chanlst,4},
	SCPI_CMD_LIST_END
};

// Additional callbacks to be used by the library.
scpi_interface_t scpi_interface = {
	.write = write_scpi,
	.error = NULL,
	.reset = NULL,
};




int main() {
    int result;

	bi_decl(bi_program_description("This is a test binary, including the SCPI library."));

	stdio_init_all();


	// Initialize the SCPI library.
	SCPI_Init(
		&scpi_context, scpi_commands, &scpi_interface, scpi_units_def,
		SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
		scpi_input_buffer, SCPI_INPUT_BUFFER_SIZE,
		scpi_error_queue, SCPI_ERROR_QUEUE_SIZE
	);

// Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);
    stdout_uart_init();

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);


    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, "UART Connected!\n");
   

#define TEST_SCPI_INPUT(cmd)  result = SCPI_Input(&scpi_context, cmd, strlen(cmd))

   // TEST_SCPI_INPUT("TEST:CHANnellist (@1!2:3!4,5!6)\r\n");

    TEST_SCPI_INPUT("IDN?)\r\n"); 
    TEST_SCPI_INPUT("ROUT:CLOSE:EXCL (@120:125)\r\n"); 
    TEST_SCPI_INPUT("ROUT:CLOSE (@100:105)\r\n"); 

    
   // TEST_SCPI_INPUT("TEST:CHANnellist (@100:105)\r\n");
   // TEST_SCPI_INPUT("TEST:CHANnellist:EXCL (@120:125)\r\n");

	while (1) {
		// Feed single characters into the SCPI library.
		// This is somewhat discouraged, since (according to the docs) it will
		// apparently cause the whole buffer to be re-parsed after each character.
		char c = fgetc(stdin);  // TODO: Error handling.
		SCPI_Input(&scpi_context, &c, 1);
	}
	
    printf("program terminated\r");
}
