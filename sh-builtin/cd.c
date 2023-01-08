/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:20 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/07 19:06:07 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	change_path(t_table *tab, char *old_path)
{
	char	cwd[10000];
	char	*new_path;
	t_env	*temp;

	new_path = getcwd(cwd, 10000);
	if (check_path(tab, new_path) == 1)
		return ;
	temp = tab->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PWD"))
			temp->val = new_path;
		temp = temp->next;
	}
	temp = tab->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "OLDPWD"))
			temp->val = old_path;
		temp = temp->next;
	}
	tab->status = 0;
}

int	check_path(t_table *tab, char *new_path)
{
	if (!new_path)
	{
		printf("cd: error retrieving current directory: getcwd: cannot access");
		printf(" parent directories: No such file or directory\n");
		tab->pwd_status = 1;
		return (1);
	}
	return (0);
}

void	change_path_to_home(t_table *tab, char *old_path)
{
	t_env	*temp;
	int		check;

	temp = tab->env;
	check = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "HOME"))
		{
			if (chdir(temp->val) == -1)
				printf("minishell: cd: %s: No such file or directory\n",
					temp->val);
			else
				change_path(tab, old_path);
			check = 0;
		}
		temp = temp->next;
	}
	if (check)
		printf("minishell: cd: HOME not set\n");
}

void	print_cd(t_cmds *cmd, t_table *tab)
{
	char	**matrix;
	char	cwd[10000];
	char	*old_path;

	matrix = cmd->arg_pack;
	old_path = getcwd(cwd, 10000);
	if (!old_path)
		no_old_path(old_path, tab);
	if (matrix[0] && ft_strcmp(matrix[0], "cd") == 0
		&& (!matrix[1] || ft_strcmp(matrix[1], "~") == 0))
	{
		tab->status = 1;
		change_path_to_home(tab, old_path);
	}
	else if (matrix[0] && ft_strcmp(matrix[0], "cd") == 0 && matrix[1])
	{
		if (chdir(matrix[1]) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", matrix[1]);
			tab->status = 1;
		}
		else
			change_path(tab, old_path);
	}
}

void	no_old_path(char *old_path, t_table *tab)
{
	t_env	*temp;

	(void)old_path;
	temp = tab->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PWD"))
			old_path = temp->val;
		temp = temp->next;
	}
}