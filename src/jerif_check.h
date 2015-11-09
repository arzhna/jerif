#ifndef __JERIF_CHECK_H__
#define __JERIF_CHECK_H__

#include "jerif_types.h"
#include "jerif_stack.h"

jerif_err jerif_check_syntax(jerif_stack *stk);
jerif_bool jerif_check_syntatic_symbol(char c);

#endif //__JERIF_CHECK_H__
