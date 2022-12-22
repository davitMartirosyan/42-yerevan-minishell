/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/18 14:32:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

static void free_tokens(t_tok *token);
static void free_parse_tree(t_cmdline *tree);

char *ft_readline(void)
{
    char	*cmd;

	cmd = NULL;
    cmd = readline(SHELL);
	if(!cmd)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (cmd[0])
		add_history(cmd);
	return (cmd);
}

int main(int argc, char *argv[], char *envp[])
{
	t_table		*table;
	t_cmdline	*tree;
	char		*cmdline;
	
	(void)argv;
	(void)envp;
	(void)argc;
	tree = NULL;
	table = NULL;
	bash_setup(&table, envp);
    while (1)
    {
		ft_signal();
        cmdline = ft_readline();
        if(lexical_analyzer(cmdline, table))
        {
            tree = parse_tree(table);
            // execution(&tree, &table);
			free_tokens(table->token);
			free_parse_tree(tree);
        }
		free(cmdline);
    }
    return (0);
}

static void free_tokens(t_tok *token)
{
	t_tok *fre;

	fre = token;
	while(token != NULL)
	{
		fre = token->next;
		free(token->tok);
		free(token);
		token = fre;
	}
}

static void free_parse_tree(t_cmdline *tree)
{
	(void)tree;
	
	// t_cmds *cmd;
	// t_cmds *cmdtmp;
	
	// cmd = tree->cmds;
	// cmdtmp = cmd;
	// while(cmd != NULL)
	// {
	// 	cmdtmp = cmd->next;
	// 	free(cmd->arguments);
	// 	if(cmd->path != NULL)
	// 		free(cmd->path);
	// 	if(cmd->err != NULL)
	// 		free(cmd->path);
	// 	free(cmd);
	// 	cmd = cmdtmp;
	// }
}