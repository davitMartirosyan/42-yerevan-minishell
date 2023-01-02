/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dmartiro <dmartiro@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/04 23:15:51 by codespace		 #+#	#+#			 */
/*   Updated: 2022/12/18 13:50:38 by dmartiro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"

static void	unlink_heredocuments(int limit, int pid);
void	free_char_pp(char ***pp)
{
	int i;

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
	t_tok *fre;

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
	(void)tree;

	t_cmds *cmd;
	t_cmds *cmdtmp;

	cmd = tree->cmds;
	cmdtmp = cmd;
	while (cmd != NULL)
	{
		cmdtmp = cmd->next;
		if (cmd->i_stream != 0)
			close(cmd->i_stream);
		if (cmd->o_stream != 1)
			close(cmd->o_stream);
		cmd->i_stream = STDIN;
		cmd->o_stream = STDOUT;
		free(cmd->arguments);
		free(cmd->path);
		free(cmd->patherr);
		if (cmd->arg_pack != NULL)
			free_char_pp(&cmd->arg_pack);
		free(cmd);
		cmd = cmdtmp;
	}
	free(cmd);
	free(tree);
	tree = NULL;
}

void	update_table(t_cmdline *tree, t_table *table)
{
	free_tokens(table->token);
	unlink_heredocuments(table->hdocs, table->get_pid);
	free_parse_tree(tree);
	table->err_handling = 0;
	table->q_c[0] = 0;
	table->q_c[1] = 0;
	table->hdocs = 0;
	table->get_heredoc_flag = 0;
}

static void	unlink_heredocuments(int limit, int pid)
{
	int i;
	char *path;
	char *pid_;

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