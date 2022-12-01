/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/12/01 12:34:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static int cmd_check(t_cmds *cmd, char **paths);
static void execute(t_cmdline **cmd, t_table **table, char **envp);
static void combined_execution(int pip, t_cmdline **cmd, t_table **table, char **envp);

void execution(t_cmdline **commands, t_table **table, char **envp)
{
    int pip;

    pip = pipes(&((*table)->token));
    if(pip == 0)
        execute(commands, table, envp);
    else if(pip > 0)
        combined_execution(pip, commands, table, envp);
    else
        return ;
}

static void execute(t_cmdline **cmd, t_table **table, char **envp)
{
    pid_t pid;
    int built;
    int binary;

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
    
    pips = malloc(sizeof(*pips) * pip);
    if(!pips)
        return ;
    v.let = -1;
    while(++v.let < pip)
        pipe(pips[v.let]);
    v.let = -1;
    v.log = dup(STDIN);
    v.def = dup(STDOUT);
    while(++v.let < pip)
    {
        pid = fork();
        if(pid == 0)
        {
            dup2(pips[v.let][1], (*cmd)->cmds->o_stream);
            close(pips[v.let][0]);
            v.built = find_in((*cmd)->cmds->arg_pack[0], (*table)->reserved);
            v.binar = cmd_check((*cmd)->cmds, (*table)->paths);
            if(v.built != -1)
                (*table)->builtin[v.built]((*cmd)->cmds, *table);
            else if(v.binar != -1)
                execve((*cmd)->cmds->path, (*cmd)->cmds->arg_pack, 0);
            else
            {
                printf("%s: %s : Command Not found\n", SHELLERR, (*cmd)->cmds->arg_pack[0]);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
         
        }
    }
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
    if(access(path, F_OK | X_OK) == 0)
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
