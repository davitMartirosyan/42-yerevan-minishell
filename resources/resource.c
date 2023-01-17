/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 03:32:47 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 03:42:13 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	free_cmd_workspace(t_cmds *cmd)
{
	if (cmd->i_stream != 0)
		close(cmd->i_stream);
	if (cmd->o_stream != 1)
		close(cmd->o_stream);
	cmd->i_stream = STDIN;
	cmd->o_stream = STDOUT;
	free(cmd->arguments);
	free(cmd->path);
	free(cmd->patherr);
	if (cmd->arg_pack != NULL)
		free_char_pp(&cmd->arg_pack);
}
