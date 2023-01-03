/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exit.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: user <user@student.42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/25 14:32:49 by sabazyan		  #+#	#+#			 */
/*   Updated: 2022/12/14 11:29:27 by user			 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"
#include <limits.h>

int	ft_isnumeric(char **s)
{
	int	i;
	int	j;

	i = 1;
	while (s && s[i])
	{
		j = 1;
		if (ft_strcmp(s[i], "-") == 0 || ft_strcmp(s[i], "+") == 0)
			return (0);
		if (s[i][0] < 43 || (s[i][0] > 43 && s[i][0] < 45)
		|| (s[i][0] > 45 && s[i][0] < 48) || s[i][0] > 57)
			return (0);
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

unsigned long long int	ft_atoi_(char *str)
{
	int						i;
	int						syb;
	unsigned long long int	counter;

	i = 0;
	syb = 1;
	counter = 0;
	if (str == (void	*)0)
		return (0);
	if (str[i] == '-')
		syb = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		counter = counter * 10 + str[i] - '0';
		i++;
	}
	return (syb * counter);
}

void	exit_cases(char **matrix, t_table *tab)
{
	unsigned long long int	check;

	check = 9223372036854775807;
	if (matrix[1] && (ft_isnumeric(matrix) == 0
			|| ft_atoi_(matrix[1]) > check))
	{
		printf("exit\n");
		ft_fprintf(STDERR_FILENO, "-sadm: exit: %s: numeric argument required\n", matrix[1]);
	}
	else if (matrix[1] && !matrix[2])
	{
		printf("exit\n");
		exit(1);
		// tab->status = ft_atoi_(matrix[1]) % 256;
		// //printf("status = %d, atoi = %llu\n", tab->status, ft_atoi_(matrix[1]));
		exit(tab->status);
	}
}

void	ft_exit(t_cmds *cmd, t_table *tab)
{
	char	**matrix;

	matrix = cmd->arg_pack;
	if (!matrix[1])
	{
		printf("exit\n");
		exit(tab->status);
	}
	else if (matrix[1] && matrix[2])
	{
		printf("exit\n");
		ft_fprintf(STDERR_FILENO, "-sadm: exit: too many arguments\n");
	}
	else
		exit_cases(matrix, tab);
}

// > 9223372036854775807 error