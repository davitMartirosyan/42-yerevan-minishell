/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/18 13:17:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    (void)argv;
    (void)envp;
    (void)argc;
    t_table     *table;
    t_cmdline   *tree;
    char        *cmdline;
    
    create_shell(envp, &table);
    while(1)
    {
        cmdline = readline(SHELL);
        add_history(cmdline);
        lexical_analyzer(cmdline, table);
        tree = parse_tree(table, envp);
    }
    return (0);
}