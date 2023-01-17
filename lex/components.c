/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:56:51 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 05:03:45 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	token_replacment(char *cmdline, char schr, char rchr)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == schr)
			cmdline[i] = rchr;
		i++;
	}
}

char	*find_replace(char *cmdline, t_table *table)
{
	char	*key;
	char	*val;

	key = NULL;
	val = NULL;
	table->v.log = 0;
	table->v.let = 0;
	while (cmdline[table->v.log])
	{
		if (cmdline[table->v.log] && cmdline[table->v.log] == '<' && \
				cmdline[table->v.log + 1] == '<' && table->v.let++)
		{
		}
		if (dollar_expansions(cmdline, &table->v))
		{
			if (table->v.let == 0)
				_key_value_pair(&cmdline, &key, &val, table);
		}
		else if (cmdline[table->v.log] && cmdline[table->v.log] == '$')
			cmdline = exit_status_code_and_pid(cmdline, table, &table->v.log);
		table->v.log++;
	}
	return (cmdline);
}

char	*keyof(char *cmdline, int pos)
{
	char	*var;
	int		varlen;
	int		i;

	i = pos;
	varlen = 0;
	while (cmdline[i] && !ft_isspace(cmdline[i]) && \
			(ft_isalnum(cmdline[i]) || cmdline[i] == '_'))
	{
		varlen++;
		i++;
	}
	var = ft_substr(cmdline, pos, varlen);
	return (var);
}

char	*valueof(char *key, t_env *env)
{
	t_env	*t;

	t = env;
	while (t != NULL)
	{
		if (ft_strcmp(t->key, key) == 0 && \
				ft_strlen(t->key) == ft_strlen(key))
			return (ft_strdup(t->val));
		t = t->next;
	}
	return (NULL);
}

char	*replace(char *cmd, char *key, char *val, int *pos)
{
	char	*newpoint;
	int		i;

	newpoint = NULL;
	i = -1;
	while (++i < *pos)
	{
	}
	newpoint = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (cmd[++i] && i < *pos)
		newpoint[i] = cmd[i];
	newpoint[i] = '\0';
	newpoint = ft_strjoin(newpoint, val);
	newpoint = ft_strjoin(newpoint, cmd + i + 1 + ft_strlen(key));
	free(val);
	free(key);
	free(cmd);
	return (newpoint);
}
