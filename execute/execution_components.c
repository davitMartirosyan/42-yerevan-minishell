/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_components.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:57:58 by user              #+#    #+#             */
/*   Updated: 2022/12/18 14:54:26 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static void free_char_pp(char **paths);

int	cmd_check(t_cmds *cmd, t_table **table)
{
	int		i;
	char	*path;
	char	**paths;
	
	i = 0;
	paths = add_paths(&(*table)->env);
	path = NULL;
    if (access(cmd->arg_pack[0], F_OK & X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->arg_pack[0]);
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
			free_char_pp(paths);
			return (0);
		}
		free(path);
		i++;
	}
	free_char_pp(paths);
	return (-1);
}

static void free_char_pp(char **paths)
{
	int i;

	i = -1;
	if(!*paths && !paths)
		return ;
	while(paths[++i])
		free(paths[i]);
	*paths = NULL;
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

void print_err(t_table **table, t_cmdline **cmd, t_vars *v)
{
	if((*table)->status == 1)
        printf("%s%s%s", SHELLERR, (*cmd)->cmds->err, FILEERR); // no such file or direcotry
	else if((*table)->status == 127)
	{
		if(v->binar == -2)
			printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], FILEERR); // no such file or direcotry
		else
        	printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR); // command not found
	}
	else
		return ;
}