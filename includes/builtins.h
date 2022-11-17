/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:39:57 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/17 12:12:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#define RESERVED			"echo pwd cd unset export exit env"
#define TOKENS				"| < > ; &"

typedef struct s_tab{
    t_env       *env;
} t_tab;

//main functions
void    print_echo(char *cmd);
void    print_pwd(char *cmd);
void    print_cd(char *cmd);
void    ft_export(char *cmd, t_tab *tab);
void    ft_unset(char *cmd, t_tab *tab);
void    print_env(char *cmd, char **env);
//echo utils
int     is_keyword(char *str);
int     is_token(char *str);
//export utils
char	*add_quotes(char *str);
int     export_err(char *str);
void	print_list_export(t_tab *tab);
t_tab	*create_tab(char **env);
void	add_node(t_tab *tab, char *str);
int     check_var(char *str);
int     check_key(t_env *env, char *str);
//unset utils
int     unset_err(char *str);
void	remove_node(t_tab *tab, char *str);

#endif