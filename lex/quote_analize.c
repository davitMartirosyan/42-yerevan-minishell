/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_analize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:05:04 by root              #+#    #+#             */
/*   Updated: 2022/10/15 20:08:08 by root             ###   ########.fr       */
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
		}
	}
	*pos = i;
}