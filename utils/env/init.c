/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/13 12:05:28 by user             ###   ########.fr       */
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
	(*table)->reserved = ft_split(RESERVED, ' ');
	(*table)->builtin[0] = print_echo;
	(*table)->builtin[1] = print_pwd;
	(*table)->builtin[2] = print_cd;
	(*table)->builtin[3] = ft_unset;
	(*table)->builtin[4] = ft_export;
	(*table)->builtin[5] = ft_exit;
	(*table)->builtin[6] = print_env;
}
