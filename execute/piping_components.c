/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_components.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:56:05 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 04:35:43 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	_execute_pipes(t_cmds *cmds, t_vars *v, t_table *table)
{
	int	ccount;

	table->pip = pipes(&table->token);
	v->let = 0;
	ccount = 0;
	while (cmds != NULL)
	{
		if (!check_command(cmds, v, table))
		{
			g_var = 23;
			cmds = cmds->next;
			continue ;
		}
		cmds->pid = fork();
		if (cmds->pid == 0)
			__ffork__exec__pipe__(cmds, table, v);
		cmds = cmds->next;
		ccount++;
		v->let++;
	}
	return (ccount);
}

void	__ffork__exec__pipe__(t_cmds *cmds, t_table *table, t_vars *v)
{
	if (g_var == 23)
		exit(0);
	dup2(cmds->i_stream, STDIN_FILENO);
	dup2(cmds->o_stream, STDOUT_FILENO);
	piping(cmds, table->pip_ptr, v->let, table->pip);
	execute_pipe_command(cmds, v, table);
	dup2(cmds->i_stream, STDIN_FILENO);
}

void	piping(t_cmds *cmd, int pip_ptr[][2], int i, int pip)
{
	int	o_stream;
	int	i_stream;

	if (i == 0)
	{
		o_stream = ostream(cmd, pip_ptr, i);
		dup2(o_stream, STDOUT_FILENO);
	}
	else if (i > 0 && i < pip)
	{
		i_stream = istream(cmd, pip_ptr, i);
		o_stream = ostream(cmd, pip_ptr, i);
		dup2(i_stream, STDIN_FILENO);
		dup2(o_stream, STDOUT_FILENO);
	}
	else
	{
		i_stream = istream(cmd, pip_ptr, i);
		dup2(i_stream, STDIN_FILENO);
		dup2(cmd->o_stream, STDOUT_FILENO);
	}
	close_all_pipes(pip_ptr, pip);
}
