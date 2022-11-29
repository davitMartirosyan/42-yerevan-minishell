/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/11/29 21:55:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static int cmd_check(t_cmds *cmd, char **paths);

void execution(t_cmdline **commands, t_table **table, char **envp)
{
    pid_t pid;

    pid = fork();
    if(pid == 0)
    {
        cmd_check((*commands)->cmds, (*table)->paths);
        dup2((*commands)->cmds->i_stream, 0);
        execve((*commands)->cmds->path, (*commands)->cmds->arg_pack, 0);
        exit(1);
    }
    waitpid(-1, 0, 0);
}

static int cmd_check(t_cmds *cmd, char **paths)
{
    int i;
    char *path;

    i = 0;
    path = NULL;
    while(paths[i])
    {
        path = join_arguments(paths[i], '/', cmd->arg_pack[0]);
        if(access(path, F_OK) == 0)
            break;
        free(path);
        i++;
    }
    if(access(path, F_OK) == 0)
    {
        cmd->path = ft_strdup(path);
        free(path);
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


// if(find_in("echo", ["echo", "cd", "pwd"]) != -1)
//     //do builtin
// else if(cmd_check(&cmd, ["/usr/bin", "/bin", "/usr/sbin"]) == 0)
//     //do command
// else
//     //error
