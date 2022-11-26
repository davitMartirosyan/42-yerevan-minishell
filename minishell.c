/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/26 20:41:58 by codespace        ###   ########.fr       */
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
    
    (void)tree;
    create_shell(envp, &table);
    while(1)
    {
        cmdline = readline(SHELL);
        add_history(cmdline);
        lexical_analyzer(cmdline, table);
        tree = parse_tree(table, envp);
        execution(&tree, &table, envp);
    }
    return (0);
}