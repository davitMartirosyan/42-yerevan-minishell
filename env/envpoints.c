/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpoints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:03 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/27 03:34:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

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
        t->next =  malloc(sizeof(t_env));
        t = t->next;
    }
   return (temp);
}

void add_paths(t_env **env, t_table **table)
{
    char **abs;
    t_env *tmp;

    tmp = *env;
    while(tmp)
    {
        if(!ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)))
        {
            (*table)->paths = ft_split(tmp->val, ':');
            return ;
        }
        tmp = tmp->next;
    }
}