/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:55 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/28 14:42:27 by user             ###   ########.fr       */
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

int echo(t_cmdline *commands, t_table *table)
{
    printf("%s\n", commands->cmds->arg_pack[1]);
    return (1);
}