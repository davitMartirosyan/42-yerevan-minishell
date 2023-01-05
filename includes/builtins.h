#ifndef BUILTINS_H
# define BUILTINS_H

//main functions
void	print_echo(t_cmds *cmd, t_table *tab);
void	print_pwd(t_cmds *cmd, t_table *tab);
void	print_cd(t_cmds *cmd, t_table *tab);
void	ft_export(t_cmds *cmd, t_table *tab);
void	ft_unset(t_cmds *cmd, t_table *tab);
void	ft_exit(t_cmds *cmd, t_table *tab);
void	print_env(t_cmds *cmd, t_table *tab);

//echo utils
int		is_keyword(char *str);
int		is_token(char *str);
void	with_flag(char **matrix, int i);

//export utils
t_table *create_tab(char **env);
int		export_err(char *str);
int		check_plus_equal(char *str);
int		check_key(char *str, t_table *tab);
int     check_flag(char *str);
void	without_flag(char **matrix, int i);
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
void	change_path_to_home(t_table *tab, char *old_path);
void	no_old_path(char *old_path, t_table *tab);

//exit utils
int     ft_isnumeric(char *str);
void	exit_cases(char **matrix, t_table *tab);
long double ft_atoi_(char *str);
void	no_pwd(t_table *tab);
int	check_err(char *str);
int	check_path(t_table *tab, char *new_path);
#endif