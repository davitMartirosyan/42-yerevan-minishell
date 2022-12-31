<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:40:29 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/21 13:40:32 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//pwd
void		print_pwd(t_cmdline *cmd, t_table *tab);
void		no_pwd(t_table *tab);
//env
void		print_env(t_cmdline *cmd, t_table *tab);
int			check_env(char **matrix);
//echo
void		print_echo(t_cmdline *cmd, t_table *tab);
void		with_flag(char **matrix, int i);
void		without_flag(char **matrix, t_table *tab, int i);
int			check_flag(char *str);
//export
void		ft_export(t_cmdline *cmd, t_table *tab);
int			export_err(char *str);
int			check_err(char *str);
int			check_plus_equal(char *str);
int			check_key(char *str, t_table *tab);
void		create_key_value(char *str, t_table *tab);
void		create_key(char *str, t_table *tab);
void		create_key_new_value(char *str, t_table *tab);
int			create_key_new_value2(char *str, t_table *tab, int index, int len);
void		create_key_plus_value(char *str, t_table *tab);
void		loop_plus_value(char *str, t_env *temp, int index, int len);
char		**create_export_matrix(t_table *tab, int count);
void		sorting(char **arr);
int			key_count(t_table *tab);
void		print_export(t_table *tab);
//unset
void		ft_unset(t_cmdline *cmd, t_table *tab);
int			unset_err(char *str);
void		remove_node(t_table *tab, char *str);
//cd
void		print_cd(t_cmdline *cmd, t_table *tab);
void		change_path(t_table *tab, char *old_path);
void		change_path_to_home(t_table *tab, char *old_path);
int			check_path(t_table *tab, char *new_path);
void		no_old_path(char *old_path, t_table *tab);
//exit
void		ft_exit(t_cmdline *cmd, t_table *tab);
int			ft_isnumeric(char *s);
void		exit_cases(char **matrix, t_table *tab);
long double	ft_atoi_(char *nptr);

//signals
void		signals(int state);
#endif
=======
#ifndef BUILTINS_H
# define BUILTINS_H

//main functions
void	print_echo(t_cmdline *cmd, t_table *tab);
void	print_pwd(t_cmdline *cmd, t_table *tab);
void	print_cd(t_cmdline *cmd, t_table *tab);
void	ft_export(t_cmdline *cmd, t_table *tab);
void	ft_unset(t_cmdline *cmd, t_table *tab);
void	ft_exit(t_cmdline *cmd, t_table *tab);
void	print_env(t_cmdline *cmd, t_table *tab);
void	builtins(t_cmdline *cmd, t_table *tab);
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
void	exit_cases(char **matrix, t_table *tab);
unsigned long long int	ft_atoi_(char *nptr);

//signals
void	signals(int state);
#endif
>>>>>>> master
