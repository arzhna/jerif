#ifndef __JERIF_STACK_H__
#define __JERIF_STACK_H__

#include "jerif_types.h"

#define MAX_STACK_SIZE 1024
typedef struct {
    char stk[MAX_STACK_SIZE];
    int top;
} jerif_stack;

jerif_err jerif_stack_init(jerif_stack* s);
jerif_err jerif_stack_push(jerif_stack* s, char item);
jerif_err jerif_stack_pop(jerif_stack* s, char* item);

void jerif_stack_dump (jerif_stack* s);

#endif //__JERIF_STACK_H__
