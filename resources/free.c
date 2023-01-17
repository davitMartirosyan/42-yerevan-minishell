/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:57:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 03:40:33 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static void	unlink_heredocuments(int limit, int pid);

void	free_char_pp(char ***pp)
{
	int	i;

	i = -1;
	if (!(*pp) && !*(*pp))
		return ;
	while ((*pp)[++i])
		free((*pp)[i]);
	free((*pp));
	(*pp) = NULL;
}

void	free_tokens(t_tok *token)
{
	t_tok	*fre;

	if (!token)
		return ;
	fre = token;
	while (token != NULL)
	{
		fre = token->next;
		free(token->tok);
		free(token);
		token = fre;
	}
}

void	free_parse_tree(t_cmdline *tree)
{
	t_cmds	*cmd;
	t_cmds	*cmdtmp;

	(void)tree;
	cmd = tree->cmds;
	cmdtmp = cmd;
	while (cmd != NULL)
	{
		cmdtmp = cmd->next;
		free_cmd_workspace(cmd);
		free(cmd);
		cmd = cmdtmp;
	}
	free(cmd);
	free(tree);
	tree = NULL;
}

void	update_table(t_cmdline *tree, t_table *table)
{
	if (table->syntax)
	{
		free(table->syntax);
		table->syntax = NULL;
	}
	if (!tree || !table || !table->token)
		return ;
	free_tokens(table->token);
	unlink_heredocuments(table->hdocs, table->get_pid);
	free_parse_tree(tree);
	if (table->paths)
		free_char_pp(&table->paths);
	table->err_handling = 0;
	table->q_c[0] = 0;
	table->q_c[1] = 0;
	table->hdocs = 0;
	table->get_heredoc_flag = 0;
	g_var = 0;
}

static void	unlink_heredocuments(int limit, int pid)
{
	int		i;
	char	*path;
	char	*pid_;

	path = NULL;
	pid_ = NULL;
	i = -1;
	while (++i < limit)
	{
		pid_ = ft_itoa(pid);
		path = ft_strdup("/var/tmp/.minishell-");
		path = ft_strjoin(path, pid_);
		free(pid_);
		pid_ = ft_itoa(i);
		path = ft_strjoin(path, pid_);
		free(pid_);
		unlink(path);
		free(path);
	}
}
