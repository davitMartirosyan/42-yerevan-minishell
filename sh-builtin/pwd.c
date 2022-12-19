/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:41 by sabazyan          #+#    #+#             */
/*   Updated: 2022/10/25 14:30:52 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	print_pwd(t_cmdline *cmd, t_table *table)
{
	(void)table;
	char	**matrix;
	char	cwd[256];

	matrix = cmd->cmds->arg_pack;
	if (matrix[0] && ft_strcmp(matrix[0], "pwd") == 0)
		printf("%s\n", getcwd(cwd, 256));
}