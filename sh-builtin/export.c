/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:17 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/03 13:42:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

/*char	*add_quotes(char *str)
{
	char	*new_str;
    int     len;
	int     i;

    len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 3));
	i = -1;
	while (str && str[++i - 1] != '=')
		new_str[i] = str[i];
	new_str[i++] = '"';
	i--;
	while (str[i])
	{
		new_str[i + 1] = str[i];
		i++;
	}
	new_str[++i] = '"';
	new_str[++i] = '\0';
	free(new_str);
	return (new_str);
}*/

/*void	sorting(char **arr)
{
	int	i;
	int	j;
	char *temp;

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
}*/

int	export_err(char *str)
{
	int		i;
	char	**key_val;

	i = 0;
	if (check_var(str))
	{
		key_val = ft_split(str, '=');
		str = key_val[0];
	}
	while (str[i])
	{
		if (!ft_isalpha(str[0]) && str[0] != '_')
			return (1);
		while (str[++i])
		{
			if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
				return (1);
		}
	}
	return (0);
}

int	check_key(t_env *env, char *str)
{
	t_env	*temp;
	char	**key_val;

	temp = env;
	key_val = ft_split(str, '=');
	if (check_var(str))
		str = key_val[0];
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	add_node(t_tab *tab, char *str)
{
	t_env	*temp;
	char	**key_val;

	temp = tab->env;
	if (check_key(temp, str))
		return ;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env));
	if (!check_var(str))
		temp->next->key = str;
	else {
		key_val = ft_split(str, '=');
		temp->next->key = key_val[0];
		if (key_val[1] == NULL)
			temp->next->val = "";
		else
			temp->next->val = ft_strtrim(key_val[1], "\"");
	}
	temp->next->next = NULL;
}

void	print_list_export(t_tab *tab)
{
	t_env	*temp;

	temp = tab->env;
	while (temp)
	{
		if (temp->val)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->val);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}

t_tab	*create_tab(char **env)
{
	t_tab *tab;

	tab = malloc(sizeof(t_tab));
	tab->env = env_tokenizing(env);
	return (tab);
}

int	check_var(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

void ft_export(char *cmd, t_tab *tab)
{
    char    **matrix;
    int     i;

    i = 0;
    matrix = ft_split(cmd, ' ');
	if (matrix[0] && ft_strcmp(matrix[0], "export") == 0 && !matrix[1])
		print_list_export(tab);
	else if (matrix[0] && ft_strcmp(matrix[0], "export") == 0 && matrix[1])
	{
		while (matrix[++i])
		{
			if (export_err(matrix[i]))
			{
				printf("-minishell: export: `%s': not a valid identifier\n", matrix[i]);
				continue ;
			}
			add_node(tab, matrix[i]);
		}
	}
}