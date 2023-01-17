/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:05:07 by tumolabs          #+#    #+#             */
/*   Updated: 2023/01/17 04:34:52 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	check_dir_or_file(t_cmds *cmd)
{
	int	fd;

	if (is_dir(cmd->arg_pack[0]))
	{
		fd = open(cmd->arg_pack[0], O_WRONLY, 0644);
		cmd->path = ft_strdup(cmd->arg_pack[0]);
		return (3);
	}
	else if (is_file(cmd->arg_pack[0]))
	{
		if (access(cmd->arg_pack[0], X_OK) == 0)
		{
			cmd->path = ft_strdup(cmd->arg_pack[0]);
			return (1);
		}
		else
			return (3);
	}
	return (3);
}

int	is_file(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int	is_dir(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}
