/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/14 07:57:05 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/12/18 14:32:33 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"
<<<<<<< HEAD

char	*ft_readline(void)
{
	char	*cmd;

	cmd = readline("minishell-$ ");
	if (!cmd)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (cmd[0])
		add_history(cmd);
	return (cmd);
}
=======
>>>>>>> master

char *ft_readline(char *line)
{
<<<<<<< HEAD
	t_table		*table;
	t_cmdline	*tree;
	char		*cmdline;

	(void)argv;
	(void)envp;
	(void)argc;
	signals(1);
	tree = NULL;
	create_shell(envp, &table);
	table->status = 0;
	while (1)
	{
		cmdline = ft_readline();
		if (lexical_analyzer(cmdline, table))
		{
			tree = parse_tree(table);
			execution(&tree, &table);
		}
	}
	free(cmdline);
	return (0);
}
=======
    char	*cmd;

	cmd = NULL;
    cmd = readline(line);
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
	(void)argc;
	tree = NULL;
	table = NULL;
	bash_setup(&table, envp);
    ft_signal(0);
	while (1)
    {
        cmdline = ft_readline("Minishell-$ ");
		if(!cmdline)
			handleterm(0);
        if(lexical_analyzer(cmdline, table))
        {
            tree = parse_tree(table);
		    execution(&tree, &table);
			update_table(tree, table);
        }
		free(cmdline);
    }
    return (0);
}
/*
signals
	in child process
	in heredocs
leaks
	echo
	cd
	export
*/
>>>>>>> master
