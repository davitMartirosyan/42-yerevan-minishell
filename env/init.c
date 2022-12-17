/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/17 15:52:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void reserved(t_table **table);

void create_shell(char **envp, t_table **table)
{
	if((*table)->minienv)
		(*table)->env = env_tokenizing((*table)->minienv);
	else
    	(*table)->env = env_tokenizing(envp);
	(*table)->minienv = create_envp(&(*table)->env);
	add_paths(&(*table)->env, table);
}

void bash_setup(t_table **table)
{
	*table = malloc(sizeof(t_table));
	if(!table)
		return ;
	(*table)->minienv = NULL;
	(*table)->paths = NULL;
	reserved(table);
	(*table)->builtin[0] = print_echo;
	(*table)->builtin[1] = print_pwd;
	(*table)->builtin[2] = print_cd;
	(*table)->builtin[3] = ft_unset;
	(*table)->builtin[4] = ft_export;
	(*table)->builtin[5] = ft_exit;
	(*table)->builtin[6] = print_env;
}

void reserved(t_table **table)
{
	(*table)->reserved[0] = "echo";
	(*table)->reserved[1] = "pwd";
	(*table)->reserved[2] = "cd";
	(*table)->reserved[3] = "unset";
	(*table)->reserved[4] = "export";
	(*table)->reserved[5] = "exit";
	(*table)->reserved[6] = "env";
}

