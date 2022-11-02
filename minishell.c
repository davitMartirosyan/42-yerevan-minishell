/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/02 16:14:39 by user             ###   ########.fr       */
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
}