#include "./includes/minishell_header.h"

void handle(int sg)
{
 write(1, "hello", 5);
}

int main(int ac, char *av[], char *envp[])
{
    struct sigaction sa;
     int a = 5;
    
    printf("%d", a);
}




//  char *cmd;

    // t_envkeys *e;

    // e = NULL;
    // env_tokenizing(&e, envp);
    
    // printf("%s\n", e->val);
//     cmd = readline("$ ");
//     printf("%s\n", cmd);

// gcc env/*.c utils/*.c libft/libft.a  minishell.c -o minishell
