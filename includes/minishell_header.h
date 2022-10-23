/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:22 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/23 07:18:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_HEADER_H
#define MINISHELL_HEADER_H

#define RESERVED			"echo pwd cd unset export exit env"
#define TOKENS				"|<>;&"
#define CMD_REGEX         	"[:[A-Za-z]:]* [:[A-Za-z]:[[-]*[A-Za-z]]*]*"
#define HEREDOC_REGEX    	"[[<<][A-Za-z]]*"
#define SHELL 				"\033[0;33mMinishell-$\x1B[0m "


/*Error Handlers*/
#define QUOTE_SYNTAX_ERR 	"syntax error near unexpected token"
#define SYNTAX_ERR          2
#define CMD_NOT_FOUND_ERR   "not found"
#define CMD_ERR             127
#define PATH_SYNTAX_ERR     "No such file or directory"
#define PATH_ERR            1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "./structs.h"


/**********************************************/
/***************Listing************************/
/**********************************************/
t_tok *new_token(int len, char *token, int type);



/**********************************************/
/***************Initializing*******************/
/**********************************************/
t_env *env_tokenizing(char **envp);
void create_shell(char **envp, t_table **table);
void add_paths(t_env **env, t_table **table);
void free_environment(char **env_tokens);
void destruct_shell(t_table **table);


/**********************************************/
/*************Lexical Analyzing****************/
/**********************************************/
void	lexical_analyzer(char *cmdline, t_table *table);
void    token_replacment(char *cmdline, char schr, char rchr);

int     check_quotes(char *cmdline, int *q_counts);
int		quote_syntax_analyzer(char *cmdline, int *q_c);
void    openquotes(char *cmdline);
void    inside_quote(char *cmdline, int *pos, int find);

int     regexp(char *cmdline, char *regex);
char    *find_replace(char *cmdline, t_env *env);
int     contains(char *tok, char *cmdline, int *pos);
char    *keyof(char *cmdline, int pos);
char    *valueof(char *key, t_env *env);
char    *replace(char *cmdline, char *key, char *val, int *pos);

t_tok	*tokenization(char *cmdline);


/**********************************************/
/************Parsing (Parse Tree)**************/
/**********************************************/



/**********************************************/
/*******************Executing******************/
/**********************************************/
int execute(char *cmd, t_table **table, char **envp);

#endif