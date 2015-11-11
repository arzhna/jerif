#include <stdio.h>
#include <string.h>

#include "jerif.h"

#define OPTION_VERSION  "-v"
#define OPTION_HELP     "-h"

void print_version(void)
{
    printf("jerif version %s\n", jerif_get_version());
}

void print_usage(void)
{
    printf("Usage: jerif {options} <json string>\n\n");
}

void printf_help(void)
{
    print_usage();
    printf("Options are ...\n");
    printf("\t%s\t\tDisplay the program version.\n", OPTION_VERSION);
    printf("\t%s\t\tDisplay this help message.\n", OPTION_HELP);
}

int main(int argc, char* argv[])
{
    jerif_err err_code = jerif_ok;

    if(argc<2){
        print_usage();
        return 0;
    }

    if(strcmp(argv[1], OPTION_VERSION)==0){
        print_version();
    }
    else if(strcmp(argv[1], OPTION_HELP)==0){
        printf_help();
    }
    else{
        printf("%s\n", argv[1]);
        err_code = jerif_check_validation(argv[1]);
        if(err_code){
            printf(" => [INVALID]\n");
            return -1;
        }

        printf(" => [VALID]\n");
    }
    return 0;
}
