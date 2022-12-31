/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   export2.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sabazyan <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/11/14 10:34:00 by sabazyan		  #+#	#+#			 */
/*   Updated: 2022/11/14 10:34:04 by sabazyan		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"

void	create_key_value(char *str, t_table *tab)
{
	if (check_plus_equal(str) == 0)
		create_key(str, tab);
	else if (check_plus_equal(str) > 0)
		create_key_new_value(str, tab);
	else
		create_key_plus_value(str, tab);
}

void	create_key(char *str, t_table *tab)
{
	t_env	*temp;

	if (check_key(str, tab))
		return ;
	temp = tab->env;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env));
	if (!temp->next)
		return ;
	temp->next->key = NULL;
	temp->next->val = NULL;
	temp = temp->next;
	temp->key = str;
	temp->next = NULL;
}

void	create_key_new_value(char *str, t_table *tab)
{
	t_env	*temp;
	int		index;
	int		len;

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
	temp->key = ft_substr(str, 0, index);
	temp->val = ft_substr(str, index + 1, len);
	temp->next = NULL;
}

int	create_key_new_value2(char *str, t_table *tab, int index, int len)
{
	t_env	*temp;

	temp = tab->env;
	if (check_key(ft_substr(str, 0, index), tab) && str[index + 1])
	{
		while (temp)
		{
			if (!ft_strcmp(temp->key, ft_substr(str, 0, index)))
				temp->val = ft_substr(str, index + 1, len);
			temp = temp->next;
		}
		return (1);
	}
	else if (check_key(ft_substr(str, 0, index), tab) && !str[index + 1])
	{
		while (temp)
		{
			if (!ft_strcmp(temp->key, ft_substr(str, 0, index)))
				temp->val = "";
			temp = temp->next;
		}
		return (1);
	}
	return (0);
}

void	create_key_plus_value(char *str, t_table *tab)
{
	t_env	*temp;
	int		index;
	int		len;

	temp = tab->env;
	index = -1 * check_plus_equal(str);
	len = ft_strlen(str);
	if (check_key(ft_substr(str, 0, index), tab))
	{
		loop_plus_value(str, temp, index, len);
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env));
	if (!temp->next)
		return ;
	temp->next->key = NULL;
	temp->next->val = NULL;
	temp = temp->next;
	temp->key = ft_substr(str, 0, index);
	temp->val = ft_strtrim(ft_substr(str, index + 2, len), "\"");
	temp->next = NULL;
}
