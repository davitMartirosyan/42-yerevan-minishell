/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/14 15:04:15 by user             ###   ########.fr       */
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
        tree = parse_tree(table, envp);
        // printf("%s\n", tree->cmds->arg_pack[2]);
        // if(tree)
        //     execute_command(tree, table, envp);
    }
}

// while(table->token != NULL)
// {
//     printf("[%s] : %d\n", table->token->tok, table->token->type);
//     table->token = table->token->next;
// }