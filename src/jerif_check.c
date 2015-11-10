#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "jerif_rsc.h"
#include "jerif_stack.h"
#include "jerif_check.h"

#define DEBUG_PRINT_ENABLE  0

jerif_bool is_pair(jerif_stack *s)
{
    int i;
    int qoute_count=0;
    int brace_toggle=0;
    int bracket_toggle=0;

    for(i=0; i<MAX_STACK_SIZE; i++){
        if(s->stk[i] == SYMBOL_DOUBLE_QOUTE){
            qoute_count++;
        }else if(s->stk[i]==SYMBOL_BRACE_OPEN){
            brace_toggle++;
        }else if(s->stk[i]==SYMBOL_BRACE_CLOSE){
            brace_toggle--;
        }else if(s->stk[i]==SYMBOL_BRACKET_OPEN){
            bracket_toggle++;
        }else if(s->stk[i]==SYMBOL_BRACKET_CLOSE){
            bracket_toggle--;
        }
    }

    if(((qoute_count%2)!=0) || (brace_toggle!=0) || (bracket_toggle!=0)){
#if DEBUG_PRINT_ENABLE
        //printf("qoute_count: %d, brace_toggle: %d, bracket_toggle=%d\n", qoute_count, brace_toggle, bracket_toggle);
#endif
        return jerif_false;
    }else{
        return jerif_true;
    }
}

jerif_bool is_valid_item(char prev, char item, jerif_bool in_bracket)
{
    jerif_bool result = jerif_true;

#if DEBUG_PRINT_ENABLE
    //printf("%c %c (%d)\n", item, prev, in_bracket);
#endif
    switch(prev){
        case SYMBOL_NULL:
            if(item!=SYMBOL_BRACE_CLOSE){
                result = jerif_false;
            }
            break;
        case SYMBOL_BRACE_CLOSE:
            if( item!=SYMBOL_BRACE_OPEN &&
                item!=SYMBOL_BRACE_CLOSE &&
                item!=SYMBOL_BRACKET_CLOSE &&
                item!=SYMBOL_DOUBLE_QOUTE &&
                item!=SYMBOL_COLON &&
                item!=SYMBOL_DATA_STRING &&
                item!=SYMBOL_DATA_INTEGER &&
                item!=SYMBOL_DATA_BOOLEAN){
                result = jerif_false;
            }
            break;
        case SYMBOL_BRACE_OPEN:
            if( item!=SYMBOL_BRACKET_OPEN &&
                item!=SYMBOL_COLON &&
                item!=SYMBOL_COMMA){
                result = jerif_false;
            }
            break;
        case SYMBOL_BRACKET_CLOSE:
            if( item!=SYMBOL_BRACE_CLOSE &&
                item!=SYMBOL_BRACKET_CLOSE &&
                item!=SYMBOL_BRACKET_OPEN &&
                item!=SYMBOL_DOUBLE_QOUTE &&
                item!=SYMBOL_COLON &&
                item!=SYMBOL_COMMA &&
                item!=SYMBOL_DATA_STRING &&
                item!=SYMBOL_DATA_INTEGER &&
                item!=SYMBOL_DATA_BOOLEAN){
                result = jerif_false;
            }
            break;
        case SYMBOL_BRACKET_OPEN:
            if(item!=SYMBOL_COLON){
                result = jerif_false;
            }
            break;
        case SYMBOL_DOUBLE_QOUTE:
            if( item!=SYMBOL_BRACKET_OPEN &&
                item!=SYMBOL_BRACE_OPEN &&
                item!=SYMBOL_DOUBLE_QOUTE &&
                item!=SYMBOL_COLON &&
                item!=SYMBOL_COMMA &&
                item!=SYMBOL_DATA_STRING){
                result = jerif_false;
            }
            break;
        case SYMBOL_COLON:
            if(item!=SYMBOL_DOUBLE_QOUTE){
                result = jerif_false;
            }
            break;
        case SYMBOL_COMMA:
            if( item!=SYMBOL_BRACKET_OPEN &&
                item!=SYMBOL_BRACKET_CLOSE &&
                item!=SYMBOL_BRACE_OPEN &&
                item!=SYMBOL_BRACE_CLOSE &&
                item!=SYMBOL_DOUBLE_QOUTE &&
                item!=SYMBOL_DATA_STRING &&
                item!=SYMBOL_DATA_INTEGER &&
                item!=SYMBOL_DATA_BOOLEAN){
                result = jerif_false;
            }
            break;
        case SYMBOL_DATA_STRING:
            if( item!=SYMBOL_DOUBLE_QOUTE ){
                result = jerif_false;
            }
            break;
        case SYMBOL_DATA_INTEGER:
        case SYMBOL_DATA_BOOLEAN:
            if(in_bracket){
                if( item!=SYMBOL_BRACKET_OPEN &&
                    item!=SYMBOL_COLON &&
                    item!=SYMBOL_COMMA ){
                    result = jerif_false;
                }
            }else{
                if( item!=SYMBOL_COLON ){
                    result = jerif_false;
                }
            }
            break;
        default:
            result = jerif_true;
    }

    return result;
}

