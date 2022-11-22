/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:20 by sabazyan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/11/07 19:06:07 by sabazyan         ###   ########.fr       */
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	change_path(t_table *tab, char *old_path)
{
	char	cwd[10000];
	char	*new_path;
	t_env	*temp;

	new_path = getcwd(cwd, 10000);
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
}

void	change_path_to_home(t_table *tab, int res, char *old_path)
{
	t_env	*temp;
	int		check;

	temp = tab->env;
	check = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "HOME"))
		{
			res = chdir(temp->val);
			if (res == -1)
				printf("minishell: cd: %s: No such file or directory\n",
					temp->val);
			else if (res == 0)
				change_path(tab, old_path);
			check = 0;
		}
		temp = temp->next;
	}
	if (check)
		printf("minishell: cd: HOME not set\n");
}

void	print_cd(char *cmd, t_table *tab)
{
	char	**matrix;
	t_env	*temp;
	char	cwd[10000];
	char	*old_path;
	int		res;

	matrix = ft_split(cmd, ' ');
	temp = tab->env;
	old_path = getcwd(cwd, 10000);
	if (matrix[0] && ft_strcmp(matrix[0], "cd") == 0
		&& (!matrix[1] || ft_strcmp(matrix[1], "~") == 0))
		change_path_to_home(tab, res, old_path);
	else if (matrix[0] && ft_strcmp(matrix[0], "cd") == 0 && matrix[1])
	{
		res = chdir(matrix[1]);
		if (res == -1)
			printf("minishell: cd: %s: No such file or directory\n", matrix[1]);
		else if (res == 0)
			change_path(tab, old_path);
	}
}
