/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:36:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/18 14:32:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

/*  
  [nonprintable] ->  ?  ->  1
  ' ' ->  ?  ->  3
   $  ->  ?  ->  4
   |  ->  ?  ->  5
   '  ->  \a ->  7
   "  ->  \b ->  8
*/

typedef struct s_vars t_vars;
typedef struct s_table t_table;
typedef struct s_cmdline t_cmdline;
typedef struct s_env t_en;
typedef struct s_tok t_tok;
typedef struct s_cmds t_cmds;
typedef void (*t_built)(t_cmdline *, t_table *);

typedef struct s_vars
{
    int fd;
    int var;
    int let;
    int def;
    int log;
    int cconst;
    int built;
    int binar;
    int dupcopy;
    int dupcopy2;
} t_vars;

typedef enum s_types
{
    STDIN,         // 0  0
    STDOUT,        // 1  1
    STDERR,        // 2  2
    SEP,           // 3  [' ']
    WORD,          // 4  [A-Z_0-9]
    SGL,           // 5  '
    DBL,           // 6  "
    EXP_FIELD,     // 7  "..." || '...'
    REDIR_OUT,     // 8  >
    REDIR_IN,      // 9  <
    APPEND,        // 10 >>
    HEREDOC,       // 11 <<
    PIPE,          // 12 |
    UNDEFINED      // 13
} t_types;


typedef struct s_cmdline
{
    t_cmds  *cmds;
    pid_t   pid;
    char    **env;
}   t_cmdline;

typedef struct s_cmds
{
    char    *arguments;
    char    **arg_pack;
    char    *path;
    char    *err;
    int     exit_status;
    int     i_stream;
    int     o_stream;
    int     e_stream;
    pid_t   pid;
    struct  s_cmds *next;
}   t_cmds;

typedef struct s_env
{
    char *key;
    char *val;
    struct s_env *next;
} t_env;

typedef struct s_tok
{
    int     len;
    char    *tok;
    int     type;
    struct  s_tok *next;
} t_tok;

typedef struct s_table{
    char        **minienv;
    char        *reserved[7];
    char        *err_handling;
    int         status;
    int         q_c[2];
    int         hdocs;
    t_built     builtin[7];
    t_env       *env;
    t_tok       *token;
} t_table;

#endif