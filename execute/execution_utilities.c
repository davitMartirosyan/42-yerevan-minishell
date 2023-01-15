/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:33:14 by tumolabs          #+#    #+#             */
/*   Updated: 2023/01/15 12:50:08 by dmartiro         ###   ########.fr       */
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

void	execute_pipe_command(t_cmds *cmds, t_vars *v, t_table *table)
{
	if (cmds->i_stream == -1 || cmds->o_stream == -1)
	{
		file_mode(table, cmds);
		exit(1);
	}
	if (v->built != -1)
	{
		table->builtin[v->built](cmds, table);
		exit(0);
	}
	else if (v->binar == 1 && cmds->i_stream != -1 && cmds->o_stream != -1)
	{
		if(execve(cmds->path, cmds->arg_pack, create_envp(&table->env)) == -1)
		{
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", cmds->arg_pack[0], "Command not found");
			exit(1);
		}
	}
	else if (v->binar > 1)
	{
		v->log = 12;
		print_errors(v, cmds, table);
	}
}

void	_execute(t_vars *v, t_cmds *cmds, t_table *table)
{
	if (cmds->i_stream == -1 || cmds->o_stream == -1)
		file_mode(table, cmds);
	else if (v->built != -1)
		table->builtin[v->built](cmds, table);
	else if (v->binar == 1 && cmds->i_stream != -1 && \
		cmds->o_stream != -1)
		_ffork(cmds, table);
	else if (v->binar > 1)
		print_errors(v, cmds, table);
}

int	_execute_pipes(t_cmds *cmds, t_vars *v, t_table *table, int (*pip_ptr)[2])
{
	int	pip;
	int	ccount;
	int	i;

	pip = pipes(&table->token);
	i = 0;
	ccount = 0;
	while (cmds != NULL)
	{
		if (!check_command(cmds, v, table))
		{
			g_var = 23;
			cmds = cmds->next;
			continue;
		}
		cmds->pid = fork();
		if (cmds->pid == 0)
		{
			if(g_var == 23)
				exit(0);
			dup2(cmds->i_stream, STDIN_FILENO);
			dup2(cmds->o_stream, STDOUT_FILENO);
			piping(cmds, pip_ptr, i, pip);
			execute_pipe_command(cmds, v, table);
			dup2(cmds->i_stream, STDIN_FILENO);
		}
		cmds = cmds->next;
		ccount++;
		i++;
	}
	return (ccount);
}

void	_ffork(t_cmds *cmds, t_table *table)
{
	signal(SIGINT, SIG_IGN);
	cmds->pid = fork();
	if (cmds->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		table->minienv = create_envp(&table->env);
		if(execve(cmds->path, cmds->arg_pack, table->minienv) == -1)
		{
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", cmds->arg_pack[0], "Command not found");
			exit(127);
		}
	}
	else
		handle_status__and_wait(cmds->pid, &table->status);
	ft_signal(0);
}
