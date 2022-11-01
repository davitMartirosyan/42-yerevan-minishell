/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/01 15:53:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell_header.h"

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
        // while(table->token != NULL)
		// {
		// 	printf("[%s] : %d\n", table->token->tok, table->token->type);
		// 	table->token = table->token->next;
		// }
    }
}