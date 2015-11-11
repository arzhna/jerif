#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "jerif_rsc.h"
#include "jerif_detect.h"

#define DEBUG_PRINT_ENABLE 0

jerif_bool detect_pattern(const char* pattern, const char* str, const char* func)
{
    int status;
    regex_t state;

    if (regcomp(&state, pattern, REG_EXTENDED)){
        return jerif_false;
    }

    status = regexec(&state, str, 0, NULL, 0);
#if DEBUG_PRINT_ENABLE
    printf("[%s] %s : %s\n", func, str, status == 0 ? "match" : "no match");
#else
    (void)func;
#endif
    if(status){
        return jerif_false;
    }

    return jerif_true;
}

jerif_bool jerif_detect_boolean(const char* str)
{
    return detect_pattern(REGEX_PATTERN_BOOLEAN, str, __FUNCTION__);
}

jerif_bool jerif_detect_integer(const char* str)
{
    return detect_pattern(REGEX_PATTERN_INTEGER, str, __FUNCTION__);
}

jerif_bool jerif_detect_float(const char* str)
{
    return detect_pattern(REGEX_PATTERN_FLOAT, str, __FUNCTION__);
}

jerif_bool jerif_detect_string(const char* str)
{
    return detect_pattern(REGEX_PATTERN_STRING, str, __FUNCTION__);
}
