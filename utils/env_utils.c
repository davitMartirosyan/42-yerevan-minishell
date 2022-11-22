/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:55 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/02 01:30:46 by dmartiro         ###   ########.fr       */
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
