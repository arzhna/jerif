#ifndef __JERIF_DETECT_H__
#define __JERIF_DETECT_H__

#include "jerif_types.h"

jerif_bool jerif_detect_boolean(const char* str);
jerif_bool jerif_detect_integer(const char* str);
jerif_bool jerif_detect_float(const char* str);
jerif_bool jerif_detect_string(const char* str);

#endif //__JERIF_DETECT_H__
