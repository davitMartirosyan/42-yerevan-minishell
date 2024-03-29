/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mimic_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:57:43 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 03:13:13 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	typeis_arg(int type)
{
	if (type == WORD || type == EXP_FIELD)
		return (1);
	return (0);
}

int	typeis_redirection(int type)
{
	if (type == REDIR_OUT || type == REDIR_IN || type == APPEND)
		return (1);
	return (0);
}

int	typeis_heredoc(int type)
{
	if (type == HEREDOC)
		return (1);
	return (0);
}

int	pipes(t_tok **token)
{
	int	count;

	count = 0;
	while (*token != NULL)
	{
		if ((*token)->type == PIPE)
			count++;
		token = &(*token)->next;
	}
	return (count);
}

char	*join_arguments(char *s1, int delimiter, char *s2)
{
	char	*arguments;
	int		i;
	int		c;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	arguments = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!arguments)
		return (NULL);
	i = -1;
	c = -1;
	while (s1[++i])
		arguments[i] = s1[i];
	arguments[i++] = delimiter;
	while (s2[++c])
		arguments[i++] = s2[c];
	arguments[i] = '\0';
	free(s1);
	s1 = 0;
	return (arguments);
}
