#ifndef __JERIF_TYPES_H__
#define __JERIF_TYPES_H__

// error code
typedef unsigned int jerif_err;
#define jerif_ok    0
#define jerif_err_invalid_json              1
#define jerif_err_invalid_argument          2
#define jerif_err_stack_underflow           3
#define jerif_err_stack_overflow            4
#define jerif_err_stack_unsupported_char    5

// boolean
typedef unsigned int jerif_bool;
#define jerif_true  1
#define jerif_false 0

#endif //__JERIF_TYPES_H__
