/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpoints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:03 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/04 20:03:04 by dmartiro         ###   ########.fr       */
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
        t->key = _tok[0];
        t->val = _tok[1];
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