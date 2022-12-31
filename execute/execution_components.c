/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   execution_components.c							 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dmartiro <dmartiro@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/12 14:57:58 by user			  #+#	#+#			 */
/*   Updated: 2022/12/18 14:54:26 by dmartiro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"

int	cmd_check(t_cmds *cmd, t_table *table)
{
	int		i;
	char	*path;
	char	**paths;
	
	i = 0;
	paths = add_paths(&table->env);
	if (paths == NULL)
		return (-2);
	path = NULL;
	// if (access(cmd->arg_pack[0], F_OK & X_OK) == 0)
	// {
	// 	if (ft_strcmp(cmd->arg_pack[0], "minishell") == 0 || \
	// 		ft_strcmp(cmd->arg_pack[0], "./minishell") == 0)
	// 	{
	// 		free_char_pp(&paths);
	// 		cmd->path = ft_strdup(cmd->arg_pack[0]);
	// 		return (0);
	// 	}
	// }
	while (paths[i])
	{
		path = join_paths(paths[i], '/', cmd->arg_pack[0]);
		if (access(path, F_OK & X_OK) == 0)
		{
			cmd->path = ft_strdup(path);
			cmd->exit_status = EXIT_SUCCESS;
			free(path);
			free_char_pp(&paths);
			return (0);
		}
		free(path);
		path = 0;
		i++;
	}
	free_char_pp(&paths);
	return (-1);
}

int find_in(char *builtin, char **reserved)
{
	t_vars v;
	
	v.let = -1;
	v.var = -1;
	while (reserved[++v.let]);
	while (reserved[++v.var])
	{
		v.def = ft_strlen(reserved[v.var]);
		v.log = ft_strlen(builtin);
		if (ft_strncmp(builtin, reserved[v.var], v.def) == 0 && \
			v.def == v.log)
			break;
	}
	if (v.var == v.let && ft_strncmp(builtin, reserved[v.var-1], \
		ft_strlen(reserved[v.var-1])) != 0)
		return (-1);	
	else if (v.var == v.let && ft_strncmp(builtin, reserved[v.var-1], \
		ft_strlen(builtin)) != 0)
		return (-1);	
	return (v.var);
}

char	*join_paths(char *s1, int delimiter, char *s2)
{
	char *arguments;
	int i;
	int c;

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