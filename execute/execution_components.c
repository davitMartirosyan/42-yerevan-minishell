/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_components.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:55:44 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 04:29:25 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	cmd_check(t_cmds *cmd, t_table *table)
{
	table->paths = add_paths(&table->env);
	if (table->paths == NULL)
	{
		cmd->path = ft_strdup(cmd->arg_pack[0]);
		return (check_dir_or_file(cmd));
	}
	if (ft_strncmp(cmd->arg_pack[0], ".", 1) == 0
		|| ft_strchr(cmd->arg_pack[0], '/'))
		return (check_dir_or_file(cmd));
	if (ft_strncmp(cmd->arg_pack[0], "minishell", 10) == 0)
	{
		cmd->path = join_paths(table->cwd, '/', cmd->arg_pack[0]);
		return (1);
	}
	if (check_in_paths(cmd, table->paths))
		return (1);
	return (0);
}

int	check_in_paths(t_cmds *cmd, char **paths)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = join_paths(paths[i], '/', cmd->arg_pack[0]);
		if (access(path, F_OK & X_OK) == 0)
		{
			cmd->path = ft_strdup(path);
			cmd->exit_status = EXIT_SUCCESS;
			free(path);
			return (1);
		}
		free(path);
		path = 0;
		i++;
	}
	return (1);
}

int	find_in(char *builtin, char **reserved)
{
	t_vars	v;

	v.let = -1;
	v.var = -1;
	while (reserved[++v.let])
	{
	}
	while (reserved[++v.var])
	{
		v.def = ft_strlen(reserved[v.var]);
		v.log = ft_strlen(builtin);
		if (ft_strncmp(builtin, reserved[v.var], v.def) == 0 && \
			v.def == v.log)
			break ;
	}
	if (v.var == v.let && ft_strncmp(builtin, reserved[v.var - 1], \
		ft_strlen(reserved[v.var - 1])) != 0)
		return (-1);
	else if (v.var == v.let && ft_strncmp(builtin, reserved[v.var - 1], \
		ft_strlen(builtin)) != 0)
		return (-1);
	return (v.var);
}

char	*join_paths(char *s1, int delimiter, char *s2)
{
	char	*arguments;
	int		i;
	int		c;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	arguments = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!arguments)
		return (NULL);
	i = -1;
	c = -1;
	while (s1[++i])
		arguments[i] = s1[i];
	arguments[i++] = delimiter;
	while (s2[++c])
		arguments[i++] = s2[c];
	arguments[i] = '\0';
	return (arguments);
}
