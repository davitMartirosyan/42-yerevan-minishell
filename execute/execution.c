/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/12/03 07:52:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static int	cmd_check(t_cmds *cmd, char **paths);
static void	execute(t_cmdline **cmd, t_table **table, char **envp);
static void	combined_execution(int pip, t_cmdline **cmd, t_table **table, char **envp);

void	execution(t_cmdline **commands, t_table **table, char **envp)
{
	int	pip;

	pip = pipes(&((*table)->token));
	if (pip == 0)
		execute(commands, table, envp);
	else if (pip > 0)
		combined_execution(pip, commands, table, envp);
	else
		return ;
}

static void execute(t_cmdline **cmd, t_table **table, char **envp)
{
    pid_t pid;
    int built;
    int binary;

	if(!cmd && !*cmd && !table && !*table && !envp && !*envp)
		return ;
    pid = fork();
    if(pid == 0)
    {
        built = find_in((*cmd)->cmds->arg_pack[0], (*table)->reserved);
        binary = cmd_check((*cmd)->cmds, (*table)->paths);
		if((*cmd)->cmds->err != NULL)
		{
			printf("%s %d", (*cmd)->cmds->err);
			exit(1);
		}
        dup2((*cmd)->cmds->i_stream, 0);
        dup2((*cmd)->cmds->o_stream, 1);
        if(built != -1)
            (*table)->builtin[built]((*cmd)->cmds, *table);
        else if(binary != -1)
            execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, 0);
        else
            printf("%s%s%s", SHELLERR, (*cmd)->cmds->arg_pack[0], COMMANDERR);
        exit(1);
    }
    waitpid(-1, 0, 0);
}

static void combined_execution(int pip, t_cmdline **cmd, t_table **table, char **envp)
{

}

static int	cmd_check(t_cmds *cmd, char **paths)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
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
	if (access(cmd->arg_pack[0], F_OK & X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->arg_pack[0]);
		cmd->exit_status = EXIT_SUCCESS;
		return (0);
	}
	return (-1);
}

int find_in(char *builtin, char **reserved)
{
    t_vars v;
    
    v.let = -1;
    v.var = 0;
    v.def = ft_strlen(builtin);
    while(reserved[++v.let]);
    while(reserved[v.var])
    {
        v.log = ft_strlen(reserved[v.var]);
        if(ft_strncmp(builtin, reserved[v.var], v.log) == 0 && \
            v.def == v.log)
            break;
        v.var++;
    }
    if(v.var == v.let && ft_strncmp(builtin, reserved[v.var-1], \
        ft_strlen(reserved[v.var-1])) != 0)
        return (-1);
    return (v.var);
}