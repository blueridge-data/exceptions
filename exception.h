#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define MAX_ERROR_HANDLERS   8

static jmp_buf error_handler_context[MAX_ERROR_HANDLERS];
static int error_handler_count = 0;

#define on_error()           if (setjmp(error_handler_context[error_handler_count++]))

void
nexterror(void)
{
    if (error_handler_count > 0)
    {
        error_handler_count--;
        longjmp(error_handler_context[error_handler_count], 1);
    }
}

void
error(char *err)
{
    if (error_handler_count == 0)
    {        
        printf("error(%s) not in a process\n", err);
        /* add ASSERT here */
        return;
    }
    
    if (error_handler_count > MAX_ERROR_HANDLERS)
    {      
        printf("error stack too deep\n");
        /* add ASSERT here */
        return;
    }

    printf("Error: %s\n", err);
    nexterror();
}

static inline void
poperror(void)
{
    error_handler_count--;
}

#endif /* EXCEPTION_HANDLER_H */
