/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_components.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:57:58 by user              #+#    #+#             */
/*   Updated: 2022/12/13 11:14:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	cmd_check(t_cmds *cmd, char **paths)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
    if (access(cmd->arg_pack[0], F_OK & X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->arg_pack[0]);
		cmd->exit_status = EXIT_SUCCESS;
		return (0);
	}
    if(paths == NULL)
        return (-2);
	while (paths[i])
	{
		path = join_arguments(paths[i], '/', cmd->arg_pack[0]);
		if (access(path, F_OK & X_OK) == 0)
		{
			cmd->path = ft_strdup(path);
			cmd->exit_status = EXIT_SUCCESS;
			free(path);
			return (0);
		}
		free(path);
		i++;
	}
	return (-1);
}

int find_in(char *builtin, char **reserved)
{
    t_vars v;
    
    v.let = -1;
    v.var = -1;
    while(reserved[++v.let]);
    while(reserved[++v.var])
    {
    	v.def = ft_strlen(reserved[v.var]);
        v.log = ft_strlen(builtin);
        if(ft_strncmp(builtin, reserved[v.var], v.def) == 0 && \
			v.def == v.log)
			break;
    }
    if(v.var == v.let && ft_strncmp(builtin, reserved[v.var-1], \
        ft_strlen(reserved[v.var-1])) != 0)
        return (-1);
	else if(v.var == v.let && ft_strncmp(builtin, reserved[v.var-1], \
        ft_strlen(builtin)) != 0)
        return (-1);
    return (v.var);
}