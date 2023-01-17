/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:51:10 by sabazyan          #+#    #+#             */
/*   Updated: 2023/01/11 14:51:36 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	create_key_plus_value(char *str, t_table *tab)
{
	t_env	*temp;
	int		index;
	int		len;
	char	*tmp_str;

	temp = tab->env;
	index = -1 * check_plus_equal(str);
	len = ft_strlen(str);
	tmp_str = ft_substr(str, 0, index);
	if (check_key(tmp_str, tab))
	{
		free(tmp_str);
		loop_plus_value(str, temp, index, len);
		return ;
	}
	free(tmp_str);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env));
	if (!temp->next)
		return ;
	create_key_plus_value2(temp, str, len, index);
}

void	create_key_plus_value2(t_env *temp, char *str, int len, int index)
{
	char	*tmp_str;

	temp->next->key = NULL;
	temp->next->val = NULL;
	temp = temp->next;
	temp->key = ft_substr(str, 0, index);
	tmp_str = ft_substr(str, index + 2, len);
	temp->val = ft_strtrim(tmp_str, "\"");
	temp->next = NULL;
	free(tmp_str);
}
