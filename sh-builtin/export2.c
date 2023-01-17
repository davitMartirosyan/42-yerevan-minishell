/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:34:00 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/14 10:34:04 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	create_key(char *str, t_table *tab)
{
	t_env	*temp;

	if (check_key(str, tab))
		return ;
	temp = tab->env;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env) + 1);
	if (!temp->next)
		return ;
	temp->next->key = NULL;
	temp->next->val = NULL;
	temp = temp->next;
	temp->key = ft_strdup(str);
	temp->next = NULL;
}

void	create_key_new_value(char *str, t_table *tab)
{
	t_env	*temp;
	int		index;
	int		len;
	char	*tmp_str;

	temp = tab->env;
	index = check_plus_equal(str);
	len = ft_strlen(str);
	if (create_key_new_value2(str, tab, index, len) == 1)
		return ;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env));
	if (!temp->next)
		return ;
	temp->next->key = NULL;
	temp->next->val = NULL;
	temp = temp->next;
	tmp_str = ft_substr(str, 0, index);
	temp->key = tmp_str;
	temp->val = ft_substr(str, index + 1, len);
	temp->next = NULL;
}

int	create_key_new_value2(char *str, t_table *tab, int index, int len)
{
	t_env	*temp;
	char	*tmp_str;

	temp = tab->env;
	tmp_str = ft_substr(str, 0, index);
	if (check_key(tmp_str, tab) && str[index + 1])
	{
		while (temp)
		{
			if (!ft_strcmp(temp->key, tmp_str))
				create_key_new_value3(temp, str, index, len);
			temp = temp->next;
		}
		free(tmp_str);
		return (1);
	}
	else if (check_key(tmp_str, tab) && !str[index + 1])
	{
		create_key_new_value4(temp, tmp_str);
		return (1);
	}
	free(tmp_str);
	return (0);
}

void	create_key_new_value3(t_env *temp, char *str, int index, int len)
{
	free(temp->val);
	temp->val = ft_substr(str, index + 1, len);
}

void	create_key_new_value4(t_env *temp, char *tmp_str)
{
	while (temp)
	{
		if (!ft_strcmp(temp->key, tmp_str))
		{
			free(temp->val);
			temp->val = ft_strdup("");
		}
		temp = temp->next;
	}
	free(tmp_str);
}
