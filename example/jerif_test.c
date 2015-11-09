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
        printf("  ==> SUCCESS\n");
        return 1;
    }else{
        printf("  ==> FAILED\n");
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
        printf("jerif_stack_init failed!, err_code=%d\n", err_code);
        return -1;
    }

    // test case #1: input 10 elements. and then if the top of stack is 9, ok.
    printf("Test Case #1\n");
    for(i=0; i<push_count; i++){
        err_code = jerif_stack_push(&stk, itoa(i));
        if(err_code){
            printf("jerif_stack_push failed!, err_code=%d\n", err_code);
            return -1;
        }
    }
    is_success = is_success + check_result(stk.top == (push_count-1));
    //jerif_stack_dump(&stk);

    // test case #2: pop 6 elements. and then if the top of stack is 3, ok.
    printf("Test Case #2\n");
    for(i=0; i<pop_count; i++){
        element = 0;
        err_code = jerif_stack_pop(&stk, &element);
        if(err_code){
            printf("jerif_stack_pop failed!, err_code=%d\n", err_code);
            return -1;
        }
    }
    is_success = is_success + check_result(stk.top == ((push_count-pop_count)-1));
    //jerif_stack_dump(&stk);


    // test case #3: pop once. if it is ?, ok
    printf("Test Case #3\n");
    element = 0;
    err_code = jerif_stack_pop(&stk, &element);
    if(err_code){
        printf("jerif_stack_pop failed!, err_code=%d\n", err_code);
        return -1;
    }
    is_success = is_success + check_result(atoi(element) == ((push_count-pop_count)-1));
    //printf("element=%d\n\n", atoi(element));
    //jerif_stack_dump(&stk);

    // test case #4: pop reamained elements, and then pop once more. if err_code is stack_underflow, ok.
    printf("Test Case #4\n");
    for(i=0; i<(push_count-pop_count-1); i++){
        element = 0;
        err_code = jerif_stack_pop(&stk, &element);
        if(err_code){
            printf("jerif_stack_pop failed!, err_code=%d\n", err_code);
            return -1;
        }
    }

    err_code = jerif_stack_pop(&stk, &element);
    is_success = is_success + check_result(err_code==jerif_err_stack_underflow);
    //jerif_stack_dump(&stk);

    // test case #5: push max, and then push once more. if err_code is stack_overflow, ok.
    printf("Test Case #5\n");
    for(i=0; i<MAX_STACK_SIZE; i++){
        err_code = jerif_stack_push(&stk, (char)((i&0x0F)+48));
        if(err_code){
            printf("jerif_stack_push failed!, err_code=%d\n", err_code);
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

#define VALIDATOR_TEST_CASE_COUNT 11
char *TEST_CASE_JSON_STR[] = {
    "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1, \"valid\":true}",
    "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1, \"valid\":true",
    "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890, \"no\":1, \"valid\":true}",
    "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":123-456-7890\", \"no\":1, \"valid\":true}",
    "\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1, \"valid\":true}",
    "\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1 \"valid\":true,}",
    "\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1, \"valid\":true",
    "\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":1, {\"valid\":true}",
    "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":[\"123-456-7890\", \"234-567-8901\"], \"no\":1, \"valid\":true}",
    "{\"name\":\"arzhna\", \"address\":\"seoul\", \"tel\":\"123-456-7890\", \"no\":[1, 2], \"valid\":true}",
    "{\"name\": \"arzhna\", \"address\": \"seoul\", \"tel\": [\"123-456-7890\", \"123-456-7890\"], \"no\": [1, 2], \"group\": [{\"name\": \"pflat-dev\", \"no\": 1}, {\"name\": \"dev\", \"no\": 2}], \"valid\": true}",
};
jerif_err TEST_CASE_RESULT[] = {
    jerif_ok,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_ok,
    jerif_ok,
    jerif_ok,
};

int validator_test(void)
{
    int i=0;
    int test_case = VALIDATOR_TEST_CASE_COUNT;
    int success_count=0;
    jerif_err err_code = jerif_ok;

    for(i=0; i<test_case; i++){
        printf("Test Case #%d\n", i+1);
        err_code = jerif_check_json_validation(TEST_CASE_JSON_STR[i]);
        success_count += check_result(err_code==TEST_CASE_RESULT[i]);
    }

    printf("%d\n",success_count);

    if(success_count >= test_case){
        return 0;
    }else{
        return -1;
    }
}

int main (void)
{
    jerif_err err_code = jerif_ok;

    printf("[STACK TEST]\n");
    if(stack_test()){
        printf("Stack test is FAILED!!!\n\n");
    }else{
        printf("Stack test is SUCCESS!!!\n\n");
    }

    printf("[VALIDATOR TEST]\n");
    if(validator_test()){
        printf("Validator test is FAILED!!!\n\n");
    }else{
        printf("Validator test is SUCCESS!!!\n\n");
    }

    return 0;
}
