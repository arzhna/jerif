#include <stdio.h>
#include <string.h>

#include "jerif_rsc.h"
#include "jerif_check.h"

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

    if(((qoute_count%2)!=0) || (brace_toggle!=0)){
        //printf("qoute_count: %d, brace_toggle: %d, bracket_toggle=%d\n", qoute_count, brace_toggle, bracket_toggle);
        return jerif_false;
    }else{
        return jerif_true;
    }
}

jerif_bool is_valid_item(char prev, char item)
{
    jerif_bool result = jerif_true;

    switch(prev){
        case SYMBOL_NULL:
            if(item!=SYMBOL_BRACE_CLOSE){
                result = jerif_false;
            }
            break;
        case SYMBOL_BRACE_CLOSE:
            if( item!=SYMBOL_BRACKET_CLOSE &&
                item!=SYMBOL_DOUBLE_QOUTE &&
                item!=SYMBOL_COLON &&
                item!=SYMBOL_DATA){
                result = jerif_false;
            }
            break;
        case SYMBOL_BRACE_OPEN:
            if( item!=SYMBOL_BRACKET_OPEN &&
                item!=SYMBOL_COMMA){
                result = jerif_false;
            }
            break;
        case SYMBOL_BRACKET_CLOSE:
            if( item!=SYMBOL_BRACE_CLOSE &&
                item!=SYMBOL_BRACKET_OPEN &&
                item!=SYMBOL_DOUBLE_QOUTE &&
                item!=SYMBOL_COLON &&
                item!=SYMBOL_COMMA &&
                item!=SYMBOL_DATA){
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
                item!=SYMBOL_DATA){
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
                item!=SYMBOL_DATA){
                result = jerif_false;
            }
            break;
        case SYMBOL_DATA:
            if( item!=SYMBOL_BRACKET_OPEN &&
                item!=SYMBOL_DOUBLE_QOUTE &&
                item!=SYMBOL_COLON &&
                item!=SYMBOL_COMMA ){
                result = jerif_false;
            }
            break;
        default:
            ;
    }

    return result;
}

jerif_bool is_valid_syntax(jerif_stack *stk, char prev_item)
{
    jerif_err err_code = jerif_ok;
    char item = 0;

    err_code = jerif_stack_pop(stk, &item);
    if(err_code){
        if(err_code==jerif_err_stack_underflow && prev_item == SYMBOL_BRACE_OPEN){
            return jerif_true; //jerif_ok;
        }else{
            return jerif_false;
        }
    }

    //printf("%c %c\n", item, prev_item);
    if(is_valid_item(prev_item, item) == jerif_false){
        return jerif_false;
    }
    else{
        return is_valid_syntax(stk, item);
    }
}

jerif_err jerif_check_syntax(jerif_stack *stk)
{
    jerif_err err_code = jerif_ok;

    //jerif_stack_dump(&stk);
    if(jerif_false == is_pair(stk) || jerif_false == is_valid_syntax(stk, 0)){
        err_code = jerif_err_invalid_json;
    }

    return err_code;
}

jerif_bool jerif_check_syntatic_symbol(char c)
{
    if( c == SYMBOL_BRACE_OPEN || c == SYMBOL_BRACE_CLOSE ||
        c == SYMBOL_BRACKET_OPEN || c == SYMBOL_BRACKET_CLOSE ||
        c == SYMBOL_DOUBLE_QOUTE || c == SYMBOL_COLON ||
        c == SYMBOL_COMMA){
        return jerif_true;
    }
    else{
        return jerif_false;
    }
}
