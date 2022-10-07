/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_components.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:49:58 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/03 00:51:23 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

static char *find_var(char *cmdline, int *pos);
static char *valueof(char *key, t_env *env);

int contains(char *tok, char *cmdline, int *pos)
{
	int i;
	int c;
	int j;
	int len;
	int flag;
	int count;

	i = -1;
	len = ft_strlen(tok);
	count = 0;
	while(cmdline[++i])
	{
		
		c = 0;
		j = i;
		if(cmdline[j] == tok[c])
		{
			flag = 0;	
			while(tok[c])
			{
				if(cmdline[j] == tok[c])
				{
					++count;
					flag++;
					j++;
				}
				c++;
			}
			if(cmdline[j] == tok[c - 1])
			{
				++count;
				i = j;
				continue;
			}
			if(count != len && cmdline[j] != tok[c - 1])
			{
				count = 0;
				i = j;
				continue;
			}
			if(flag == len && count == len)
			{
				*pos = j;
				count = 0;
				return(1);
			}
			i = j;
		}
		count = 0;
	}
	return (0);
}

char *token_replacment(char *cmdline, char schr, char rchr)
{
	int i = -1;
	char *newpoint = malloc(sizeof(char) * ft_strlen(cmdline + 1));
	if(!newpoint)
		return (NULL);
	while(cmdline[++i])
	{
		
		if(cmdline[i] == schr)
			newpoint[i] =  rchr;
		else
			newpoint[i] = cmdline[i];
	}
	newpoint[i] = '\0';
	free(cmdline);
	return (newpoint);
}

char *openquotes(char *cmdline)
{
	char *newpoint;
	int i;
	int c;
	int dq;
	int sq;

	i = -1;
	dq = 0;
	sq = 0;
	while(cmdline[++i])
	{
		if(cmdline[i] == DQUOTE)
			dq++;
		else if(cmdline[i] == SQUOTE)
			sq++;
	}
	if((dq && ((dq % 2) != 0)) || (sq && ((sq % 2) != 0)))
		printf("not in even measure of DOUBLE or SINGLE quotes\n");

	newpoint = malloc(sizeof(char) * (ft_strlen(cmdline) - (dq + sq) + 1));
	if(!newpoint)
		return (NULL);
	i = -1;
	c = 0;
	while(cmdline[++i])
	{
		if(cmdline[i] == DQUOTE)
			continue;
		else if(cmdline[i] == SQUOTE)
			continue;
		newpoint[c] = cmdline[i];
		c++;
	}
	newpoint[c] = '\0';
	free(cmdline);
	return (newpoint);
}

char *find_replace(char *cmdline, t_env *env)
{
	char *key;
	char *val;
	char *newpoint;
	int i;

	i = 0;
	while(cmdline[i])
	{
		if(cmdline[i] && cmdline[i++] == '$' && !ft_isspace(cmdline[i + 1]))
		{
			key = find_var(cmdline, &i);
			val = valueof(key, env);
			printf("%s : %s\n", key, val);
			free(val);
			free(key);
		}
	}
	return (0);
}

static char *valueof(char *key, t_env *env)
{
	return (0);
}

static char *find_var(char *cmdline, int *pos)
{
	char *var;
	int i;
	int varlen;
	int len;

	i = *pos;
	varlen = 0;
	while(ft_isascii(cmdline[i++]))
		varlen++;
	i = *pos;	
	var = malloc(sizeof(char) * (varlen));
	len = ft_strlcpy(var, cmdline+i, varlen+1);
	return (var);
}