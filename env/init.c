/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/27 03:34:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

void create_env(t_env **env, char **envp, t_table **table)
{
	*table = malloc(sizeof(t_table));
    *env = env_tokenizing(envp);
	add_paths(env, table);
}