#include "./includes/minishell_header.h"

int main(void)
{
    char *cmd;

    cmd = readline("$>> ");

    printf("%s\n", cmd);
    
}