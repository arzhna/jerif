#include <stdio.h>
#include <string.h>

#include "jerif_types.h"
#include "jerif_stack.h"
#include "jerif.h"

jerif_bool is_syntatic_symbol(char c)
{
    if(c == '{' || c == '}' || c == '[' || c == ']' || c == '"' || c == ':' || c == ','){
        return jerif_true;
    }
    else{
        return jerif_false;
    }
}

jerif_bool is_pair(jerif_stack *s)
{
    int i;
    int qoute_count=0;
    int brace_toggle=0;
    int bracket_toggle=0;

    for(i=0; i<MAX_STACK_SIZE; i++){
        if(s->stk[i] == '"'){
            qoute_count++;
        }else if(s->stk[i]=='{'){
            brace_toggle++;
        }else if(s->stk[i]=='}'){
            brace_toggle--;
        }else if(s->stk[i]=='['){
            bracket_toggle++;
        }else if(s->stk[i]==']'){
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

jerif_err check_json_syntax(jerif_stack *stk, char prev_item)
{
    jerif_err err_code = jerif_ok;
    char item = 0;

    err_code = jerif_stack_pop(stk, &item);
    if(err_code){
        if(err_code==jerif_err_stack_underflow && prev_item == '{'){
            return jerif_ok;
        }else{
            return jerif_err_invalid_json;
        }
    }

    //printf("prev: %c, item %c\n", ((prev_item==0)?'0':prev_item), item);

    if(prev_item==0 && item!='}'){
        return jerif_err_invalid_json;
    }
    else if(prev_item=='}' && (item!=':' && item!='"' && item!=']')){
        return jerif_err_invalid_json;
    }
    else if(prev_item=='{' && (item!=',' && item!='[')){
        return jerif_err_invalid_json;
    }
    else if(prev_item==']' && (item!='"' && item!=':' && item!=',' && item!='}' && item!='[')){
        return jerif_err_invalid_json;
    }
    else if(prev_item=='[' && (item!=':')){
        return jerif_err_invalid_json;
    }
    else if(prev_item==':' && item!='"'){
        return jerif_err_invalid_json;
    }
    else if(prev_item==',' && (item!='"' && item!=':' && item!='[' && item!=']' && item!='{' && item!='}')){
        return jerif_err_invalid_json;
    }
    else if(prev_item=='"' && (item!='"' && item!=',' && item!='[' && item!='{' && item!=':')){
        return jerif_err_invalid_json;
    }
    else{
        return check_json_syntax(stk, item);
    }
}

jerif_err jerif_check_json_validation(const char* json_str)
{
    jerif_err err_code = jerif_ok;
    jerif_stack stk;
    int i;

    if(json_str==NULL){
        return jerif_err_invalid_argument;
    }

    err_code = jerif_stack_init(&stk);
    if(err_code){
        printf("jerif_stack_init failed!\n");
        return -1;
    }

    // TODO: implement to check validation
    for(i=0; i<(int)strlen(json_str); i++){
        if(jerif_true == is_syntatic_symbol(json_str[i])){
            err_code = jerif_stack_push(&stk, json_str[i]);
            if(err_code){
                break;
            }
        }
    }

    //jerif_stack_dump(&stk);

    if(jerif_false == is_pair(&stk)){
        err_code = jerif_err_invalid_json;
    }else{
        err_code = check_json_syntax(&stk, 0);
    }

    return err_code;
}
