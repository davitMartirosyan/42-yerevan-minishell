/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_components.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:49:58 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/13 07:40:57 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

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

void token_replacment(char *cmdline, char schr, char rchr)
{
	int i;

	i = 0;
	while(cmdline[i])
	{
		if(cmdline[i] == schr)
			cmdline[i] =  rchr;
		i++;
	}
}

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

char *find_replace(char *cmdline, t_env *env)
{
	char *key;
	char *val;
	char *newpoint;
	int i;

	i = 0;
	while(cmdline[i])
	{
		if(cmdline[i] && cmdline[i] == '$' 
			&& (ft_isalpha(cmdline[i+1]) || ft_isdigit(cmdline[i+1])))
		{
			key = keyof(cmdline, i+1);
			val = valueof(key, env);
			cmdline = replace(cmdline, key, val, &i);
			free(key);
		}
		i++;
	}
	return (cmdline);
}

char *keyof(char *cmdline, int pos)
{
	char *var;
	int varlen;
	int i;

	i = pos;
	varlen = 0;
	while(cmdline[i] && !ft_isspace(cmdline[i])
		&& (ft_isalpha(cmdline[i])|| ft_isdigit(cmdline[i])))
	{
		varlen++;
		i++;
	}
	var = ft_substr(cmdline, pos, varlen);
	return (var);
}

char *valueof(char *key, t_env *env)
{
	t_env *t;

	t = env;
	while(t->next != NULL)
	{
		if(ft_strncmp(t->key, key, ft_strlen(key)) == 0)
			return(t->val);
		t = t->next;
	}
	return (NULL);
}

char *replace(char *cmd, char *key, char *val, int *pos)
{
	char *newpoint;
	int i;

	i = -1;
	while(++i < *pos);
	newpoint = malloc(sizeof(char) * (i + 1));
	i = -1;
	while(cmd[++i] && i < *pos)
		newpoint[i] = cmd[i];
	newpoint[i] = '\0';
	newpoint = ft_strjoin(newpoint, val);
	newpoint = ft_strjoin(newpoint, cmd+i + 1 + ft_strlen(key));
	free(cmd);
	return (newpoint);
}
