/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/16 23:35:56 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

/*  
    sgl -> ' -> \a
    dbl -> " -> \b
*/

typedef enum s_types
{
    STDIN,         // 0 0
    STDOUT,        // 1 1
    STDERR,        // 2 2
    SEP,           // 3 [' ']
    WORD,          // 4 [A-Z]
    SGL,           // 5 '
    DBL,           // 6 "
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
    int         q_c[2];
    t_env       *env;
} t_table;

typedef int (*t_builtin_ptr)(t_list *, t_table *);

#endif