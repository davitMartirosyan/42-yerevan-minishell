/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/29 09:17:57 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    t_env   *env;
    t_table     *table;
    char *cmd;
    create_env(&env, envp, &table);
    while(1)
    {
        cmd = readline("$: ");
        lexical_analyze(cmd, &env, &table);
        // parse_cmds();
        // execute_line();
        // if(is_exit())
        //     exit(table->exit_status);
        // printf("%s\n", cmd);
    }
}




//  char *cmd;

    // t_env *e;

    // e = NULL;
    // env_tokenizing(&e, envp);
    
    // printf("%s\n", e->val);
//     cmd = readline("$ ");
//     printf("%s\n", cmd);

// gcc -lreadline env/*.c utils/*.c lex/*c libft/libft.a  minishell.c -o minishell && ./minishell
// gcc env/*.c utils/*.c libft/libft.a  minishell.c -o minishell




//  char *cmdline;
//     char **tok;
//     char *path;
    
//     cmdline = readline("dmbash$ ");
//     tok = ft_split(cmdline, ' ');
//     path = ft_strjoin("/bin/", tok[0]);
//     execve(path, tok, NULL);