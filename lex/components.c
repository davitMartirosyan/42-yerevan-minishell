/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   components.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dmartiro <dmartiro@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/03 00:49:58 by dmartiro		  #+#	#+#			 */
/*   Updated: 2022/12/19 10:45:37 by dmartiro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell_header.h"

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
	while (cmdline[++i])
	{	
		c = 0;
		j = i;
		if (cmdline[j] == tok[c])
		{
			flag = 0;	
			while (tok[c])
			{
				if (cmdline[j] == tok[c])
				{
					++count;
					flag++;
					j++;
				}
				c++;
			}
			if (cmdline[j] == tok[c - 1])
			{
				++count;
				i = j;
				continue;
			}
			if (count != len && cmdline[j] != tok[c - 1])
			{
				count = 0;
				i = j;
				continue;
			}
			if (flag == len && count == len)
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

void	token_replacment(char *cmdline, char schr, char rchr)
{
	int i;

	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == schr)
			cmdline[i] =  rchr;
		i++;
	}
}

char	*find_replace(char *cmdline, t_table *table)
{
	t_vars v;
	char *key;
	char *val;

	v.log = 0;
	v.let = 0;
	while (cmdline[v.log])
	{
		if (cmdline[v.log] && cmdline[v.log] == '<' && \
			cmdline[v.log+1] == '<' && v.let++){}
		if (cmdline[v.log] && cmdline[v.log] == '$' && \
			cmdline[v.log + 1] != '?' && cmdline[v.log + 1] != '$' && \
				cmdline[v.log + 1] != '\0')
		{
			if (v.let == 0)
			{
				key = keyof(cmdline, v.log + 1);
				val = valueof(key, table->env);
				cmdline = replace(cmdline, key, val, &v.log);
			}
		}
		else if (cmdline[v.log] && cmdline[v.log] == '$')
			cmdline = exit_status_code_and_pid(cmdline, table, &v.log);
		v.log++;
	}
	return (cmdline);
}

char	*keyof(char *cmdline, int pos)
{
	char *var;
	int varlen;
	int i;

	i = pos;
	varlen = 0;
	while (cmdline[i] && !ft_isspace(cmdline[i])
		&& (ft_isalnum(cmdline[i]) || cmdline[i] == '_'))
	{
		varlen++;
		i++;
	}
	var = ft_substr(cmdline, pos, varlen);
	return (var);
}

char	*valueof(char *key, t_env *env)
{
	t_env *t;

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
	char *newpoint;
	int i;

	newpoint = NULL;
	i = -1;
	while (++i < *pos);
	newpoint = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (cmd[++i] && i < *pos)
		newpoint[i] = cmd[i];
	newpoint[i] = '\0';
	newpoint = ft_strjoin(newpoint, val);
	newpoint = ft_strjoin(newpoint, cmd+i + 1 + ft_strlen(key));
	free(val);
	free(key);
	free(cmd);
	return (newpoint);
}
