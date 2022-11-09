/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mimic_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:55:38 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/09 05:01:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int typeis_arg(int type)
{
	if(type == WORD || type == EXP_FIELD)
		return (1);
	return (0);
}

int typeis_redirection(int type)
{
	if(type == REDIR_OUT || type == REDIR_IN \
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int pipes(t_tok **token)
{
	int count;

	count = 0;
	while(*token != NULL)
	{
		if((*token)->type == PIPE)
			count++;
		token = &(*token)->next;
	}
	return count;
}

char		*join_arguments(char *s1, int delimiter, char *s2)
{
	char *arguments;
	int i;
	int c;

	if(!s1 && !s2)
		return (ft_strdup(""));
	if(!s1)
		return (ft_strdup(s2));
	if(!s2)
		return (ft_strdup(s1));
	arguments = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if(!arguments)
		return (NULL);
	i = -1;
	c = -1;
	while(s1[++i])
		arguments[i] = s1[i];
	arguments[i++] = delimiter;
	while(s2[++c])
		arguments[i++] = s2[c];
	arguments[i] = '\0';
	return (arguments);
}