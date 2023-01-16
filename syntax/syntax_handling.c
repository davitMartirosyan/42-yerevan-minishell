/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:58:21 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/16 11:58:23 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void print_tokens(t_tok *tok)
{
	t_tok *tmp;

	tmp = tok;
	while(tmp != NULL)
	{
		printf("{%s} : %d\n", tmp->tok, tmp->type);
		tmp = tmp->next;
	}
}

void	syntax_error(t_table *table)
{
	t_tok *tmp;

	tmp = table->token;
	if(!tmp)
		return;
	while(tmp != NULL)
	{
		if(typeis_redirection(tmp->type))
			if(redirection_error(tmp, table) == -1)
				break;
		if(tmp->type == PIPE)
			if(pipe_error(tmp, table) == -1)
				break;
		tmp = tmp->next;
	}
}

int	pipe_error(t_tok *tmp, t_table *table)
{
	tmp = tmp->next;
	if(tmp == NULL || (tmp->type == SEP && tmp->next == NULL))
	{
		_errno_(table, "|");
		return (-1);
	}
	while(tmp != NULL)
	{
		if(tmp->type == SEP || typeis_arg(tmp->type) || typeis_redirection(tmp->type))	
			return (0);
		else
		{
			_errno_(table, "|");
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirection_error(t_tok *tmp, t_table *table)
{
	tmp = tmp->next;
	if(tmp == NULL)
	{
		_errno_(table, "newline");
		return (-1);
	}
	while(tmp != NULL)
	{
		if(tmp->type == SEP)
		{
			tmp = tmp->next;
			continue;
		}
		if((typeis_arg(tmp->type)))
			return (0);
		else
		{
			_errno_(table, tmp->tok);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	_errno_(t_table *table, char *err)
{
	table->status = SYNTAX_ERR_STATUS;
	if(table->syntax)
		free(table->syntax);
	table->syntax = ft_strdup(err);
}
//valgrind -leak-check=full