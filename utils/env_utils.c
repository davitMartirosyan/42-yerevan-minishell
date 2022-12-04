/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:55 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/04 22:08:32 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

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
        write(1, cmd->arg_pack[i], \
            ft_strlen(cmd->arg_pack[i]));
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