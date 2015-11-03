#include <stdio.h>

#include "jerif_stack.h"
#include "jerif.h"

#define DO_NOTHING()

char itoa(int n)
{
    if(n < 0 || n > 127){
        return -1;
    }

    return (char)(n+48);
}

int atoi(char c)
{
    if(c<48 || c>57){
        return -1;
    }

    return (int)(c-48);
}

int check_result(int condition){
    if(condition){
        printf("==> SUCCESS\n");
        return 1;
    }else{
        printf("==> FAILED\n");
        return 0;
    }
}

int stack_test(void){
    jerif_err err_code = jerif_ok;
    jerif_stack stk;
    int is_success=0;
    int i;

    int push_count = 10;
    int pop_count = 6;
    char element = 0;

    int test_case = 5;

    err_code = jerif_stack_init(&stk);
    if(err_code){
        printf("jerif_stack_init failed!\n");
        return -1;
    }

    // test case #1: input 10 elements. and then if the top of stack is 9, ok.
    printf("Test Case #1");
    for(i=0; i<push_count; i++){
        err_code = jerif_stack_push(&stk, itoa(i));
        if(err_code){
            printf("jerif_stack_push failed!\n");
            return -1;
        }
    }
    is_success = is_success + check_result(stk.top == (push_count-1));
    //jerif_stack_dump(&stk);

    // test case #2: pop 6 elements. and then if the top of stack is 3, ok.
    printf("Test Case #2");
    for(i=0; i<pop_count; i++){
        element = 0;
        err_code = jerif_stack_pop(&stk, &element);
        if(err_code){
            printf("jerif_stack_pop failed!\n");
            return -1;
        }
    }
    is_success = is_success + check_result(stk.top == ((push_count-pop_count)-1));
    //jerif_stack_dump(&stk);


    // test case #3: pop once. if it is ?, ok
    printf("Test Case #3");
    element = 0;
    err_code = jerif_stack_pop(&stk, &element);
    if(err_code){
        printf("jerif_stack_pop failed!\n");
        return -1;
    }
    is_success = is_success + check_result(atoi(element) == ((push_count-pop_count)-1));
    //printf("element=%d\n\n", atoi(element));
    //jerif_stack_dump(&stk);

    // test case #4: pop reamained elements, and then pop once more. if err_code is stack_underflow, ok.
    printf("Test Case #4");
    for(i=0; i<(push_count-pop_count-1); i++){
        element = 0;
        err_code = jerif_stack_pop(&stk, &element);
        if(err_code){
            printf("jerif_stack_pop failed!\n");
            return -1;
        }
    }

    err_code = jerif_stack_pop(&stk, &element);
    is_success = is_success + check_result(err_code==jerif_err_stack_underflow);
    //jerif_stack_dump(&stk);

    // test case #4: push max, and then push once more. if err_code is stack_overflow, ok.
    printf("Test Case #5");
    for(i=0; i<MAX_STACK_SIZE; i++){
        err_code = jerif_stack_push(&stk, (char)(i+48));
        if(err_code){
            printf("jerif_stack_push failed!\n");
            return -1;
        }
    }

    err_code = jerif_stack_push(&stk, '1');
    is_success = is_success + check_result(err_code==jerif_err_stack_overflow);
    //jerif_stack_dump(&stk);

    if(is_success >= test_case){
        return 0;
    }else{
        return -1;
    }
}

#define TEST_CASE_JSON_STR_01 "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1}"
#define TEST_CASE_JSON_STR_02 "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1"
#define TEST_CASE_JSON_STR_03 "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890, \"no\":1}"
#define TEST_CASE_JSON_STR_04 "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":123-456-7890\", \"no\":1}"
#define TEST_CASE_JSON_STR_05 "\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1}"
#define TEST_CASE_JSON_STR_06 "\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1, }"

int main (void)
{
    printf("[STACK TEST]\n");
    if(stack_test()){
        printf("Stack test is FAILED!!!\n\n");
    }else{
        printf("Stack test is SUCCESS!!!\n\n");
    }

    jerif_check_json_validation(TEST_CASE_JSON_STR_01);

    return 0;
}
