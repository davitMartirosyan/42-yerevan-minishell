/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/05 00:15:01 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

static void print_tokens(t_tok **token);

int main(int argc, char *argv[], char *envp[])
{
    (void)argv;
    (void)envp;
    (void)argc;
    t_table     *table;
    t_cmdline   *tree;
    char        *cmdline;
    
    (void)tree;
	tree = NULL;
    create_shell(envp, &table);    
    while(1)
    {
        cmdline = readline("Minishell-$ ");
        add_history(cmdline);
        lexical_analyzer(cmdline, table);
        tree = parse_tree(table, envp);
        execution(&tree, &table, envp);
    }
    return (0);
}

static void print_tokens(t_tok **token)
{
	while((*token) != NULL)
	{
		printf("[%s] : %d\n", (*token)->tok, (*token)->type);
		token = &(*token)->next;
	}
}