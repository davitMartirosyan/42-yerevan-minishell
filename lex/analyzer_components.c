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

static char *find_var(char *cmdline, int pos);
static char *valueof(char *key, t_env *env);
static char *replace(char *cmd, char *key, char *val, int pos);

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
		if(cmdline[i] && cmdline[i++] == '$' && !ft_isspace(cmdline[i])
			&& (cmdline[i] != '\"' || cmdline[i] != '\''))
		{
			key = find_var(cmdline, i);
			val = valueof(key, env);
			// printf("%s\n%s\n", key, val);
			cmdline = replace(cmdline, key, val, i-1);
		}
	}
	printf("%s\n", cmdline);
	return (0);
}
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
static char *replace(char *cmd, char *key, char *val, int pos)
{
	//all string 			-> cmd;
	//right half 			-> cmd+pos;
	//key of var 			-> key;
	//value of  key 		-> val;
	//position of $ sign	-> pos;
	char *newpoint;
	int i;

	newpoint = malloc(sizeof(char) * (pos + 1));
	if(!newpoint)
		return (NULL);
	i = 0;
	while(i < pos)
	{
		newpoint[i] = cmd[i];
		i++;
	}
	newpoint[i] = '\0';
	newpoint = ft_strjoin(newpoint, val);
	newpoint = ft_strjoin(newpoint, cmd+pos+ft_strlen(key));
	free(cmd);
	return (newpoint);
}

static char *valueof(char *key, t_env *env)
{
	t_env *t;

	t = env;
	while(t->next != NULL)
	{
		if(ft_strncmp(t->key, key, ft_strlen(t->key)) == 0)
			return(t->val);
		t = t->next;
	}
	return (0);
}

static char *find_var(char *cmdline, int pos)
{
	char *var;
	int varlen;
	int i;

	i = pos;
	varlen = 0;
	while(ft_isascii(cmdline[pos]) && cmdline[pos++] != '$')
		varlen++;
	var = ft_substr(cmdline, i, varlen);
	return (var);
}