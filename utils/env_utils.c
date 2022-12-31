/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:55 by dmartiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/13 11:21:29 by user             ###   ########.fr       */
=======
/*   Updated: 2022/12/17 15:56:28 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
<<<<<<< HEAD

void free_environment(char **env_tokens)
{
    int i;

    i = -1;
    while(env_tokens[++i])
        free(env_tokens[i]);
    free(env_tokens);
}

int echo(t_cmds *cmd, t_table *table)
{
    int i;
	int flag;

	flag = 0;
    i = 0;
    if(!cmd->arg_pack[1])
        write(1, "\n", 1);
    while(cmd->arg_pack[++i])
    {
        ft_putstr_fd(cmd->arg_pack[i], 1);
        if(cmd->arg_pack[i + 1])
            ft_putchar_fd(' ', 1);
		if(!cmd->arg_pack[i+1])
		{
			flag = 1;
			break;
		}
    }
	if(flag == 1)
		write(1, "\n", 1);
    return (1);
}

int clear(t_cmds *cmd, t_table *table)
{
	(void)cmd;
	(void)table;
	printf("\e[1;1H\e[2J");
	return (1);
}
=======
>>>>>>> master
