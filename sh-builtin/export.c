/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:17 by sabazyan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/11/18 12:30:33 by sabazyan         ###   ########.fr       */
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
<<<<<<< HEAD

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
=======
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2

int	export_err(char *str)
{
	int		i;
	char	**key_val;

	i = 0;
	if (check_plus_equal(str))
	{
		key_val = ft_split(str, '+');
		if (!key_val[0])
			return (1);
		str = ft_split(key_val[0], '=')[0];
	}
	while (str[i])
	{
		if (!ft_isalpha(str[0]) && str[0] != '_')
			return (1);
		while (str[++i])
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
				return (1);
		}
	}
	return (0);
}

<<<<<<< HEAD
int	check_key(t_env *env, char *str)
=======
int	check_key(char *str, t_table *tab)
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
{
	t_env	*temp;

	temp = tab->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, str))
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_table	*create_tab(char **env)
{
	t_table	*tab;

<<<<<<< HEAD
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
=======
	tab = malloc(sizeof(t_table));
	if (!tab || !env)
		return (NULL);
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
	tab->env = env_tokenizing(env);
	return (tab);
}

int	check_plus_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			return (-i);
		if (str[i] == '=')
			return (i);
	}
	return (0);
}

void	loop_plus_value(char *str, t_env *temp, int index, int len)
{
	while (temp)
	{
		if (!ft_strcmp(temp->key, ft_substr(str, 0, index)))
		{
			temp->val = ft_strjoin(ft_strtrim(temp->val, "\""),
					ft_strtrim(ft_substr(str, index + 2, len), "\""));
		}
		temp = temp->next;
	}
}
