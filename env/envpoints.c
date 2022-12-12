/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpoints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:03 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/12 14:35:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_env *env_tokenizing(char **envp)
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
        t->key = ft_strdup(_tok[0]);
        free(_tok[0]);
        t->val = ft_strdup(_tok[1]);
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

void add_paths(t_env **env, t_table **table)
{
    while((*env) != NULL)
    {
        if(!ft_strncmp((*env)->key, "PATH", ft_strlen((*env)->key)))
        {
            (*table)->paths = ft_split((*env)->val, ':');
            return ;
        }
        env = &(*env)->next;
    }
    return ;
}