/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parsing_components.c							   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dmartiro <dmartiro@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/11/12 19:29:49 by root			  #+#	#+#			 */
/*   Updated: 2022/12/17 14:31:56 by dmartiro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"

void	select_filename(t_tok **token, t_cmds *cmds)
{
	int type;
	char *filename;

	filename = NULL;
	type = (*token)->type;
	while ((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
	while(*token != NULL && typeis_arg((*token)->type))
	{
		filename = ft_strjoin(filename, (*token)->tok);
		if((*token)->next == NULL)
			break;
		*token = (*token)->next;
	}
	open__file__check__type(type, filename, cmds);
	free(filename);
}

void	open__file__check__type(int type, char *filename, t_cmds *cmds)
{
	int fd;
	
	fd = 0;
	if (type == REDIR_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == HEREDOC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd == -1)
		cmds->patherr = ft_strdup(filename);
	check_type(fd, type, cmds);
}

void	check_type(int fd, int type, t_cmds *cmds)
{
	if (type == REDIR_IN || type == HEREDOC)
	{
		if (cmds->i_stream != 0)
			close(cmds->i_stream);
		cmds->i_stream = fd;
	}
	else if (type == REDIR_OUT || type == APPEND)
	{
		if (cmds->o_stream != 1)
			close(cmds->o_stream);
		cmds->o_stream = fd;
	}
}

int type_is_p_h(t_tok **token, t_cmds ***cmds, t_table *table, int *rtr)
{
	if (typeis_heredoc((*token)->type))
	{
		if(!(*token)->next || !typeis_arg((*token)->next->type))
		{
			_errno_(table, (*token)->tok);
			*rtr = -1;
			return 0;
		}
		heredoc(token, *(*cmds), table);
		if (typeis_arg((*token)->type))
			*token = (*token)->next;
		return 0;
	}
	if ((*token)->type == PIPE)
	{
		*cmds = &(*(*cmds))->next;
		*(*cmds) = malloc(sizeof(t_cmds));
		std(*cmds);	
		*token = (*token)->next;
		return 0;
	}
	return 1;
}

void	std(t_cmds **cmds)
{
	(*cmds)->arguments = NULL;
	(*cmds)->arg_pack = NULL;
	(*cmds)->path = NULL;
	(*cmds)->patherr = NULL;
	(*cmds)->i_stream = STDIN_FILENO;
	(*cmds)->o_stream = STDOUT_FILENO;
	(*cmds)->e_stream = STDERR_FILENO;
}