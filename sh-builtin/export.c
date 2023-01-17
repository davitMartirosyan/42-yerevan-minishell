/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:17 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/18 12:30:33 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	export_err(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (check_err(str) == 0 || check_err2(str) == 0)
		return (1);
	tmp = ft_strdup(str);
	if (export_err2(tmp))
		return (1);
	if (!ft_isalpha(tmp[0]) && tmp[0] != '_')
	{
		free(tmp);
		return (1);
	}
	while (tmp[++i])
	{
		if (!ft_isalpha(tmp[i]) && !ft_isdigit(tmp[i]) && tmp[i] != '_')
		{
			free(tmp);
			return (1);
		}
	}
	free(tmp);
	return (0);
}

int	export_err2(char *tmp)
{
	if (check_plus_equal(tmp))
	{
		if (tmp[0] && tmp[0] == '+')
			return (1);
		if (ft_strchr(tmp, '+'))
			*ft_strchr(tmp, '+') = 0;
		else if (ft_strchr(tmp, '='))
			*ft_strchr(tmp, '=') = 0;
	}
	return (0);
}

int	check_key(char *str, t_table *tab)
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
	char	*tmp_str;
	char	*tmp_str2;
	char	*tmp_str3;

	tmp_str = ft_substr(str, 0, index);
	tmp_str2 = ft_substr(str, index + 2, len);
	while (temp)
	{
		if (!ft_strcmp(temp->key, tmp_str))
		{
			free(temp->val);
			tmp_str3 = ft_strtrim(tmp_str2, "\"");
			temp->val = ft_strjoin(ft_strtrim(temp->val, "\""), tmp_str3);
		}
		temp = temp->next;
	}
	free(tmp_str);
	free(tmp_str2);
	free(tmp_str3);
}
