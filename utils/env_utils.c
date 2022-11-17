/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:55 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/17 15:58:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

void free_environment(char **env_tokens)
{
    int i;

    i = -1;
    while(env_tokens[++i])
        free(env_tokens[i]);
    free(env_tokens);
}

int find_in(char *builtin, char **reserved)
{
    int i;
    int builtin_len;
    int reserve_len;

    i = 0;
    builtin_len = ft_strlen(builtin);
    while(reserved[i])
    {
        reserve_len = ft_strlen(reserved[i]);
        if(ft_strncmp(builtin, reserved[i], reserve_len) == 0 \
            && builtin_len == reserve_len)
            break;
        i++;
    }
    return (i);
}
