/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/03 19:30:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    t_table     *table;
    char        *cmdline;
    create_shell(envp, &table);
    while(1)
    {
        cmdline = readline(SHELL);
        add_history(cmdline);
        lexical_analyzer(cmdline, table);
        parse_tree(table, envp);
    }
    
    t_cmdline   *command;
    t_list      *list;
    t_cmds      *cmd;
    
    command = malloc(sizeof(t_cmdline));
    command->cmds = malloc(sizeof(t_list));
    list = command->cmds;
    command->cmds->content = malloc(sizeof(t_cmds));
    
    cmd = command->cmds->content;
    
    cmd->i_stream = 0;
    
    printf("%d\n", cmd->i_stream);
}