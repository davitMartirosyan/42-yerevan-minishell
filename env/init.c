/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/28 14:39:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void create_shell(char **envp, t_table **table)
{
	*table = malloc(sizeof(t_table));
	(*table)->env = malloc(sizeof(t_env));
    (*table)->env = env_tokenizing(envp);
	(*table)->reserved = ft_split(RESERVED, ' ');
	add_paths(&(*table)->env, table);
	// "echo pwd cd unset export exit env";
	(*table)->builtin[0] = echo;
	// (*table)->builtin[1] = pwd;
	// (*table)->builtin[2] = cd;
	// (*table)->builtin[3] = unset;
	// (*table)->builtin[4] = export;
	// (*table)->builtin[5] = exit_;
	// (*table)->builtin[6] = env;
}

