/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_analize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:05:04 by root              #+#    #+#             */
/*   Updated: 2022/10/17 05:46:09 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

void openquotes(char *cmdline)
{
	int i;
	int dbl;
	int sgl;

	i = -1;
	while(cmdline[++i])
	{
		if(cmdline[i] == '\'')
			inside_quote(cmdline, &i, DBL);
		if(cmdline[i] == '\"')
			inside_quote(cmdline, &i, SGL);
	}
}

int check_quotes(char *cmdline, int *q_c)
{
	int i;
	int dbl;
	int sgl;

	dbl = 0;
	sgl = 0;
	i = -1;
	while(cmdline[++i])
	{
		if(cmdline[i] == '\"')
			dbl++;
		else if(cmdline[i] == '\'')
			sgl++;
	}
	q_c[0] = dbl;
	q_c[1] = sgl;
	if((dbl % 2 != 0) || (sgl % 2 != 0))
		return (0);
	else 
		return (1);
}

void inside_quote(char *cmdline, int *pos, int find)
{
	int i;

	i = *pos;
	if(find == SGL)
	{
		while(cmdline[++i])
		{
			if(cmdline[i] == '\"')
				break;
			if(cmdline[i] == '\'')
				cmdline[i] = '\a';
		}
	}
	else if(find == DBL)
	{
		while(cmdline[++i])
		{
			if(cmdline[i] == '\'')
				break;
			if(cmdline[i] == '\"')
				cmdline[i] = '\b';
			if(cmdline[i] == '$')
				cmdline[i] = 4;
		}
	}
	*pos = i;
}

int quote_syntax_analyze(char *cmdline, int *q_c)
{
	if(check_quotes(cmdline, q_c))
	{
		token_replacment(cmdline, '\a', '\'');
		token_replacment(cmdline, '\b', '\"');
		return (1);
	}
	else
	{
		token_replacment(cmdline, '\a', '\'');
		token_replacment(cmdline, '\b', '\"');
		return (0);
	}
}