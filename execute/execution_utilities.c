/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:55:52 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 04:31:09 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	check_command(t_cmds *cmds, t_vars *v, t_table *table)
{
	if (!cmds->arg_pack)
		return (0);
	v->built = find_in(cmds->arg_pack[0], table->reserved);
	v->binar = cmd_check(cmds, table);
	return (1);
}

void	_ffork(t_cmds *cmds, t_table *table)
{
	signal(SIGINT, SIG_IGN);
	cmds->pid = fork();
	if (cmds->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		char** child_envp = create_envp(&table->env);
		if (execve(cmds->path, cmds->arg_pack, child_envp) == -1)
		{
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", \
				cmds->arg_pack[0], "Command not found");
			exit(127);
		}
	}
	else
		handle_status__and_wait(cmds->pid, &table->status);
	ft_signal(0);
}

void	file_mode(t_table *table, t_cmds *cmds)
{
	if (cmds->i_stream == -1)
	{
		ft_fprintf(STDERR_FILENO, \
		"minishell: %s: No such file or directory\n", cmds->patherr);
		table->status = PATH_ERR_STATUS;
	}
	if (cmds->o_stream == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: Is a Directory\n", \
			cmds->patherr);
		table->status = PATH_ERR_STATUS;
	}
}

void	print_errors(t_vars *v, t_cmds *cmds, t_table *table)
{
	if (v->binar == 3)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", \
			cmds->arg_pack[0], strerror(errno));
		table->status = 126;
		if (v->log == 12)
			exit(126);
		return ;
	}
}
