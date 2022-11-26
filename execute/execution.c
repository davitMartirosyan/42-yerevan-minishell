/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:34:37 by codespace         #+#    #+#             */
/*   Updated: 2022/11/26 21:11:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static int cmd_check(t_cmds *cmd, char **paths);

void execution(t_cmdline **commands, t_table **table, char **envp)
{
    printf("%d\n", cmd_check((*commands)->cmds, (*table)->paths));
    printf("%s\n", (*commands)->cmds->path);
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