/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/13 11:55:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void create_shell(char **envp, t_table **table)
{
	*table = malloc(sizeof(t_table));
	if(!table)
		return ;
	(*table)->paths = NULL;
    (*table)->env = env_tokenizing(envp);
	(*table)->minienv = create_envp(&(*table)->env);
	add_paths(&(*table)->env, table);
	//builtins
	(*table)->reserved = ft_split(RESERVED, ' ');
	(*table)->builtin[0] = echo;
	// (*table)->builtin[1] = pwd;
	// (*table)->builtin[2] = cd;
	// (*table)->builtin[3] = unset;
	// (*table)->builtin[4] = export;
	// (*table)->builtin[5] = exit_;
	// (*table)->builtin[6] = env;
}
