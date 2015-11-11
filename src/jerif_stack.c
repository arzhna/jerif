#include <stdio.h>
#include <string.h>

#include "jerif_stack.h"

#define MIN_ASCII_CHAR 33   // NULL~Space
#define MAX_ASCII_CHAR 126  // DEL~?

jerif_err jerif_stack_init(jerif_stack* s)
{
    if(s==NULL){
        return jerif_err_invalid_argument;
    }

    s->top = -1;
    memset(s->stk, 0, MAX_STACK_SIZE);

    return jerif_ok;
}

jerif_err jerif_stack_push(jerif_stack* s, char item)
{
    if(s==NULL){
        return jerif_err_invalid_argument;
    }

    if(item < MIN_ASCII_CHAR || item > MAX_ASCII_CHAR){
        return jerif_err_stack_unsupported_char;
    }

    if(s->top == (MAX_STACK_SIZE - 1)){
        return jerif_err_stack_overflow;
    }
    else{
        s->top = s->top + 1;
        s->stk[s->top] = item;
    }
    return jerif_ok;
}

jerif_err jerif_stack_pop(jerif_stack* s, char* item)
{
    if(s==NULL || item==NULL){
        return jerif_err_invalid_argument;
    }

    if (s->top == - 1){
        return jerif_err_stack_underflow;
    }
    else{
        *item = s->stk[s->top];
        s->top = s->top - 1;
    }
    return jerif_ok;
}

void jerif_stack_dump (jerif_stack* s)
{
    if(s==NULL){
        return;
    }

    if (s->top == -1){
        printf("stack is empty!\n");
    }
    else{
        int i;

        printf ("dump stack, top=%d\n", s->top);
        for (i = s->top; i >= 0; i--){
            printf ("│ %c │\n", s->stk[i]);
        }
        printf("└───┘\n\n");
    }
}
