/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/20 14:36:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    t_table     *table;
    char        *cmdline;
    create_shell(envp, &table);
    while(1)
    {
        cmdline = readline(SHELL);
        cmdline = lexical_analyzer(cmdline, &table);
        // parse_cmds(envp);
        // execute(cmd, &table, envp);
        // if(is_exit())
        //     exit(table->exit_status);
        if(cmdline)
            printf("%s\n", cmdline);
    }
    int a;
    a = ~2;
    printf("%d\n", a);

    //~2 -> 11111101
    //10 -> 00001010
    //2  -> 00000010
    //o  -> 00001000
}


   // echo "hello             ho?" how are you $USER | > out

  // gcc -lreadline env/*.c utils/*.c lex/*c libft/libft.a  minishell.c -o minishell && ./minishell
 //gcc  env/*.c utils/*.c lex/*c libft/libft.a  minishell.c -o minishell -lreadline && ./minishell
// gcc env/*.c utils/*.c libft/libft.a  minishell.c -o minishell
////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
//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
