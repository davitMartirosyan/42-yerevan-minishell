/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/13 14:30:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

static char *ft_readline(void);

static char *ft_readline(void)
{
    char	*cmd;

    cmd = readline(SHELL);
	if (cmd[0])
		add_history(cmd);
	return (cmd);
}

int main(int argc, char *argv[], char *envp[])
{
	t_table	*table;
	t_cmdline	*tree;
	char    *cmdline;
	(void)argv;
	(void)envp;
	(void)argc;
	tree = NULL;
	signals(1);
    create_shell(envp, &table);
    while (1)
    {
        cmdline = ft_readline();
        if(lexical_analyzer(cmdline, table))
        {
            tree = parse_tree(table);
            execution(&tree, &table);
        }
    }
    return (0);
}
