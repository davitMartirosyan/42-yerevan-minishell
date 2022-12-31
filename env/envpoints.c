/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpoints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:03 by dmartiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/13 11:54:17 by user             ###   ########.fr       */
=======
/*   Updated: 2022/12/18 14:35:09 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_env   *env_tokenizing(char **envp)
{
    int i;
    char **_tok;
    t_env *t;
    t_env *temp;
    
    i = -1;
    t = malloc(sizeof(t_env));
    temp = t;
    while(envp[++i])
    {
        _tok = ft_split(envp[i], '=');
<<<<<<< HEAD
		// if (!ft_strcmp(_tok[0], "OLDPWD"))
		// 	continue;
        t->key = ft_strdup(_tok[0]);
        free(_tok[0]);
        t->val = ft_strdup(_tok[1]);
=======
        t->key = ft_strdup(_tok[0]);
        free(_tok[0]);
        if(_tok[1])
            t->val = ft_strdup(_tok[1]);
>>>>>>> master
        free(_tok[1]);
        free(_tok);
        if (!envp[i + 1])
			break;
        t->next = malloc(sizeof(t_env));
        if(!t->next)
            return (NULL);
        t = t->next;
    }
    t->next = NULL;
   return (temp);
}

<<<<<<< HEAD
void    add_paths(t_env **env, t_table **table)
{
=======
char	**add_paths(t_env **env)
{
	char	**paths;
	
>>>>>>> master
    while((*env) != NULL)
    {
        if(!ft_strncmp((*env)->key, "PATH", ft_strlen((*env)->key)))
        {
<<<<<<< HEAD
            (*table)->paths = ft_split((*env)->val, ':');
            return ;
        }
        env = &(*env)->next;
    }
    return ;
=======
            paths = ft_split((*env)->val, ':');
            return (paths);
        }
        env = &(*env)->next;
    }
    return (NULL);
>>>>>>> master
}

char    **create_envp(t_env **env)
{
	int i;
    int c;
    char **envp;
    t_env *minienv;

    minienv = *env;
	i = 0;
	while(*env != NULL)
	{
		i++;
		env = &(*env)->next;
	}
<<<<<<< HEAD
        // ft_putstr_fd(minienv->key, 1);
=======
>>>>>>> master
    envp = malloc(sizeof(char *) * (i + 1));
    if(!envp)
        return (NULL);
    c = -1;
    while(minienv != NULL)
    {
        envp[++c] = join_env(minienv->key, '=', minienv->val);
        minienv = minienv->next;
    }
    return (envp);
}

char *join_env(char *key, char eq, char *value)
{
    t_vars v;
    char *env_line;
    
    if(!key && !value)
		return (ft_strdup(""));
	if(!key)
		return (ft_strdup(value));
	if(!value)
		return (ft_strdup(key));
    v.log = ft_strlen(key);
    v.def = ft_strlen(value);
    env_line = malloc(sizeof(char) * (v.log + v.def + 2));
    if(!env_line)
        return (NULL);
    v.var = -1;
    v.let = -1;
    while(key[++v.var])
        env_line[v.var] = key[v.var];
    env_line[v.var++] = eq;
    while(value[++v.let])
        env_line[v.var++] = value[v.let];
    env_line[v.var] = '\0';
    return (env_line);
}