/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:15:51 by codespace         #+#    #+#             */
/*   Updated: 2022/12/18 13:50:38 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void    free_char_pp(char **pp)
{
	int i;

	i = -1;
	if(!pp && !*pp)
		return ;
	while(pp[++i])
		free(pp[i]);
	free(pp);
	*pp = NULL;
}

void	free_tokens(t_tok *token)
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

void	free_parse_tree(t_cmdline *tree)
{
	(void)tree;

	t_cmds *cmd;
	t_cmds *cmdtmp;

	cmd = tree->cmds;
	cmdtmp = cmd;
	while(cmd != NULL)
	{
		cmdtmp = cmd->next;
		if(cmd->arguments != NULL)
			free(cmd->arguments);
		if(cmd->path != NULL)
			free(cmd->path);
		if(cmd->err && cmd->err != NULL)
			free(cmd->err);
        if(cmd->arg_pack != NULL)
		    free_char_pp(cmd->arg_pack);
		free(cmd);
		cmd = cmdtmp;
	}
	free(cmd);
	free(tree);
	tree = NULL;
}

void	update_table(t_table *table)
{
	table->err_handling = 0;
	table->q_c[0] = 0;
	table->q_c[1] = 0;
	table->hdocs = 0;
	free_tokens(table->token);
}