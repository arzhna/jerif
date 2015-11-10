#include <stdio.h>

#include "jerif_stack.h"
#include "jerif_check.h"

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

#define VALIDATOR_TEST_CASE_COUNT  14    //10
char *TEST_CASE_JSON_STR[] = {
    // valid cases, 7
    "{\"string\":\"100 strings\", \"int\":0.1, \"bool\":false }",
    "{\"string\":\"string\", \"int\":1029384756, \"group\":{\"string\":\"string\", \"int\":88}, \"bool\":true}",
    "{\"string\":\"string\", \"int\":1029384756, \"array\":[11, 22, 33], \"bool\":true}",
    "{\"string\":\"string\", \"int\":1029384756, \"array\":[false, true, true], \"bool\":true}",
    "{\"string\":\"string\", \"int\":1029384756, \"array\":[\"abc\", \"def\", \"ghi\"], \"bool\":true}",
    "{\"string\":\"string\", \"int\":1029384756, \"array\":[\"string1\", \"string2\", \"string3\"], \"bool\":true}",
    "{\"string\":\"string\", \"int\":1029384756, \"array\":[{\"int\":55, \"string\":\"string\"}, {\"int\":66, \"string\":\"string\"}, {\"int\":77, \"string\":\"string\"}], \"bool\":true}",

    // invalid cases, 5
    "{\"string\":\"string\", \"int\":1, \"bool\":true",
    "\"string\":\"string\", \"int\":1, \"bool\":true}",
    "{\"string\":\"string\", \"int\":1, \"group\":{\"string\":\"string\", }, \"bool\":true}",
    "{\"string\":\"string\", \"int\":1, \"array\":[1, 2, 3, \"bool\":true}",
    "{\"string\":\"true_string\", \"int\", 1, \"array\":[{\"int\":1, \"string\":\"string\"}, {\"int\":2, \"string\":\"string\"}, {\"int\":3, \"string\":\"string\"}], \"bool\":true}",

    // complex cases, 2
    "{\"problems\": [{\"Diabetes\": [{\"medications\": [{\"medicationsClasses\": [{\"className\": [{\"associatedDrug\": [{\"name\": \"asprin\", \"dose\": \"\", \"strength\": \"500 mg\"}], \"associatedDrug#2\": [{\"name\": \"somethingElse\", \"dose\": \"\", \"strength\": \"500 mg\"}]}], \"className2\": [{\"associatedDrug\": [{\"name\": \"asprin\", \"dose\": \"\",\"strength\": \"500 mg\"}], \"associatedDrug#2\": [{\"name\": \"somethingElse\", \"dose\": \"\", \"strength\": \"500 mg\"}]}]}]}], \"labs\": [{\"missing_field\": \"missing_value\"}]}], \"Asthma\": [{}]}]}",
    "{\"id\": \"0001\", \"type\": \"donut\", \"name\": \"Cake\", \"ppu\": 0.55, \"batters\":{\"batter\":[{\"id\": \"1001\", \"type\": \"Regular\"},	{ \"id\": \"1002\", \"type\": \"Chocolate\" }, { \"id\": \"1003\", \"type\": \"Blueberry\" }, { \"id\": \"1004\", \"type\": \"Devil's Food\" }]}, \"topping\": [{ \"id\": \"5001\", \"type\": \"None\" }, { \"id\": \"5002\", \"type\": \"Glazed\" }, { \"id\": \"5005\", \"type\": \"Sugar\" }, { \"id\": \"5007\", \"type\": \"Powdered Sugar\" }, { \"id\": \"5006\", \"type\": \"Chocolate with Sprinkles\" }, { \"id\": \"5003\", \"type\": \"Chocolate\" }, { \"id\": \"5004\", \"type\": \"Maple\" }]}",
};
jerif_err TEST_CASE_RESULT[] = {
    jerif_ok,
    jerif_ok,
    jerif_ok,
    jerif_ok,
    jerif_ok,
    jerif_ok,
    jerif_ok,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
    jerif_err_invalid_json,
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
        err_code = jerif_check_validation(TEST_CASE_JSON_STR[i]);
        success_count += check_result(err_code==TEST_CASE_RESULT[i]);
    }

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
