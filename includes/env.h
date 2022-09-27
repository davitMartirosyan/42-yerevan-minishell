/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:12 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/27 03:34:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

t_env *env_tokenizing(char **envp);
void create_env(t_env **env, char **envp, t_table **table);
void add_paths(t_env **env, t_table **table);

#endif