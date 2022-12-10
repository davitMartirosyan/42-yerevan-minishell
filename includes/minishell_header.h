/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:22 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/10 22:41:35 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_HEADER_H
# define MINISHELL_HEADER_H

# define RESERVED			"echo pwd cd unset export exit env clear"
# define TOKENS				"| < > ; &"
# define CMD_REGEX         	"[:[A-Za-z]:]* [:[A-Za-z]:[[-]*[A-Za-z]]*]*"
# define HEREDOC_REGEX    	"[[<<][A-Za-z]]*"
# define SHELL 				"Minishell-$ "
# define SHELLERR           "-sadm: " 


/*Error Handlers*/
# define TOKEN_SYNTAX_ERR 	" : Syntax error near unexpected token\n"
# define SYNTAX_ERR          2

# define COMMANDERR         " : Command Not Found\n"
# define CMD_ERR             127

# define FILEERR            " : No Such file or directory\n"
# define PATH_ERR            1

# define HEREDOC_SYNTAX_WARNING    "Warning: HEREDOC (wanted ${hd})"
# define HEREDOC_WARNING     0

# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "./structs.h"
# include "./builtins.h"

/**********************************************/
/*******************Listing********************/
/**********************************************/
t_tok	*new_token(int len, char *token, int type);
void	add(t_tok **lst, t_tok *new);

/**********************************************/
/****************Initializing******************/
/**********************************************/
t_env	*env_tokenizing(char **envp);
void	create_builtins(t_table *table);
void	create_shell(char **envp, t_table **table);
void	add_paths(t_env **env, t_table **table);
void	free_environment(char **env_tokens);
void	destruct_shell(t_table **table);

/**********************************************/
/**************Lexical Analyzing***************/
/**********************************************/
int		check_quotes(char *cmdline, int *q_counts);
int		quote_syntax_analyzer(char *cmdline, int *q_c);
int		regexp(char *cmdline, char *regex);
int		contains(char *tok, char *cmdline, int *pos);
void	lexical_analyzer(char *cmdline, t_table *table);
void	token_replacment(char *cmdline, char schr, char rchr);
void	openquotes(char *cmdline);
void	inside_quote(char *cmdline, int *pos, int find);
char	*find_replace(char *cmdline, t_env *env);
char	*keyof(char *cmdline, int pos);
char	*valueof(char *key, t_env *env);
char	*replace(char *cmdline, char *key, char *val, int *pos);

/**********************************************/
/****************Tokenizing********************/
/**********************************************/
t_tok	*tokenization(char *cmdline);
char	*word(char *cmdline, int len, int s_pos);
int		wordlen(char *wordstart, int s_pos);
int		typeface(int c, int len);
void	add_word(char *cmdline, int *pos, t_tok **token);
void	redirection(char *cmdline, int *pos, int io, t_tok **token);
void	add_pipe(char *cmdline, int *pos, int _p_ch, t_tok **token);
void	expansion(char *cmdline, int *pos, int quote, t_tok **token);
void	space(char *cmdline, int *pos, t_tok **token);

/**********************************************/
/************Parsing (Parse Tree)**************/
/**********************************************/
t_cmdline	*parse_tree(t_table *table);
t_cmds	*parse(t_tok *token, t_table *table);
void	std(t_cmds **cmds);
void	separate(t_cmds **commands);
void	parse_to(t_tok *token, t_table *table, t_cmds **cmds);
char    *new_file(char *delim);
void	select_filename(t_tok **token, t_cmds *cmds);
void	open__file__check__type(int type, char *filename, t_cmds *cmds);
void	check_type(int fd, int type, t_cmds *cmds);
void	heredoc(t_tok **token, t_cmds *cmds, t_table *table);
char	*heredoc_delimiter(t_tok **token, t_vars **v);
char	*open_heredoc_prompt(char *delim, int flag, t_table *table);
char	*join_arguments(char *s1, int delimiter, char *s2);
int		pipes(t_tok **token);
int		type_is_p_h(t_tok **token, t_cmds ***cmds, t_table *table);
int		typeis_redirection(int type);
int		typeis_arg(int type);
int		typeis_heredoc(int type);

/**********************************************/
/****************Err Handling******************/
/**********************************************/
int		syntax_handling(t_tok **tokens, t_cmdline **cmdline);

/**********************************************/
/******************Builtins********************/
/**********************************************/
int builtin_execution(int k, t_cmdline *cmd, t_table *table);
int find_in(char *builtin, char **reserved);
int echo(t_cmds *cmd, t_table *table);
int clear(t_cmds *cmd, t_table *table);
// int pwd    (t_cmdline *cmd, t_table *table);
// int cd     (t_cmdline *cmd, t_table *table);
// int unset  (t_cmdline *cmd, t_table *table);
// int export (t_cmdline *cmd, t_table *table);
// int exit_  (t_cmdline *cmd, t_table *table);
// int env    (t_cmdline *cmd, t_table *table);

/**********************************************/
/*****************Execution********************/
/**********************************************/
void	execution(t_cmdline **commands, t_table **table);


/**********************************************/
/****************Free Resources****************/
/**********************************************/
void    print_tokens(t_tok **token);
void    reset_update_table(t_table **table, t_cmdline *tree);
void    free_tokens(t_tok **token);
void	free_cmdline(t_cmdline *tree);
void	free_arg_pack(char **arg_pack);
#endif