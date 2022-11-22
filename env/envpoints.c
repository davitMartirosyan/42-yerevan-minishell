/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpoints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:03 by dmartiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/11/02 22:01:44 by dmartiro         ###   ########.fr       */
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
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
<<<<<<< HEAD
			break;
=======
        {
            t->next = NULL;
			break;
        }
>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
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