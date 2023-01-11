/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:35:34 by sabazyan          #+#    #+#             */
/*   Updated: 2023/01/11 20:28:49 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	ft_export(t_cmds *cmd, t_table *tab)
{
	char	**matrix;
	int		i;

	i = 0;
	tab->status = 0;
	matrix = cmd->arg_pack;
	if (matrix[0] && (ft_strcmp(matrix[0], "export") == 0) && !matrix[1])
		print_export(tab);
	else if (matrix[0] && (ft_strcmp(matrix[0], "export") == 0) && matrix[1])
	{
		while (matrix[++i])
		{
			if (export_err(matrix[i]))
			{
				ft_fprintf(STDERR_FILENO, \
					"-sadm: export: `%s': not a valid identifier\n",
					matrix[i]);
				tab->status = 1;
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
	export_matrix = create_export_matrix(tab, count);
	sorting(export_matrix);
	while (export_matrix[++j] != NULL)
		printf("declare -x %s\n", export_matrix[j]);
	free_char_pp(&export_matrix);
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
				val = ft_strdup(temp->val);
			else
				val = ft_strjoin(ft_strjoin(ft_strdup("\""), temp->val), "\"");
			matrix[i] = ft_strjoin(ft_strjoin(ft_strdup(temp->key), "="), val);
			free(val);
		}
		else
			matrix[i] = ft_strdup(temp->key);
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
