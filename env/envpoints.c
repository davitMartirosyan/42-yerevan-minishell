/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpoints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:03 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/22 08:20:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

t_envkeys *env_tokenizing(char **envp)
{
    int i;
    char **_tok;
    t_envkeys *t;
    t_envkeys *temp;
    
    i = -1;
    t = malloc(sizeof(t_envkeys));
    temp = t;
    while(envp[++i])
    {
        _tok = ft_split(envp[i], '=');
        t->key = _tok[0];
        t->val = _tok[1];
        t->next =  malloc(sizeof(t_envkeys));
        t = t->next;
    }
   return (temp);
}

void add_paths(t_envkeys **env, t_table **table)
{
    char **abs;
    
    while((*env))
    {
        if(!ft_strncmp((*env)->key, "PATH", ft_strlen((*env)->key)))
        {
            (*table)->paths = ft_split((*env)->val, ':');
            return ;
        }
        (*env) = (*env)->next;
    }
}