/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/12 15:58:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

static char *ft_readline(void);

static char *ft_readline(void)
{
    char *cmd;
    
    cmd = readline("Minishell-$: ");
    if(cmd[0])
        add_history(cmd);
    return (cmd);
}

int main(int argc, char *argv[], char *envp[])
{
    (void)argv;
    (void)envp;
    (void)argc;
    t_table     *table;
    t_cmdline   *tree;
    char        *cmdline;
    
	tree = NULL;
    create_shell(envp, &table);
    while(1)
    {
        cmdline = ft_readline();
        if(lexical_analyzer(cmdline, table))
        {
            tree = parse_tree(table);
            execution(&tree, &table);
        }
        free(cmdline);
    }
    return (0);
}