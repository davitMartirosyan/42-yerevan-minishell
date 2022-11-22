/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:32:26 by sabazyan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/11/07 19:04:03 by sabazyan         ###   ########.fr       */
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	print_env(char *cmd, t_table *table)
{
	char	**matrix;
	t_env	*temp;

	matrix = ft_split(cmd, ' ');
	temp = table->env;
	if (matrix[0] && ft_strcmp(matrix[0], "env") == 0 && !matrix[1])
	{
		while (temp)
		{
			if (temp->val && ft_strchr(temp->val, '"'))
				printf("%s=%s\n", temp->key, ft_strtrim(temp->val, "\""));
			else if (temp->val && !ft_strchr(temp->val, '"'))
				printf("%s=%s\n", temp->key, temp->val);
			temp = temp->next;
		}
	}
	else if (matrix[0] && ft_strcmp(matrix[0], "env") == 0 && matrix[1])
		printf("env: %s: No such file or directory\n",
			ft_strtrim(matrix[1], "\""));
}
