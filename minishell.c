/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/17 03:08:28 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    t_table     *table;
    char        *cmd;
    create_shell(envp, &table);
    while(1)
    {
        cmd = readline(SHELL);
        lexical_analyze(cmd, &table);
        // parse_cmds(envp);
        // execute(&table, envp);
        // if(is_exit())
        //     exit(table->exit_status);
        // printf("%s\n", cmd);
    }
        
}


// echo "hello             ho?" how are you $USER | > out

  // gcc -lreadline env/*.c utils/*.c lex/*c libft/libft.a  minishell.c -o minishell && ./minishell
 //gcc  env/*.c utils/*.c lex/*c libft/libft.a  minishell.c -o minishell -lreadline && ./minishell
// gcc env/*.c utils/*.c libft/libft.a  minishell.c -o minishell
//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