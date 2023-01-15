/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:15:04 by tumolabs          #+#    #+#             */
/*   Updated: 2023/01/15 14:36:21 by tumolabs         ###   ########.fr       */
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
	if(g_var == 1)
	{
		g_var = 0;
		return;
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

	if (!cmd->cmds->arg_pack)
		return ;
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

void	piping_execute(int pip, t_cmdline *cmd, t_table *table)
{
	t_vars	v;
	t_cmds	*cmds;
	int		(*pip_ptr)[2];
	int		i;
	int		ccount;

	cmds = cmd->cmds;
	pip_ptr = malloc(sizeof(*pip_ptr) * pip);
	if (!pip_ptr)
		return ;
	i = -1;
	while (++i < pip)
		pipe(pip_ptr[i]);
	ccount = _execute_pipes(cmds, &v, table, pip_ptr);
	i = -1;
	close_all_pipes(pip_ptr, pip);
	while (ccount--)
		wait(&table->status);
	free(pip_ptr);
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
		ft_fprintf(STDERR_FILENO, "minishell: %s: Is a Directory\n", cmds->patherr);
		table->status = PATH_ERR_STATUS;
	}
}

void	print_errors(t_vars *v, t_cmds *cmds, t_table *table)
{
	if(v->binar == 3)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", cmds->arg_pack[0], strerror(errno));
		table->status = 126;
		if(v->log == 12)
			exit(126);
		return;
	}
}