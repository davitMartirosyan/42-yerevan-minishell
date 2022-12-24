/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:35:34 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/14 03:40:29 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	ft_export(t_cmdline *cmd, t_table *tab)
{
	char	**matrix;
	int		i;

	if (!cmd || !tab)
		return ;
	i = 0;
	matrix = cmd->cmds->arg_pack;
	if (matrix[0] && (ft_strcmp(matrix[0], "export") == 0) && !matrix[1])
		print_export(tab);
	else if (matrix[0] && (ft_strcmp(matrix[0], "export") == 0) && matrix[1])
	{
		while (matrix[++i])
		{
			if (export_err(matrix[i]))
			{
				printf("%s export: `%s': not a valididentifier\n",
					SHELLERR, matrix[i]);
				continue ;
			}
			create_key_value(matrix[i], tab);
		}
	}
}

void	print_export(t_table *tab)
{
	int		j;
	int		count;
	char	**export_matrix;

	j = -1;
	count = key_count(tab);
	printf("b\n");
	export_matrix = create_export_matrix(tab, count);
	sorting(export_matrix);
	while (export_matrix[++j] != NULL)
		printf("declare -x %s\n", export_matrix[j]);
}

char	**create_export_matrix(t_table *tab, int count)
{
	t_env	*temp;
	char	**matrix;
	char	*val;
	int		i;

	temp = tab->env;
	i = 0;
	matrix = malloc(sizeof(char *) * (count + 1));
	while (temp && temp->key)
	{
		if (temp->val)
		{
			if (ft_strchr(temp->val, '"'))
				val = temp->val;
			else
				val = ft_strjoin(ft_strjoin(ft_strdup("\""), temp->val), "\"");
			matrix[i] = ft_strjoin(ft_strjoin(temp->key, "="), val);
		}
		else
			matrix[i] = temp->key;
		i++;
		temp = temp->next;
	}
	matrix[i] = NULL;
	return (matrix);
}

int	key_count(t_table *tab)
{
	t_env	*temp;
	int		i;

	temp = tab->env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	sorting(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (arr[i][0] > arr[j][0])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}
