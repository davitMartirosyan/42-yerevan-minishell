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
//cmd->arg_pack
//t_cmdline *cmd

// void	builtins(t_cmdline *cmd, t_table *table)
// {
// 	char	**matrix;

// 	matrix = cmd->cmds->arg_pack;
// 	if (!cmd || !table || !matrix[0])
// 		return ;
// 	else if (!ft_strcmp(matrix[0], "export"))
// 		ft_export(cmd, table);
// 	else if (!ft_strcmp(matrix[0], "unset"))
// 		ft_unset(cmd, table);
// 	else if (!ft_strcmp(matrix[0], "env"))
// 		print_env(cmd, table);
// 	else if (!ft_strcmp(matrix[0], "pwd"))
// 		print_pwd(cmd);
// 	else if (!ft_strcmp(matrix[0], "cd"))
// 		print_cd(cmd, table);
// 	else if (!ft_strcmp(matrix[0], "echo"))
// 		print_echo(cmd, table);
// 	else if (!ft_strcmp(matrix[0], "exit"))
// 		ft_exit(cmd, table);
// 	else
// 		printf("minishell: %s: command not found\n", matrix[0]);
// }

// void	builtins(char *cmdline, t_table *table)
// {
// 	char	**matrix;

// 	matrix = ft_split(cmdline, ' ');
// 	if (!cmdline || !table || !matrix[0])
// 		return ;
// 	else if (!ft_strcmp(matrix[0], "export"))
// 		ft_export(cmdline, table);
// 	else if (!ft_strcmp(matrix[0], "unset"))
// 		ft_unset(cmdline, table);
// 	else if (!ft_strcmp(matrix[0], "env"))
// 		print_env(cmdline, table);
// 	else if (!ft_strcmp(matrix[0], "pwd"))
// 		print_pwd(cmdline);
// 	else if (!ft_strcmp(matrix[0], "cd"))
// 		print_cd(cmdline, table);
// 	else if (!ft_strcmp(matrix[0], "echo"))
// 		print_echo(cmdline, table);
// 	else if (!ft_strcmp(matrix[0], "exit"))
// 		ft_exit(cmdline, table);
// 	else
// 		printf("minishell: %s: command not found\n", cmdline);
// }
