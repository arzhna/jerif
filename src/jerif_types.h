#ifndef __TOAST_PFLAT_JERIF_TYPES_H__
#define __TOAST_PFLAT_JERIF_TYPES_H__

// error code
typedef unsigned int jerif_err;
#define jerif_ok    0
#define jerif_err_invalid_argument          1
#define jerif_err_stack_underflow           2
#define jerif_err_stack_overflow            3
#define jerif_err_stack_unsupported_char    4

// boolean
typedef unsigned int jerif_bool;
#define jerif_true  1
#define jerif_false 0


#endif //__TOAST_PFLAT_JERIF_TYPES_H__
