/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:56:00 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/22 19:30:53 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	execution(t_cmdline **commands, t_table **table)
{
	int	pip;

	if ((*table)->syntax)
	{
		ft_fprintf(STDERR_FILENO, \
		"minishell: %s `%s'\n", TOKEN_SYNTAX_ERR, (*table)->syntax);
		return ;
	}
	if (g_var == 1)
	{
		(*table)->status = 1;
		g_var = 0;
		return ;
	}
	if (commands && *commands)
	{
		pip = pipes(&((*table)->token));
		if (pip == 0)
			execute(*commands, *table);
		else if (pip > 0)
			piping_execute(pip, *commands, *table);
	}
}

void	execute(t_cmdline *cmd, t_table *table)
{
	t_vars	v;

	table->dup0 = dup(STDIN_FILENO);
	table->dup1 = dup(STDOUT_FILENO);
	v.built = find_in(cmd->cmds->arg_pack[0], table->reserved);
	v.binar = cmd_check(cmd->cmds, table);
	dup2(cmd->cmds->i_stream, STDIN_FILENO);
	dup2(cmd->cmds->o_stream, STDOUT_FILENO);
	_execute(&v, cmd->cmds, table);
	dup2(table->dup0, STDIN_FILENO);
	dup2(table->dup1, STDOUT_FILENO);
	close(table->dup0);
	close(table->dup1);
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

void	piping_execute(int pip, t_cmdline *cmd, t_table *table)
{
	t_vars	v;
	t_cmds	*cmds;
	t_cmds	*tmpcmds;
	int		ccount;

	cmds = cmd->cmds;
	tmpcmds = cmd->cmds;
	table->pip_ptr = malloc(sizeof(*(table->pip_ptr)) * pip);
	if (!table->pip_ptr)
		return ;
	v.log = -1;
	while (++v.log < pip)
		pipe(table->pip_ptr[v.log]);
	ccount = _execute_pipes(cmds, &v, table);
	close_all_pipes(table->pip_ptr, pip);
	while (ccount--)
	{
		handle_status__and_wait(tmpcmds->pid, &table->status);
		tmpcmds = tmpcmds->next;
	}
	free(table->pip_ptr);
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
		if (execve(cmds->path, cmds->arg_pack, create_envp(&table->env)) == -1)
		{
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", \
				cmds->arg_pack[0], "Command not found");
			exit(127);
		}
	}
	else if (v->binar > 1)
	{
		v->log = 12;
		print_errors(v, cmds, table);
	}
}
