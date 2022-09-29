/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/29 13:53:10 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

void create_shell(char **envp, t_table **table)
{
	*table = malloc(sizeof(t_table));
	(*table)->heredoc = malloc(sizeof(t_heredoc));
	(*table)->env = malloc(sizeof(t_env));
    (*table)->env = env_tokenizing(envp);
	add_paths(&(*table)->env, table);
}