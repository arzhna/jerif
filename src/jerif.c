#include <stdio.h>
#include <string.h>

#include "jerif_stack.h"
#include "jerif_check.h"

void print_usage(void)
{
    printf("Usage: jerif <json string>\n");
}

int main(int argc, char* argv[])
{
    jerif_err err_code = jerif_ok;

    if(argc<2){
        print_usage();
        return 0;
    }

    printf("%s\n", argv[1]);
    err_code = jerif_check_validation(argv[1]);
    if(err_code){
        printf(" => [INVALID]\n");
        return -1;
    }

    printf(" => [VALID]\n");
    return 0;
}
