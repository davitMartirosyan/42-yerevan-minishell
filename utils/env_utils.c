/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:55 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/01 14:44:02 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void free_environment(char **env_tokens)
{
    int i;

    i = -1;
    while(env_tokens[++i])
        free(env_tokens[i]);
    free(env_tokens);
}

int echo(t_cmds *cmd, t_table *table)
{
    int i;

    i = 0;
    while(cmd->arg_pack[++i])
    {
        write(1, cmd->arg_pack[i], \
            ft_strlen(cmd->arg_pack[i]));
        if(cmd->arg_pack[i+1])
            write(1, " ", 1);
        else
            write(1, "\n", 1);
    }
    return (1);
}