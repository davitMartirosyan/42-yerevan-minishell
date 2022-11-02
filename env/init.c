/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/29 12:57:41 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/11/02 01:29:40 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

<<<<<<< HEAD
void create(t_env **env, char **envp, t_table **table)
=======
void create_shell(char **envp, t_table **table)
>>>>>>> master
{
	*table = malloc(sizeof(t_table));
	(*table)->env = malloc(sizeof(t_env));
    (*table)->env = env_tokenizing(envp);
	(*table)->reserved = ft_split(RESERVED, ' ');
	add_paths(&(*table)->env, table);
}