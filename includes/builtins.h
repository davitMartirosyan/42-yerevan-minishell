/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:39:57 by sabazyan          #+#    #+#             */
/*   Updated: 2022/10/25 14:50:22 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//main functions
void	print_echo(char *cmd);
void	print_pwd(char *cmd);
void	print_cd(char *cmd, t_table *tab);
void	ft_export(char *cmd, t_table *tab);
void	ft_unset(char *cmd, t_table *tab);
void	ft_exit(char *cmd);
void	print_env(char *cmd, t_table *table);
void	builtins(char *cmdline, t_table *table);
//echo utils
int		is_keyword(char *str);
int		is_token(char *str);
void	with_flag(char **matrix, int i);
//export utils
int		export_err(char *str);
t_table	*create_tab(char **env);
int		check_plus_equal(char *str);
int		check_key(char *str, t_table *tab);
void	create_key_value(char *str, t_table *tab);
void	create_key(char *str, t_table *tab);
void	create_key_new_value(char *str, t_table *tab);
int		create_key_new_value2(char *str, t_table *tab, int index, int len);
void	create_key_plus_value(char *str, t_table *tab);
void	loop_plus_value(char *str, t_env *temp, int index, int len);
char	**create_export_matrix(t_table *tab, int count);
void	sorting(char **arr);
int		key_count(t_table *tab);
void	print_export(t_table *tab);
//unset utils
int		unset_err(char *str);
void	remove_node(t_table *tab, char *str);
//cd utils
void	change_path(t_table *tab, char *old_path);
void	change_path_to_home(t_table *tab, int res, char *old_path);
//exit utils
int		ft_isnumeric(char **s);

#endif