/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/18 14:32:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

char *ft_readline(void)
{
    char	*cmd;

    cmd = readline(SHELL);
	if(!cmd)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (cmd[0])
		add_history(cmd);
	return (cmd);
}

int main(int argc, char *argv[], char *envp[])
{
	t_table		*table;
	t_cmdline	*tree;
	char		*cmdline;
	
	(void)argv;
	(void)envp;
	(void)argc;
	tree = NULL;
	table = NULL;
	bash_setup(&table, envp);
    while (1)
    {
		ft_signal();
        cmdline = ft_readline();
        if(lexical_analyzer(cmdline, table))
        {
			// print_tokens(&(table)->token);
            tree = parse_tree(table);
            execution(&tree, &table);
        }
		//destruct_shell(&table, &tree);
    }
    return (0);
}