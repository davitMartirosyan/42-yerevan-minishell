/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:54 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/07 19:07:18 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	unset_err(char *str)
{
	int		i;
	char	**key_val;

	i = 0;
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

void	remove_node(t_table *tab, char *str)
{
	t_env	*temp;

	temp = tab->env;
	if (temp && ft_strcmp(temp->key, str) == 0)
		tab->env = tab->env->next;
	else
	{
		while (temp->next)
		{
			if (ft_strcmp(temp->next->key, str) == 0)
			{
				temp->next = temp->next->next;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	ft_unset(t_cmdline *cmd, t_table *tab)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = cmd->cmds->arg_pack;
	if (matrix[0] && ft_strcmp(matrix[0], "unset") == 0 && matrix[1])
	{
		while (matrix[++i])
		{
			if (unset_err(matrix[i]))
			{
				printf("-minishell: export: `%s': not a valid identifier\n",
					matrix[i]);
				continue ;
			}
			remove_node(tab, matrix[i]);
		}
	}
}