jerif_bool is_valid_syntax(jerif_stack *s, char prev_item, jerif_bool in_bracket)
{
    jerif_err err_code = jerif_ok;
    char item = 0;

    err_code = jerif_stack_pop(s, &item);
    if(err_code){
        if(err_code==jerif_err_stack_underflow && prev_item == SYMBOL_BRACE_OPEN){
            return jerif_true; //jerif_ok;
        }else{
            return jerif_false;
        }
    }

#if DEBUG_PRINT_ENABLE
    printf("[%d] %c %c\n", s->top, item, prev_item);
#endif
    if(prev_item == SYMBOL_BRACKET_CLOSE){
        in_bracket = jerif_true;
    }else if(prev_item == SYMBOL_BRACKET_OPEN){
        in_bracket = jerif_false;
    }

    if(is_valid_item(prev_item, item, in_bracket) == jerif_false){
        return jerif_false;
    }
    else{
        return is_valid_syntax(s, item, in_bracket);
    }
}

jerif_err check_syntax(jerif_stack *s)
{
    jerif_err err_code = jerif_ok;

#if DEBUG_PRINT_ENABLE
    jerif_stack_dump(s);
#endif
    if( (jerif_false == is_pair(s)) ||
        (jerif_false == is_valid_syntax(s, 0, jerif_false))){
        err_code = jerif_err_invalid_json;
    }

    return err_code;
}

jerif_bool is_syntatic_symbol(char c)
{
    if( c == SYMBOL_BRACE_OPEN || c == SYMBOL_BRACE_CLOSE ||
        c == SYMBOL_BRACKET_OPEN || c == SYMBOL_BRACKET_CLOSE ||
        c == SYMBOL_DOUBLE_QOUTE || c == SYMBOL_COLON ||
        c == SYMBOL_COMMA ){
        return jerif_true;
    }
    else{
        return jerif_false;
    }
}

jerif_bool is_space_symbol(char c)
{
    if( c <= SYMBOL_SPACE ){
        return jerif_true;
    }
    else{
        return jerif_false;
    }
}

jerif_bool is_boolean(const char* str)
{
    int status;
    regex_t state;
    const char *pattern = REGEX_PATTERN_BOOLEAN;

    if (regcomp(&state, pattern, REG_EXTENDED)){
        return jerif_false;
    }

    status = regexec(&state, str, 0, NULL, 0);
#if DEBUG_PRINT_ENABLE
    printf("[%s] %s: %s\n", __FUNCTION__, str, status == 0 ? "match" : "no match");
#endif
    if(status){
        return jerif_false;
    }

    return jerif_true;
}

jerif_bool is_integer(const char* str)
{
    int status;
    regex_t state;
    const char *pattern = REGEX_PATTERN_INTEGER;

    if (regcomp(&state, pattern, REG_EXTENDED)){
        return jerif_false;
    }

    status = regexec(&state, str, 0, NULL, 0);
#if DEBUG_PRINT_ENABLE
    printf("[%s] %s: %s(%d)\n", __FUNCTION__, str, status == 0 ? "match" : "no match", status);
#endif
    if(status){
        return jerif_false;
    }

    return jerif_true;
}

jerif_bool is_float(const char* str)
{
    int status;
    regex_t state;
    const char *pattern = REGEX_PATTERN_FLOAT;

    if (regcomp(&state, pattern, REG_EXTENDED)){
        return jerif_false;
    }

    status = regexec(&state, str, 0, NULL, 0);
#if DEBUG_PRINT_ENABLE
    printf("[%s] %s: %s(%d)\n", __FUNCTION__, str, status == 0 ? "match" : "no match", status);
#endif
    if(status){
        return jerif_false;
    }

    return jerif_true;
}

jerif_err jerif_check_validation(const char* json_str)
{
    jerif_err err_code = jerif_ok;
    jerif_stack s;
    jerif_bool data_toggle=jerif_false;
    int i;

    if(json_str==NULL){
        return jerif_err_invalid_argument;
    }

    err_code = jerif_stack_init(&s);
    if(err_code){
        printf("jerif_stack_init failed!\n");
        return -1;
    }

    // TODO: implement to check validation
    for(i=0; i<(int)strlen(json_str); i++){
        if(is_syntatic_symbol(json_str[i])){
            if(data_toggle){
                data_toggle = jerif_false;
            }
            err_code = jerif_stack_push(&s, json_str[i]);
            if(err_code){
                break;
            }
        }else if(jerif_false == is_space_symbol(json_str[i])){
            char symbol = SYMBOL_DATA_STRING;
            if(data_toggle == jerif_false){
                // check boolean
                if(s.stk[s.top] != SYMBOL_DOUBLE_QOUTE){
                    if(json_str[i] == SYMBOL_DATA_BOOL_TRUE || json_str[i] == SYMBOL_DATA_BOOL_FALSE){
                        if(is_boolean(&(json_str[i]))){
                            symbol = SYMBOL_DATA_BOOLEAN;
                        }
                    }
                    // check integer
                    else if(is_integer(&(json_str[i]))){
                        symbol = SYMBOL_DATA_INTEGER;
                    }
                    // check float
                    else if(is_float(&(json_str[i]))){
                        symbol = SYMBOL_DATA_INTEGER;
                    }
#if DEBUG_PRINT_ENABLE
                    else {
                        printf("[%s] no push: %d\n", __FUNCTION__, json_str[i]);
                    }
#endif
                }

                err_code = jerif_stack_push(&s, symbol);
                if(err_code){
                    break;
                }
                data_toggle = jerif_true;
            }
        }
#if DEBUG_PRINT_ENABLE
        else{
            printf("[%s] no push: %d\n", __FUNCTION__, json_str[i]);
        }
#endif
    }

    return check_syntax(&s);
}
