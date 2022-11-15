/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/15 12:20:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    t_table     *table;
    t_cmdline   *tree;
    char        *cmdline;
    
    create_shell(envp, &table);
    while(1)
    {
        cmdline = readline(SHELL);
        add_history(cmdline);
        lexical_analyzer(cmdline, table);
        // while(table->token != NULL)
        // {
        //     printf("[%s] : %d\n", table->token->tok, table->token->type);
        //     table->token = table->token->next;
        // }
        tree = parse_tree(table, envp);
        // printf("%s\n", tree->cmds->arg_pack[2]);
        // if(tree)
        //     execute_command(tree, table, envp);
    }
}

