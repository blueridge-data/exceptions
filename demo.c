#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include "exception.h"

int
throw_error(void)
{
    clock_t ticks = clock();
    
    return  (ticks % 2);
}

void
initialize_board(void)
{
    int rc;

    rc = 0;

    printf("\nBegin 'initialize_board' function\n");
    
    /* setup gpios, flash, etc */
    /* when rc not 0, throw error */

    printf("End 'initialized_board' function\n");
}

void run_process(void)
{
    printf("\nBegin 'run_process' function\n");

    /* Instantiate error handler */
    on_error()
    {
        printf("Error in 'process'\n");
        printf("Handling\n");
        if (throw_error())
        {
            printf("Unable to handle error, unwinding stack\n");
            nexterror();
        }
        goto Done;
    }

    if (throw_error())
    {        
        error("Error detected in process\n");
    }

    /* Remove error handler */
    poperror();

    Done:
    printf("End 'run_process' function\n");
}

int
main(int argc, char **argv)
{
    printf("\n-------------------------------------\n");
    printf("Exception handling demonstration in C\n");
    printf("-------------------------------------\n");

    /* Instantiate main error handler */
    on_error()
    {
        printf("\nError: ending 'main' module\n");
        printf("Complete with error 1\n");
        return 1;
    }

    /* Initialize board */
    initialize_board();

    /* Run app */
    run_process();

    /* Remove main error handler */
    poperror();

    printf("\nComplete\n");

    return 0;
}
