/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:22 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/06 04:39:15 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_HEADER_H
#define MINISHELL_HEADER_H

#define RESERVED 		"echo pwd cd unset export exit env"
#define CMD         	"[:[A-Za-z]:]* [:[A-Za-z]:[[-]*[A-Za-z]]*]*"
#define HEREDOC     	"[[<<][A-Za-z]]*"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "./structs.h"

#define DQUOTE '\"'
#define SQUOTE '\''

t_env *env_tokenizing(char **envp);
void create_shell(char **envp, t_table **table);
void add_paths(t_env **env, t_table **table);
void execute(t_table **table, char **envp);
void free_environment(char **env_tokens);

//lexycal analise
void    lexical_analyze(char *cmdline, t_table **table);
char    *openquotes(char *cmdline);
char    *token_replacment(char *cmdline, char schr, char rchr);
char *find_replace(char *cmdline, t_env *env);
int     contains(char *tok, char *cmdline, int *pos);
int     regexp(char *cmdline, char *regex);
#endif