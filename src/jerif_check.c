#include <stdio.h>
#include <string.h>

#include "jerif_rsc.h"
#include "jerif_stack.h"
#include "jerif_detect.h"
#include "jerif_check.h"

#define DEBUG_PRINT_ENABLE  0

jerif_bool is_pair(jerif_stack *s)
{
    int i;
    int qoute_count=0;
    int brace_toggle=0;
    int bracket_toggle=0;

    for(i=0; i<MAX_STACK_SIZE; i++){
        if(s->stk[i]== SYMBOL_DOUBLE_QOUTE){
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
        printf("qoute_count: %d, brace_toggle: %d, bracket_toggle=%d\n", qoute_count, brace_toggle, bracket_toggle);
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
    printf("%c %c (%d)\n", item, prev, in_bracket);
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

jerif_bool is_syntactic_symbol(char c)
{
    if( SYMBOL_BRACE_OPEN == c || SYMBOL_BRACE_CLOSE == c ||
        SYMBOL_BRACKET_OPEN == c || SYMBOL_BRACKET_CLOSE == c ||
        SYMBOL_DOUBLE_QOUTE == c || SYMBOL_COLON == c ||
        SYMBOL_COMMA == c ){
        return jerif_true;
    }
    else{
        return jerif_false;
    }
}

jerif_bool is_double_qoute(char c)
{
    if(SYMBOL_DOUBLE_QOUTE == c){
        return jerif_true;
    }
    else{
        return jerif_false;
    }
}

jerif_bool is_space_symbol(char c)
{
    if( SYMBOL_SPACE >= c ){
        return jerif_true;
    }
    else{
        return jerif_false;
    }
}

jerif_err tokenize(jerif_stack* s, const char* json_str)
{
    jerif_err err_code = jerif_ok;
    jerif_bool data_flag = jerif_false;
    jerif_bool qoute_open_flag = jerif_false;
    int str_length = (int)strlen(json_str);
    int i;

    // tokenize and push in stack
    for(i=0; i<str_length; i++){
#if DEBUG_PRINT_ENABLE
        printf("%c\n", json_str[i]);
#endif
        if(is_syntactic_symbol(json_str[i]) && !qoute_open_flag){
            if(data_flag){
                data_flag = jerif_false;
#if DEBUG_PRINT_ENABLE
                printf("bool or decimal data end\n");
#endif
            }

            if(SYMBOL_DOUBLE_QOUTE==json_str[i] && !qoute_open_flag){
                qoute_open_flag = jerif_true;
#if DEBUG_PRINT_ENABLE
                printf("qoute opened\n");
#endif
            }

            err_code = jerif_stack_push(s, json_str[i]);
            if(err_code){
                return err_code;
            }
        }
        else if(!is_space_symbol(json_str[i])){
            if(!data_flag){
                if(s->stk[s->top] != SYMBOL_DOUBLE_QOUTE){
                    char symbol = SYMBOL_DATA_OTHER;
                    // check boolean
                    if(jerif_detect_boolean(&(json_str[i]))){
                        symbol = SYMBOL_DATA_BOOLEAN;
                    }
                    // check integer
                    else if(jerif_detect_integer(&(json_str[i]))){
                        symbol = SYMBOL_DATA_INTEGER;
                    }
                    // check float
                    else if(jerif_detect_float(&(json_str[i]))){
                        symbol = SYMBOL_DATA_INTEGER;
                    }
#if DEBUG_PRINT_ENABLE
                    else {
                        printf("[%s(%d)] no push: %d\n", __FUNCTION__, __LINE__, json_str[i]);
                    }
#endif
                    if(SYMBOL_DATA_OTHER != symbol){
                        err_code = jerif_stack_push(s, symbol);
                        if(err_code){
                            return err_code;
                        }
                    }
                    data_flag = jerif_true;
#if DEBUG_PRINT_ENABLE
                    printf("bool or decimal data start\n");
#endif
                }
                else{
                    // check string
                    if(jerif_detect_string(&(json_str[i]))){
                        char *loc;

                        err_code = jerif_stack_push(s, SYMBOL_DATA_STRING);
                        if(err_code){
                            return err_code;
                        }
                        err_code = jerif_stack_push(s, SYMBOL_DOUBLE_QOUTE);
                        if(err_code){
                            return err_code;
                        }

                        // move pointer location to next qoute
                        loc = strchr(&json_str[i], SYMBOL_DOUBLE_QOUTE);
                        i += loc - &json_str[i];

                        qoute_open_flag = jerif_false;
#if DEBUG_PRINT_ENABLE
                        printf("qoute closed\n");
#endif
                    }
                }
            }
        }
#if DEBUG_PRINT_ENABLE
        else{
            printf("[%s(%d)] no push: %d\n", __FUNCTION__, __LINE__, json_str[i]);
        }
#endif
    }

    return jerif_ok;
}

jerif_err jerif_check_validation(const char* json_str)
{
    jerif_err err_code = jerif_ok;
    jerif_stack s;

    if(json_str==NULL){
        return jerif_err_invalid_argument;
    }

    err_code = jerif_stack_init(&s);
    if(err_code){
        printf("jerif_stack_init failed!\n");
        return err_code;
    }

    err_code = tokenize(&s, json_str);
    if(err_code){
        printf("json-tokenizing failed\n");
        return err_code;
    }

    return check_syntax(&s);
}
