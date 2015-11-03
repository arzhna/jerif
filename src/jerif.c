#include <stdio.h>
#include <string.h>

#include "jerif_types.h"
#include "jerif_stack.h"
#include "jerif.h"

jerif_bool is_seperator(char c)
{
    if(c == '{' || c == '}' || c == '"' || c == ':' || c == ','){
        return jerif_true;
    }
    else{
        return jerif_false;
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
        if(jerif_true == is_seperator(json_str[i])){
            err_code = jerif_stack_push(&stk, json_str[i]);
            if(err_code){
                break;
            }
        }
    }

    jerif_stack_dump(&stk);

    return err_code;
}
