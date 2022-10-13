/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/13 06:14:55 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum s_types
{
    SEP,           // 0 [' ']
    WORD,          // 1 [A-Z]
    FIELD,         // 2 '
    EXP_FIELD,     // 3 "
    STDIN,         // 4 0
    STDOUT,        // 5 1
    STDERR,        // 6 2
    APPEND,        // 7 >>
    HEREDOC,       // 8 <<
    PIPE           // 9 |
} t_type;

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env; 

typedef struct s_heredoc
{
    char *term;
	char *delimiter;
	char *heredoc;
} t_heredoc;

typedef struct s_cmds
{
    char    *fullcmd;
    char    *path;
    int     istream;
    int     ostream;
}   t_cmds;


typedef struct s_table{
    char        **paths;
    char        **reserved;
    char        *cmdline;
    t_env       *env;
    t_list      *cmds;
} t_table;

typedef int (*t_builtin_ptr)(t_list *, t_table *);

#endif