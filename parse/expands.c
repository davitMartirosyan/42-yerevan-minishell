/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 06:43:56 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 07:11:21 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	__expand__join(t_cmds **cmds, t_tok **token)
{
	char	*joined;

	joined = NULL;
	joined = word_expansions(token);
	(*cmds)->arguments = join_arguments((*cmds)->arguments, 1, joined);
	if (joined != NULL)
		free(joined);
}

char	*word_expansions(t_tok **token)
{
	char	*word_exps;

	word_exps = NULL;
	while ((*token) != NULL)
	{
		word_exps = ft_strjoin(word_exps, (*token)->tok);
		*token = (*token)->next;
		if ((*token) != NULL && !typeis_arg((*token)->type))
			break ;
	}
	return (word_exps);
}

void	__free_(t_vars *v, char *tmpfile, char *term, char *delim)
{
	free(tmpfile);
	free(v);
	free(term);
	free(delim);
}

int	__open__readline__prompt(char **heredoc, char **delim, char **term)
{
	if (g_var == 1)
	{
		ft_signal(0);
		return (0);
	}
	if (*heredoc == NULL)
	{
		ft_fprintf(STDERR_FILENO, \
		"minishell: %s %d delimited by end-of-file (wanted `%s')\n", \
		HEREDOC_SYNTAX_WARNING, (uintmax_t)__LINE__, *delim);
		*term = ft_strjoin(*term, "\n");
		return (0);
	}
	if (*heredoc && ft_strcmp(*heredoc, *delim) != 0)
		*term = join_arguments(*term, '\n', *heredoc);
	if (ft_strlen(*heredoc) == ft_strlen(*delim) && \
			ft_strcmp(*heredoc, *delim) == 0)
	{
		*term = ft_strjoin(*term, "\n");
		return (0);
	}
	return (1);
}
