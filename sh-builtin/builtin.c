/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:27:41 by user              #+#    #+#             */
/*   Updated: 2022/11/20 12:40:39 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int echo(t_cmdline *command, t_table *table)
{
    // printf("%s\n", command->cmds->arg_pack[1]);
    return (1);
}

int builtin_execution(int k, t_cmdline *cmd, t_table *table)
{
    int execution;
    
    if(k != -1)
    {
        execution = table->builtin[k](cmd, table);
        return (execution);
    }
    return (-1);
}