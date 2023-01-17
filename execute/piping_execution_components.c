/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_execution_components.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:56:12 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 04:35:56 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	istream(t_cmds *cmd, int (*pipe)[2], int i)
{
	if (cmd->i_stream != 0)
		return (cmd->i_stream);
	return (pipe[i - 1][0]);
}

int	ostream(t_cmds *cmd, int (*pipe)[2], int i)
{
	if (cmd->o_stream != 1)
		return (cmd->o_stream);
	return (pipe[i][1]);
}

void	close_all_pipes(int pips[][2], int pip)
{
	int	a;

	a = -1;
	while (++a < pip)
	{
		close(pips[a][1]);
		close(pips[a][0]);
	}
}

void	handle_status__and_wait(int pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status);
	else if (WIFSTOPPED(*status))
		*status = WIFSTOPPED(*status);
}
