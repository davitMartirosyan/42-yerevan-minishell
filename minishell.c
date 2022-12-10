/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/10 22:41:29 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

int main(int argc, char *argv[], char *envp[])
{
    (void)argv;
    (void)envp;
    (void)argc;
    t_table     *table;
    t_cmdline   *tree;
    char        *cmdline;
    
	tree = NULL;
    create_shell(envp, &table);
    while(1)
    {
        cmdline = readline("Minishell-$: ");
        add_history(cmdline);
        lexical_analyzer(cmdline, table);
        tree = parse_tree(table);
        execution(&tree, &table);
        reset_update_table(&table, tree);
    }
    return (0);
}

//if (!cmdline || cmdline[0] == '\0')
//{
//	struct termios term;
//	tcgetattr(fileno(stdin), &term);

//	term.c_lflag &= ~ECHO;
//	tcsetattr(fileno(stdin), 0, &term);

//	ft_exit("exit 0");
//	//printf("\n");
//	//rl_replace_line("", 0);
//	//return 0;
//}