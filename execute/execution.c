/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/12/02 07:27:49 by dmartiro         ###   ########.fr       */
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
        dup2((*cmd)->cmds->i_stream, 0);
        dup2((*cmd)->cmds->o_stream, 1);
        if(built != -1)
            (*table)->builtin[built]((*cmd)->cmds, *table);
        else if(binary != -1)
            execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, 0);
        else
            printf("%s: %s : Command Not found\n", SHELLERR, (*cmd)->cmds->arg_pack[0]);
        exit(1);
    }
    waitpid(-1, 0, 0);
}

static void combined_execution(int pip, t_cmdline **cmd, t_table **table, char **envp)
{
    t_vars  v;
    int (*pips)[2];
    pid_t pid;
	int	i;
    
    pips = malloc(sizeof(*pips) * pip);
    if(!pips)
        return ;
    v.let = -1;
    while(++v.let < pip)
        pipe(pips[v.let]);
    v.let = 0;
    v.log = dup(STDIN);
    v.def = dup(STDOUT);
	i = 0;
    while((*cmd)->cmds != NULL)
    {
		pid = fork();
		if(pid == 0)
		{
			if(i == 0)
			{
			
				dup2(pips[i][1], STDOUT_FILENO);
				//close ()
			}
			else if(i < pip+1)
			{
				dup2(pips[i][1], 1);
				dup2(pips[i - 1][0], 0);
				close (pips[i][1]);
				close (pips[i - 1][0]);
			}else
			{
				dup2(pips[i - 1][0], 0);
				close (pips[i - 1][0]);
			}
			
		}
			i++;
		(*cmd)->cmds = (*cmd)->cmds->next;
		
    }
	
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
			free(path);
			return (0);
		}
		free(path);
		i++;
	}
	if (access(cmd->arg_pack[0], F_OK & X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->arg_pack[0]);
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