#include <stdio.h>
#include <string.h>

#include "jerif_check.h"
#include "jerif_rsc.h"
#include "jerif.h"



jerif_err jerif_check_validation(const char* json_str)
{
    jerif_err err_code = jerif_ok;
    jerif_stack stk;
    jerif_bool data_toggle=jerif_false;
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
        if(jerif_check_syntatic_symbol(json_str[i])){
            if(data_toggle){
                data_toggle = jerif_false;
            }
            err_code = jerif_stack_push(&stk, json_str[i]);
            if(err_code){
                break;
            }
        }else if(json_str[i]!=SYMBOL_SPACE){
            if(data_toggle == jerif_false){
                err_code = jerif_stack_push(&stk, SYMBOL_DATA);
                if(err_code){
                    break;
                }
                data_toggle = jerif_true;
            }
        }
    }

    return jerif_check_syntax(&stk);
}