/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 01:32:43 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/02 06:58:05 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void parse_tree(t_table *table, char **envp)
{
	t_cmdline *command;

	command = malloc(sizeof(t_cmdline));
	if(!command)
		return (NULL);
	t_cmds *cmd_list = 
}